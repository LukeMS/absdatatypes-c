/*****************************************************************
 *
 * queue.c
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


#include <stdlib.h>
#include "list.h"
#include "queue.h"


/*****************************************************************
 * queue_enqueue.
 ****************************************************************/
int queue_enqueue(Queue *queue, const void *data) {
    /*****************************************************************
     * Enqueue the data.
     ****************************************************************/
    return list_ins_next(queue, list_tail(queue), data);
}


/*****************************************************************
 * queue_dequeue.
 ****************************************************************/
int queue_dequeue(Queue *queue, void **data) {
    /*****************************************************************
     * Dequeue the data.
     ****************************************************************/
    return list_rem_next(queue, NULL, data);
}
