#include <stdio.h>
#include "parcel.h"

int main(void)
{
    PQueue parcels;
    pqueue_init(&parcels, &compare_parcel_decreasing, NULL);

    Parcel p;

    //printf("inserting priority %d\n", 5);
    Parcel p1 = {.data=NULL, .priority=5};
    if (put_parcel(&parcels, &p1) != 0)
        return -1;

    //printf("inserting priority %d\n", 10);
    Parcel p2 = {.data=NULL, .priority=10};
    if (put_parcel(&parcels, &p2) != 0)
        return -1;

    //printf("inserting priority %d\n", 3);
    Parcel p3 = {.data=NULL, .priority=3};
    if (put_parcel(&parcels, &p3) != 0)
        return -1;

    //printf("inserting priority %d\n", 7);
    Parcel p4 = {.data=NULL, .priority=7};
    if (put_parcel(&parcels, &p4) != 0)
        return -1;

    //printf("inserting priority %d\n", 1);
    Parcel p5 = {.data=NULL, .priority=1};
    if (put_parcel(&parcels, &p5) != 0)
        return -1;

    while (get_parcel(&parcels, &p) == 0) {
        printf("priority %d, %d parcels left\n", p.priority, parcels.size);

    }

    pqueue_destroy(&parcels);

    return 0;
}
