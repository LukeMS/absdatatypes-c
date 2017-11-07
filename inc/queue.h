/*****************************************************************
 *
 * queue.h
 *
 * Source: "Mastering Algorithms with C" (1999, p. 105) by Kyle Loudon,
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


#ifndef QUEUE_H
#define QUEUE_H
#include <stdlib.h>
#include "list.h"


/*****************************************************************
 *
 * Implement queues as linked lists.
 *
 ****************************************************************/
typedef List Queue;



/*****************************************************************
 *
 * PUBLIC INTERFACE
 *
 ****************************************************************/


/*************************************************************//**
 * queue_init: Initializes the queue specified by `queue`.
 *
 * This operation must be called for a queue before the queue can be used
 * with any other operation.
 *
 * \param *queue pointer to a `Queue` struct
 * \param *destroy pointer to a function to clear allocated memory for data.
 *     If the queue contains data dynamically allocated using malloc, destroy
 *     should be set to `free` to free the data as the queue is destroyed.
 *     For structured data containing several dynamically allocated members,
 *     destroy should be set to a user-defined function that calls free for
 *     each dynamically allocated member as well as for the structure itself.
 *     For a queue containing data that should not be freed, destroy should be
 *     set to `NULL`.
 * \return None
 ****************************************************************/
// void queue_init(Queue *queue, void (*destroy)(void *data));
#define queue_init list_init


/*************************************************************//**
 * queue_destroy: Destroys the queue specified by `queue`.
 *
 * No other operations are permitted after calling `queue_destroy` unless
 * `queue_init` is called again. The `queue_destroy` operation removes all
 * elements from a queue and calls the function passed as `destroy` to
 * `queue_init` once for each element as it is removed, provided
 * destroy was not set to `NULL`.
 * Complexity: O(n), where n is the number of elements in the queue.
 *
 * \param *queue pointer to a `Queue` struct
 *
 * \return None
 ****************************************************************/
// void queue_destroy(Queue *queue);
#define queue_destroy list_destroy


/*************************************************************//**
 * queue_enqueue: Enqueues an element at the tail `queue`.
 *
 * The new element contains a pointer to `data`, so the memory referenced by
 * `data` should remain valid as long as the element remains in the queue. It
 * is the responsibility of the caller to manage the storage associated with
 * `data`.
 * Complexity: O(1).
 *
 * \param *queue pointer to a `Queue` struct
 * \param *data pointer to the data that will be referenced by the new element
 *
 * \return 0 if enqueuing the element is successful, or –1 otherwise.
 ****************************************************************/
int queue_enqueue(Queue *queue, const void *data);


/*************************************************************//**
 * queue_dequeue: Dequeues an element from the head of `queue`.
 *
 * Upon return, `data` points to the data stored in the element that was
 * dequeued. It is the responsibility of the caller to manage the storage
 * associated with the data.
 * Complexity: O(1).
 *
 * \param *queue pointer to a `Queue` struct
 * \param *data pointer to where the data stored in the element be kept
 *
 * \return 0 if dequeuing the element is successful, or –1 otherwise.
 ****************************************************************/
int queue_dequeue(Queue *queue, void **data);


/*************************************************************//**
 * queue_peek: evaluates to the data stored in the head element of `queue`.
 * Complexity: O(1).
 *
 * \param *queue pointer to a `Queue` struct
 *
 * \return Data stored in the element at the head of the queue, or `NULL` if
 * the queue is empty.
 ****************************************************************/
#define queue_peek(queue)((queue)->head == NULL ? NULL : (queue)->head->data)


/*************************************************************//**
 * queue_size: evaluates to the number of elements in the `queue`
 * Complexity: O(1).
 *
 * \param *queue pointer to a `Queue` struct
 *
 * \return Number of elements in the queue.
 ****************************************************************/
// int queue_size(const Queue *queue);
#define queue_size list_size


#endif
