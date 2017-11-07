#include "pqueue.h"
/*************************************************************//**
 * Parcel, Parcel_: structure for linked list elements.
 ****************************************************************/
typedef struct Parcel_ {
    void               *data;
    int                priority;
} Parcel;

int get_parcel(PQueue *parcels, Parcel *parcel);

int put_parcel(PQueue *parcels, const Parcel *parcel);


/*
Return Value 1 if key1 > key2, 0 if key1 = key2, and –1 if key1 < key2.

Description Compare key1 with key2, for a priority queue in which large keys have a higher priority.

Complexity O(1)
*/
int compare_parcel_decreasing(const void *key1, const void *key2);

/*
Return Value 1 if key1 < key2, 0 if key1 = key2, and –1 if key1 > key2.

Description Compare key1 with key2, for a priority queue in which smaller keys have a higher priority.

Complexity O(1)
*/
int compare_parcel_increasing(const void *key1, const void *key2);
