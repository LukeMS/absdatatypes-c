/*****************************************************************************
*                                                                            *
*  ------------------------------- pqueue.h -------------------------------  *
*                                                                            *
*****************************************************************************/
#ifndef PQUEUE_H
#define PQUEUE_H
#include "heap.h"
/*****************************************************************************
*                                                                            *
*  Implement priority queues as heaps.                                       *
*                                                                            *
*****************************************************************************/
typedef Heap PQueue;
/*****************************************************************************
*                                                                            *
*  --------------------------- Public Interface ---------------------------  *
*                                                                            *
*****************************************************************************/


/*
Return Value None.

Description Initializes the priority queue specified by pqueue. This operation
must be called for a priority queue before it can be used with any other opera
tion. The compare argument is a function used by various priority queue operations in maintaining the priority queue’s heap property. This function should return 1 if key1 > key2, 0 if key1 = key2, and –1 if key1 < key2 for a priority queue in which large keys have a higher priority. For a priority queue in which smaller keys have a higher priority, compare should reverse the cases that return 1 and –1. The destroy argument provides a way to free dynamically allocated data when pqueue_destroy is called. For example, if the priority queue contains data dynamically allocated using malloc, destroy should be set to free to free the data as the priority queue is destroyed. For structured data containing several dynamically allocated members, destroy should be set to a user-defined function that calls free for each dynamically allocated member as well as for the structure itself.
For a priority queue containing data that should not be freed, destroy should be set to NULL.

Complexity O(1)

void pqueue_init(PQueue *pqueue, int (*compare)(const void *key1, const void *key2), void (*destroy)(void *data));
*/
#define pqueue_init heap_init


/*
Return Value None.
Description Destroys the priority queue specified by pqueue. No other opera-
tions are permitted after calling pqueue_destroy unless pqueue_init is called again.
The pqueue_destroy operation extracts all elements from a priority queue and calls
the function passed as destroy to pqueue_init once for each element as it is
extracted, provided destroy was not set to NULL.
Complexity O(n), where n is the number of elements in the priority queue.

void pqueue_destroy(PQueue *pqueue);
*/
#define pqueue_destroy heap_destroy


/*
Return Value 0 if inserting the element is successful, or –1 otherwise.
Description Inserts an element into the priority queue specified by pqueue.
The new element contains a pointer to data, so the memory referenced by data
should remain valid as long as the element remains in the priority queue. It is the
responsibility of the caller to manage the storage associated with data.
Complexity O(lg n), where n is the number of elements in the priority queue.

int pqueue_insert(PQueue *pqueue, const void *data);
*/
#define pqueue_insert heap_insert

/*
Return Value 0 if extracting the element is successful, or –1 otherwise.

Description Extracts the element at the top of the priority queue specified by
pqueue. Upon return, data points to the data stored in the element that was
extracted. It is the responsibility of the caller to manage the storage associated
with the data.

Complexity O(lg n), where n is the number of elements in the priority queue.

int pqueue_extract(PQueue *pqueue, void **data);
*/
#define pqueue_extract heap_extract
#define pqueue_peek(pqueue) ((pqueue)->tree == NULL ? NULL : (pqueue)->tree[0])
#define pqueue_size heap_size
#endif
