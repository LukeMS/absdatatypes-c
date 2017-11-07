/*****************************************************************
 *
 * chtbl.c
 * Chained Hash Table
 *
 * Source: "Mastering Algorithms with C" (1999, p. 150) by Kyle Loudon,
 *         published by O'Reilly & Associates.
 *
 * This source can be freely used, adapted, and redistributed in source or
 * binary form, so long as an acknowledgment appears in derived source files.
 * The citation should list that the code comes from the book "Mastering
 * Algorithms with C" by Kyle Loudon, published by O'Reilly & Associates.
 * This code is under copyright and cannot be included in any other book,
 * publication, or educational product without permission from O'Reilly
 * & Associates. No warranty is attached; we cannot take responsibility for
 * errors or fitness for use.
 *
 *****************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "chtbl.h"


/*****************************************************************
 * chtbl_init.
 ****************************************************************/
int chtbl_init(CHTbl *htbl, int buckets,
    int (*h)(const void *key, int buckets),
    int (*match)(const void *key1, const void *key2),
    void (*destroy)(void*data))
{
    int                i;

    /*****************************************************************
     * Allocate space for the hash table.
     ****************************************************************/
    if ((htbl->table = (List *)malloc(buckets * sizeof(List))) == NULL) {
        return -1;
    }

   /*****************************************************************
    * Initialize the buckets.
    ****************************************************************/
    htbl->buckets = buckets;
    for (i = 0; i < htbl->buckets; i++) {
       list_init(&htbl->table[i], destroy);
    }

    /*****************************************************************
     * Encapsulate the functions.
     ****************************************************************/
    htbl->h = h;
    htbl->match = match;
    htbl->destroy = destroy;

    /*****************************************************************
     * Initialize the number of elements in the table.
     ****************************************************************/
    htbl->size = 0;

    return 0;
}


/*****************************************************************
 * chtbl_destroy
 ****************************************************************/
void chtbl_destroy(CHTbl *htbl) {
    int i;

    /*****************************************************************
     * Destroy each bucket.
     ****************************************************************/
    for (i = 0; i < htbl->buckets; i++) {
       list_destroy(&htbl->table[i]);
    }

    /*****************************************************************
     * Free the storage allocated for the hash table.
     ****************************************************************/
    free(htbl->table);

    /*****************************************************************
     * No operations are allowed now, but clear the structure as a precaution.
     ****************************************************************/
    memset(htbl, 0, sizeof(CHTbl));

    return;
}


/*****************************************************************
 * chtbl_insert
 ****************************************************************/
int chtbl_insert(CHTbl *htbl, const void *data) {
    void               *temp;
    int                bucket,
                       retval;

    /*****************************************************************
     * Do nothing if the data is already in the table.
     ****************************************************************/
    temp = (void *)data;
    if (chtbl_lookup(htbl, &temp) == 0){
        return 1;
    }

    /*****************************************************************
     * Hash the key.
     ****************************************************************/
    bucket = htbl->h(data, htbl->buckets) % htbl->buckets;

    /*****************************************************************
     * Insert the data into the bucket.
     ****************************************************************/
    if ((retval = list_ins_next(&htbl->table[bucket], NULL, data)) == 0) {
        htbl->size++;
        if (chtbl_loadfactor(htbl) > 2)
        {
            chtbl_grow(htbl);
        }
    }

    return retval;
}


/*****************************************************************
 * chtbl_remove
 ****************************************************************/
int chtbl_remove(CHTbl *htbl, void **data)
{
    ListElmt           *element,
                       *prev;
    int                bucket;

    /*****************************************************************
     * Hash the key.
     ****************************************************************/
    bucket = htbl->h(*data, htbl->buckets) % htbl->buckets;

    /*****************************************************************
     * Search for the data in the bucket.
     ****************************************************************/
    prev = NULL;
    for (element = list_head(&htbl->table[bucket]); element != NULL; element =
       list_next(element)) {
       if (htbl->match(*data, list_data(element))) {

          /*****************************************************************
           * Remove the data from the bucket.
           ****************************************************************/
          if (list_rem_next(&htbl->table[bucket], prev, data) == 0) {
             htbl->size--;
             return 0;
             }
          else {
             return -1;
          }
       }
       prev = element;
    }

    /*****************************************************************
     * Return that the data was not found.
     ****************************************************************/
    return -1;
}


/*****************************************************************
 * chtbl_lookup
 ****************************************************************/
int chtbl_lookup(const CHTbl *htbl, void **data) {
    ListElmt           *element;
    int                bucket;

    /*****************************************************************
     * Hash the key.
     ****************************************************************/
    bucket = htbl->h(*data, htbl->buckets) % htbl->buckets;

    /*****************************************************************
     * Search for the data in the bucket.
     ****************************************************************/
    for (element = list_head(&htbl->table[bucket]); element != NULL;
         element = list_next(element)) {

       if (htbl->match(*data, list_data(element))) {
          /*****************************************************************
           * Pass back the data from the table.
           ****************************************************************/
          *data = list_data(element);

          return 0;
       }
    }

    /*****************************************************************
     * Return that the data was not found.
     ****************************************************************/
    return  -1;
}

int chtbl_pop(CHTbl *htbl, void **data)
{
    List *bucket;
    ListElmt *element;
    int i;

    for (i = 0; i < htbl->buckets; i++)
    {
        bucket = &htbl->table[i];
        for (element = list_head(bucket);
             element != NULL;
             element=list_next(element))
        {
            *data = list_data(element);
            chtbl_remove(htbl, data);
            return 0;
        }
    }
    return -1;
}

/*****************************************************************
 * chtbl_grow
 ****************************************************************/
void chtbl_grow(CHTbl *htbl)
{
    printf("chtbl_grow %d -> %d (size %d, load factor %.2f)...",
           htbl->buckets, htbl->buckets * 2, htbl->size,
           chtbl_loadfactor(htbl));
    CHTbl tmp = *htbl;
    chtbl_init(htbl, htbl->buckets * 2, htbl->h, htbl->match, htbl->destroy);

    for(void *data; !chtbl_pop(&tmp, &data); chtbl_insert(htbl, data));

    puts(" done!");


    return;
}
