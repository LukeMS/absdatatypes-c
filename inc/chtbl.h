/*****************************************************************
 *
 * chtbl.h
 * Chained Hash Table
 *
 * Source: "Mastering Algorithms with C" (1999, p. 150) by Kyle Loudon,
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


#ifndef CHTBL_H
#define CHTBL_H
#include <stdlib.h>
#include "list.h"


/*************************************************************//**
 * CHTbl, CHTbl_: structure for chained hash tables.
 ****************************************************************/
typedef struct CHTbl_ {
    int                buckets;
    int                (*h)(const void *key, int buckets);
    int                (*match)(const void *key1, const void *key2);
    void               (*destroy)(void *data);
    int                size;
    List               *table;
} CHTbl;



/*****************************************************************
 *
 * PUBLIC INTERFACE
 *
 *****************************************************************/


/*************************************************************//**
 * chtbl_init:
 *
 * Initializes the chained hash table specified by htbl. This operation must
 * be called for a chained hash table before the hash table can be used
 * with any other operation.
 * Complexity: O(m), where m is the number of buckets in the hash table.
 *
 * \param buckets The number of buckets allocated in the hash table
 * \param *h a user-defined hash function for hashing keys
 * \param *match specifies a user-defined function to determine whether two
 *     keys match. It should return 1 if key1 is equal to key2, and 0
 *     otherwise.
 * \param *destroy provides a way to free dynamically allocated data when
 *     chtbl_destroy is called. For example, if the hash table contains data
 *     dynamically allocated using malloc, destroy should be set to free to
 *     free the data as the hash table is destroyed. For structured data
 *     containing several dynamically allocated members, destroy should be
 *     set to a user-defined function that calls free for each dynamically
 *     allocated member as well as for the structure itself. For a hash table
 *     containing data that should not be freed, destroy should be set to
 *     NULL.
 *
 * \return 0 if initializing the hash table is successful, or –1 otherwise.
 ****************************************************************/
int chtbl_init(CHTbl *htbl, int buckets,
    int (*h)(const void *key, int buckets),
    int (*match)(const void *key1, const void *key2),
    void (*destroy)(void*data));


/*************************************************************//**
 * chtbl_destroy: Destroys the chained hash table specified by htbl.
 *
 * No other operations are permitted after calling chtbl_destroy unless
 * chtbl_init is called again. The chtbl_destroy operation removes all
 * elements from a hash table and calls the function passed as destroy to
 * chtbl_init once for each element as it is removed,
 * provided destroy was not set to NULL.
 * Complexity: O(m), where m is the number of buckets in the hash table.
 *
 * \param *htbl pointer to a `CHTbl` struct
 *
 * \return None
 ****************************************************************/
void chtbl_destroy(CHTbl *htbl);


/*************************************************************//**
 * chtbl_insert: Inserts an element into the chained hash table `htbl`.
 *
 * The new element contains a pointer to data, so the memory referenced by
 * data should remain valid as long as the element remains in the hash table.
 * It is the responsibility of the caller to manage the storage associated
 * with data.
 * Complexity: O(1)
 *
 * \param *htbl pointer to a `CHTbl` struct
 * \param *data pointer to the data that will be referenced by the new element
 *
 * \return 0 if inserting the element is successful, 1 if the element is
 *     already in the hash table, or –1 otherwise.
 ****************************************************************/
int chtbl_insert(CHTbl *htbl, const void *data);


/*************************************************************//**
 * chtbl_remove: Removes the element matching data from `htbl`.
 *
 *  Upon return, data points to the data stored in the element that
 * was removed. It is the responsibility of the caller to manage the storage
 * associated with the data.
 * Complexity: O(1)
 *
 * \param *htbl pointer to a `CHTbl` struct
 * \param **data pointer to the pointer where a reference to the data from
 *     the removed element will be stored.
 *
 * \return 0 if removing the element is successful, or –1 otherwise.
 ****************************************************************/
int chtbl_remove(CHTbl *htbl, void **data);


/*************************************************************//**
 * chtbl_lookup: Determines whether an element matches data in `htbl`.
 *
 * If a match is found, data points to the matching data in the hash table
 * upon return.
 * Complexity: O(1)
 *
 * \param *htbl pointer to a `CHTbl` struct
 * \param **data pointer to the pointer where a reference to the matching
 * data, if found, will be stored.
 *
 * \return 0 if the element is found in the hash table, or –1 otherwise.
 ****************************************************************/
int chtbl_lookup(const CHTbl *htbl, void **data);

int chtbl_pop(CHTbl *htbl, void **data);

/*************************************************************//**
 * chtbl_grow: Grow the chained hash table to twice its current size.
 *
 * In practice a new table is created, every element is removed from the
 * former table and insert into the new one with a new hash fitting the
 * current size.
 * Complexity: O(n), where n is the number of elements in the hash table.
 *
 * \param *htbl pointer to a `CHTbl` struct
 *
 * \return 0 if the element is found in the hash table, or –1 otherwise.
 ****************************************************************/
void chtbl_grow(CHTbl *htbl);


/*************************************************************//**
 * chtbl_size: evaluates to the number of elements in `htbl`.
 *
 * Complexity: O(1)
 *
 * \param *htbl pointer to a `CHTbl` struct
 *
 * \return Number of elements in the hash table.
 ****************************************************************/
#define chtbl_size(htbl) ((htbl)->size)


/*************************************************************//**
 * chtbl_loadfactor: evaluates to the number of elements in `htbl`.
 *
 * The load factor of a hash table is defined as:
 *     α = n / m
 * where n is the number of elements in the table and m is the number of
 * positions into which elements may be hashed. The load factor of a chained
 * hash table indicates the maximum number of elements we can expect to
 * encounter in a bucket, assuming uniform hashing.
 * Performance degrades significantly if we make the number of buckets in the
 * table small relative to the number of elements we plan to insert.
 * Python's dict implementation, for example, is said to grow when it's load
 * factor reaches 2/3, to prevent performance degradation.
 * Complexity: O(1)
 *
 * \param *htbl pointer to a `CHTbl` struct
 *
 * \return Load factor.
 ****************************************************************/
#define chtbl_loadfactor(htbl) (((float)((htbl)->size)) / ((htbl)->buckets))


#endif
