#include <pqueue.h>
#include <stdio.h>

#define TEST_SIZE 50

static void test_insertion(PQueue *pqueue)
{
    pqueue_enqueue(pqueue,  1, "01");
    pqueue_enqueue(pqueue,  2, "02");
    pqueue_enqueue(pqueue, 47, "47");
    pqueue_enqueue(pqueue, 46, "46");
    pqueue_enqueue(pqueue, 45, "45");
    pqueue_enqueue(pqueue, 44, "44");
    pqueue_enqueue(pqueue, 43, "43");
    pqueue_enqueue(pqueue, 42, "42");
    pqueue_enqueue(pqueue, 41, "41");
    pqueue_enqueue(pqueue, 40, "40");
    pqueue_enqueue(pqueue, 39, "39");
    pqueue_enqueue(pqueue, 38, "38");
    pqueue_enqueue(pqueue, 37, "37");
    pqueue_enqueue(pqueue, 36, "36");
    pqueue_enqueue(pqueue, 35, "35");
    pqueue_enqueue(pqueue, 34, "34");
    pqueue_enqueue(pqueue, 33, "33");
    pqueue_enqueue(pqueue, 32, "32");
    pqueue_enqueue(pqueue, 31, "31");
    pqueue_enqueue(pqueue, 30, "30");
    pqueue_enqueue(pqueue, 29, "29");
    pqueue_enqueue(pqueue, 28, "28");
    pqueue_enqueue(pqueue, 27, "27");
    pqueue_enqueue(pqueue, 26, "26");
    pqueue_enqueue(pqueue, 25, "25");
    pqueue_enqueue(pqueue, 24, "24");
    pqueue_enqueue(pqueue, 23, "23");
    pqueue_enqueue(pqueue, 22, "22");
    pqueue_enqueue(pqueue, 21, "21");
    pqueue_enqueue(pqueue, 20, "20");
    pqueue_enqueue(pqueue, 19, "19");
    pqueue_enqueue(pqueue, 18, "18");
    pqueue_enqueue(pqueue, 17, "17");
    pqueue_enqueue(pqueue, 16, "16");
    pqueue_enqueue(pqueue, 15, "15");
    pqueue_enqueue(pqueue, 14, "14");
    pqueue_enqueue(pqueue, 13, "13");
    pqueue_enqueue(pqueue, 12, "12");
    pqueue_enqueue(pqueue, 11, "11");
    pqueue_enqueue(pqueue, 10, "10");
    pqueue_enqueue(pqueue,  9, "09");
    pqueue_enqueue(pqueue,  8, "08");
    pqueue_enqueue(pqueue,  7, "07");
    pqueue_enqueue(pqueue,  6, "06");
    pqueue_enqueue(pqueue,  5, "05");
    pqueue_enqueue(pqueue,  4, "04");
    pqueue_enqueue(pqueue,  3, "03");
    pqueue_enqueue(pqueue, 48, "48");
    pqueue_enqueue(pqueue, 49, "49");

    return;
}

static void test_extraction(PQueue *pqueue)
{
    char *data = NULL;
    for (;;)
    {
        if (pqueue_dequeue(pqueue, (void **)&data))
        {
            break;
        }
        printf("data %s\n", data);
    }

    return;
}

int main(void)
{
    puts("running");
    PQueue pqueue;
    pqueue_init(&pqueue, NULL);

    test_insertion(&pqueue);
    printf("pqueue.size %d\n", pqueue.size);
    test_extraction(&pqueue);
    printf("pqueue.size %d\n", pqueue.size);

    return 0;
}

