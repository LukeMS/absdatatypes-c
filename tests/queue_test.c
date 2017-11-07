#include "queue.h"
#include <stdio.h>

int main(void)
{
    Queue queue = {0};

    char *data = NULL;

    queue_enqueue(&queue, "1st");
    queue_enqueue(&queue, "2nd");
    queue_enqueue(&queue, "3rd");

    queue_dequeue(&queue, (void **)&data);
    printf("%s\n", data);
    queue_dequeue(&queue, (void **)&data);
    printf("%s\n", data);
    queue_dequeue(&queue, (void **)&data);
    printf("%s\n", data);

    return 0;
}
