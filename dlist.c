/*****************************************************************
 *
 * dlist.c
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

#include <stdlib.h>
#include <string.h>

#include "dlist.h"


/*****************************************************************
 *
 * dlist_init
 *
 *****************************************************************/

void dlist_init(DList *list, void (*destroy)(void *data)) {
    /*****************************************************************
    * Initialize the list.
    *****************************************************************/
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;

    return;
}


/*****************************************************************
 *
 * Dlist_destroy
 *
 *****************************************************************/
void dlist_destroy(DList *list) {
    void *data;

    /*****************************************************************
    * Remove each element.
    *****************************************************************/
    while (dlist_size(list) > 0) {
        if (dlist_remove(list, dlist_tail(list), (void **)&data) == 0 &&
            list->destroy != NULL) {
            /*****************************************************************
            * Call a user-defined function to free dynamically allocated
            * data.
            *****************************************************************/
            list->destroy(data);
            }
    }

    /*****************************************************************
    * No operations are allowed now, but clear the structure as a precaution.
    *****************************************************************/
    memset(list, 0, sizeof(DList));

    return;
}


/*****************************************************************
 *
 * dlist_ins_next
 *
 *****************************************************************/
int dlist_ins_next(DList *list, DListElmt *element, const void *data) {
    DListElmt *new_element;

    /*****************************************************************
    * Do not allow a NULL element unless the list is empty.
    *****************************************************************/
    if (element == NULL && dlist_size(list) != 0) {
        return -1;
    }

    /*****************************************************************
    * Allocate storage for the element.
    *****************************************************************/
    if ((new_element = malloc(sizeof(DListElmt))) == NULL) {
        return -1;
    }

    /*****************************************************************
    * Insert the element into the list.
    *****************************************************************/
    new_element->data = (void *)data;


    if (dlist_size(list) == 0) {
        /*****************************************************************
        * Handle insertion when the list is empty.
        *****************************************************************/
        list->head = new_element;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail = new_element;

    } else {
        /*****************************************************************
        * Handle insertion when the list is not empty.
        *****************************************************************/
        new_element->next = element->next;
        new_element->prev = element;

        if (element-> next == NULL) {
            list->tail = new_element;

        } else {
            element->next->prev = new_element;
        }

        element->next = new_element;
    }

    /*****************************************************************
    * Adjust the size of the list to account for the inserted element.
    *****************************************************************/
    list->size++;

    return 0;
}


/*****************************************************************
 *
 * dlist_ins_next
 *
 *****************************************************************/
int dlist_ins_prev(DList *list, DListElmt *element, const void *data) {
    DListElmt *new_element;

    /*****************************************************************
    * Do not allow a NULL element unless the list is empty.
    *****************************************************************/
    if (element == NULL && dlist_size(list) != 0) {
        return -1;
    }

    /*****************************************************************
    * Allocate storage for the element.
    *****************************************************************/
    if ((new_element = malloc(sizeof(DListElmt))) == NULL) {
        return -1;
    }

    /*****************************************************************
    * Insert the element into the list.
    *****************************************************************/
    new_element->data = (void *)data;

    if (dlist_size(list) == 0) {
        /*****************************************************************
        * Handle insertion when the list is empty.
        *****************************************************************/
        list->head = new_element;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail = new_element;

    } else {
        /*****************************************************************
        * Handle insertion when the list is not empty.
        *****************************************************************/
        new_element->next = element;
        new_element->prev = element->prev;

        if (element->prev == NULL) {
            list->head = new_element;

        } else {
            element->prev->next = new_element;
        }

        element->prev = new_element;
    }

    /*****************************************************************
    * Adjust the size of the list to account for the inserted element.
    *****************************************************************/
    list->size++;

    return 0;
}


/*****************************************************************
*
* list_rem_next
*
*****************************************************************/
int dlist_remove(DList *list, DListElmt *element, void **data) {
    /*****************************************************************
    * Do not allow a NULL element or removal from an empty list.
    *****************************************************************/
    if (element == NULL || dlist_size(list) == 0) {
        return -1;
    }

    /*****************************************************************
    * Remove the element from the list.
    *****************************************************************/
    *data = element->data;

    if (element == list->head) {
        /*****************************************************************
        * Handle removal from the head of the list.
        *****************************************************************/
        list->head = element->next;

        if (list->head == NULL) {
            list->tail = NULL;

        } else {
            element->next->prev = NULL;
        }

    } else {
        /*****************************************************************
        * Handle removal from somewhere other than the head.
        *****************************************************************/
        element->prev->next = element->next;

        if (element->next == NULL) {
            list->tail = element->prev;

        } else {
            element->next->prev = element->prev;
        }

    }

    /*****************************************************************
    * Free the storage allocated by the abstract datatype.
    *****************************************************************/
    free(element);

    /*****************************************************************
    * Adjust the size of the list to account for the removed element.
    *****************************************************************/
    list->size--;

    return 0;
}
