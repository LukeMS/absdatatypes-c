/*****************************************************************
 *
 * ohtbl.h
 *
 * Source: "Mastering Algorithms with C" (1999, p. 164) by Kyle Loudon,
 *         published by O'Reilly & Associates.
 *
 * This source can be freely used, adapted, and redistributed in source or
 * binary form, so long as an acknowledgment appears in derived source files.
 * The citation should list that the code comes from the  book  "Mastering
 * Algorithms with C"  by Kyle Loudon,  published by O'Reilly & Associates.
 * This code is under copyright and cannot be included in any other book,
 * publication, or  educational product  without  permission  from  O'Reilly
 * & Associates.  No warranty is attached; we cannot take responsibility for
 * errors or  fitness for use.
 *
 *****************************************************************/

#ifndef OHTBL_H
#define OHTBL_H
#include <stdlib.h>


/*****************************************************************
 * OHTbl, OHTbl_: structure for open-addressed hash
 ****************************************************************/
typedef struct OHTbl_ {
int                positions;
void               *vacated;
int                (*h1)(const void *key);
int                (*h2)(const void *key);
int                (*match)(const void *key1, const void *key2);
void               (*destroy)(void *data);
int                size;
void               **table;
} OHTbl;



/*****************************************************************
 * PUBLIC INTERFACE
 ****************************************************************/


/*************************************************************//**
 * ohtbl_init: Initializes the open-addressed hash table `htbl`.
 *
 * This operation must be called for an open-addressed hash table before the
 * hash table can be used with any other operation.
 *
 * \param positions The number of positions to be allocated in the hash table
 * \param *h1 user-defined auxiliary hash functions for double hashing
 * \param *h2 user-defined auxiliary hash functions for double hashing
 * \param *match user-defined function to determine if two keys match. It
 *     should return 1 if key1 is equal to key2, and 0 otherwise.
 * \param *destroy provides a way to free dynamically allocated data when
 *     ohtbl_destroy is called. For example, if the hash table contains data
 *     dynamically allocated using malloc, destroy should be set to `free` to
 *     free the data as the hash table is destroyed. For structured data
 *     containing several dynamically allocated members, destroy should be
 *     set to a user-defined function that calls free for each dynamically
 *     allocated member as well as for the structure itself. For a hash table
 *     containing data that should not be freed, destroy should be set to
 *     `NULL`.
 *
 * \return 0 if initializing the hash table is successful, or –1 otherwise.
 ****************************************************************/
int ohtbl_init(OHTbl *htbl, int positions, int (*h1)(const void *key), int
   (*h2)(const void *key), int (*match)(const void *key1, const void *key2),
   void (*destroy)(void *data));
void ohtbl_destroy(OHTbl *htbl);
int ohtbl_insert(OHTbl *htbl, const void *data);
int ohtbl_remove(OHTbl *htbl, void **data);
int ohtbl_lookup(const OHTbl *htbl, void **data);
#define ohtbl_size(htbl) ((htbl)->size)
#endif
