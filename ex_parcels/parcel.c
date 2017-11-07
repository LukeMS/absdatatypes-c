/*****************************************************************************
*                                                                            *
*  ------------------------------- parcels.c ------------------------------  *
*                                                                            *
*****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parcel.h"
#include "parcels.h"
#include "pqueue.h"


/*****************************************************************************
*                                                                            *
*  ------------------------------ get_parcel ------------------------------  *
*                                                                            *
*****************************************************************************/
int get_parcel(PQueue *parcels, Parcel *parcel) {
    //printf("extracting parcel\n");
    Parcel             *data;
    if (pqueue_size(parcels) == 0)
        /*********************************************************************
        *                                                                    *
        *  Return that there are no parcels.                                 *
        *                                                                    *
        *********************************************************************/
        return -1;
    else {
        if (pqueue_extract(parcels, (void **)&data) != 0)
            /*****************************************************************
            *                                                                *
            *  Return that a parcel could not be retrieved.                  *
            *                                                                *
            *****************************************************************/
            return -1;
        else {
            /*****************************************************************
            *                                                                *
            *  Pass back the highest-priority parcel.                        *
            *                                                                *
            *****************************************************************/
            memcpy(parcel, data, sizeof(Parcel));
            free(data);
        }
    }
    return 0;
}


/*****************************************************************************
*                                                                            *
*  ------------------------------ put_parcel ------------------------------  *
*                                                                            *
*****************************************************************************/
int put_parcel(PQueue *parcels, const Parcel *parcel) {
    Parcel             *data;
    /*************************************************************************
    *                                                                        *
    *  Allocate storage for the parcel.                                      *
    *                                                                        *
    *************************************************************************/
    if ((data = (Parcel *)malloc(sizeof(Parcel))) == NULL)
        return -1;
    /*************************************************************************
    *                                                                        *
    *  Insert the parcel into the priority queue.                            *
    *                                                                        *
    *************************************************************************/
    memcpy(data, parcel, sizeof(Parcel));
    if (pqueue_insert(parcels, data) != 0)
        return -1;
    return 0;
}


/*****************************************************************************
*                                                                            *
*  --------------------- compare_parcel_decreasing ------------------------  *
*                                                                            *
*****************************************************************************/
int compare_parcel_decreasing(const void *p1, const void *p2) {
    int v1 = ((Parcel *) p1)->priority;
    int v2 = ((Parcel *) p2)->priority;

    //printf("comparing %d with %d\n", v1, v2);

    if (v1 > v2) return 1;
    if (v1 < v2) return -1;

    return 0;
}


/*****************************************************************************
*                                                                            *
*  --------------------- compare_parcel_increasing ------------------------  *
*                                                                            *
*****************************************************************************/
int compare_parcel_increasing(const void *p1, const void *p2) {
    int v1 = ((Parcel *) p1)->priority;
    int v2 = ((Parcel *) p2)->priority;

    //printf("comparing %d with %d\n", v1, v2);

    if (v1 < v2) return 1;
    if (v1 > v2) return -1;

    return 0;
}

