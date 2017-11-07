/*****************************************************************
 *
 * dlist.h
 *
 * Source: "Mastering Algorithms with C" (1999, p. 72) by Kyle Loudon,
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

#ifndef DLIST_H
#define DLIST_H

#include <stdlib.h>


/*****************************************************************
 *
 * DListElmt, DListElmt_: structure for doubly-linked list elements.
 *
 *****************************************************************/
typedef struct DListElmt_ {
    void *data;
    struct DListElmt_ *next;
    struct DListElmt_ *prev;
} DListElmt;


/*****************************************************************
 *
 * DList, DList_: structure for doubly-linked lists.
 *
 *****************************************************************/
typedef struct DList_ {
    int size;

    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);

    DListElmt *head;
    DListElmt *tail;

} DList;



/*****************************************************************
 *
 * PUBLIC INTERFACE
 *
 *****************************************************************/


/*************************************************************//**
 * dlist_init: Initializes the doubly-linked list specified by list.
 *
 * This operation must be called for a doubly-linked list before the list can
 * be used with any other operation. The destroy argument provides a way to
 * free dynamically allocated data when dlist_destroy is called.
 * Complexity: O(1)
 *
 * \param *list pointer to a DList struct
 * \param *destroy pointer to a function to clear allocated memory for data.
 *     If the list contains data dynamically allocated using malloc, destroy
 *     should be set to free to free the data as the list is destroyed.
 *     For structured data containing several dynamically allocated members,
 *     destroy should be set to a user-defined function that calls free for
 *     each dynamically allocated member as well as for the structure itself.
 *     For a list containing data that should not be freed, destroy should be
 *     set to NULL.
 *
 * \return void
 ****************************************************************/
void dlist_init(DList *list, void(*destroy)(void *data));


/*************************************************************//**
 * dlist_destroy: Destroys the doubly-linked list specified by list.
 *
 * No other operations are permitted after calling dlist_destroy unless
 * dlist_init is called again. The dlist_destroy operation removes all
 * elements from a list and calls the function passed as
 * destroy to dlist_init once for each element as it is removed, provided
 * destroy was not set to NULL.
 * Complexity: O(n), where n is the number of elements in the list.
 *
 * \param *list pointer to a DList struct
 *
 * \return None
 ****************************************************************/
void dlist_destroy(DList *list);


/*************************************************************//**
 * dlist_ins_next: Inserts an element just after element in the list.
 *
 * The new element contains a pointer to data, so the memory referenced by
 * data should remain valid as long as the element remains in the list. It is
 * the responsibility of the caller to manager the storage associated with
 * data.
 * Complexity: O(1)
 *
 * \param *list pointer to a DList struct
 * \param *element the element after which the insertion should occur. When
 *     inserting into an empty list, element may point anywhere, but should
 *     be NULL to avoid confusion.
 *
 * \return 0 if inserting the element is successful, or -1 otherwise.
 ****************************************************************/
int dlist_ins_next(DList *list, DListElmt *element, const void *data);


/*************************************************************//**
 * dlist_ins_prev: Inserts an element just before element in the list.
 *
 * The new element contains a pointer to data, so the memory referenced by
 * data should remain valid as long as the element remains in the list. It is
 * the responsibility of the caller to manager the storage associated with
 * data.
 * Complexity: O(1)
 *
 * \param *list pointer to a DList struct
 * \param *element the element before which the insertion should occur. When
 *     inserting into an empty list, element may point anywhere, but should
 *     be NULL to avoid confusion.
 *
 * \return 0 if inserting the element is successful, or -1 otherwise.
 ****************************************************************/
int dlist_ins_prev(DList *list, DListElmt *element, const void *data);


/*************************************************************//**
 * dlist_remove: Removes the element specified as element from `list`.
 *
 * Upon return, `data` points to the data stored in the element that was
 * removed. It is the responsibility of the called to manager the storage
 * associated with the data.
 * Complexity: O(1)
 *
 * \param *list pointer to a DList struct
 * \param *element pointer to the element to be removed
 * \param **data pointer to the pointer where a reference to the data from
 *     the removed element will be stored.
 *
 * \return 0 if removing the element is successful, or -1 otherwise.
 ****************************************************************/
int dlist_remove(DList *list, DListElmt *element, void **data);


/*************************************************************//**
 * dlist_size: Macro that evaluates to the number of elements in `list`.
 *
 * \param *list pointer to a DList struct
 *
 * \return Number of elements in the list.
 ****************************************************************/
#define dlist_size(list) ((list)->size)


/*************************************************************//**
 * dlist_head: Evaluates to the elements at the head of `list`.
 * Complexity: O(1)
 *
 * \param *list Pointer to a DList struct
 *
 * \return Element at the head of the list.
 ****************************************************************/
#define dlist_head(list) ((list)->head)


/*************************************************************//**
 * dlist_tail: Evaluates to the elements at the tail of `list`.
 * Complexity: O(1)
 *
 * \param *list Pointer to a DList struct
 *
 * \return Element at the tail of the list.
 ****************************************************************/
#define dlist_tail(list) ((list)->tail)


/*************************************************************//**
 * dlist_is_head: Determines whether `element` is at the head of `list`
 * Complexity: O(1)
 *
 * \param *list Pointer to a DList struct
 *
 * \return 1 if `element` is at the head, or 0 otherwise
 ****************************************************************/
#define dlist_is_head(list, element) ((element) == (list)->head? 1: 0)


/*************************************************************//**
 * dlist_is_tail: Determines whether `element` is at the tail of `list`
 * Complexity: O(1)
 *
 * \param *list Pointer to a DList struct
 *
 * \return 1 if `element` is at the tail, or 0 otherwise
 ****************************************************************/
#define dlist_is_tail(element) ((element)->next == NULL ? 1: 0)


/*************************************************************//**
 * dlist_data: Evaluates to the data stored in the `element` of the list.
 * Complexity: O(1)
 *
 * \param *list Pointer to a DList struct
 *
 * \return Data stored in the element
 ****************************************************************/
#define dlist_data(element) ((element)->data)


/*************************************************************//**
 * dlist_next: Evaluates to the element following `element`.
 * Complexity: O(1)
 *
 * \param *list Pointer to a DList struct
 *
 * \return Element following the specified element.
 ****************************************************************/
#define dlist_next(element) ((element)->next)


/*************************************************************//**
 * dlist_prev: Evaluates to the element preceding `element`.
 * Complexity: O(1)
 *
 * \param *list Pointer to a DList struct
 *
 * \return Element preceding the specified element.
 ****************************************************************/
#define dlist_prev(element) ((element)->next)


#endif
