#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int priority;
    void *data;
} HTPQ_node;

typedef struct {
    HTPQ_node *nodes;
    int size;
    int len;
} HTPQ;


int less(HTPQ *tree, int a, int b)
{
    return tree->nodes[a].priority < tree->nodes[b].priority;
}

void exch(HTPQ *tree, int a, int b)
{
    tree->nodes[0] = tree->nodes[a];
    tree->nodes[a] = tree->nodes[b];
    tree->nodes[b] = tree->nodes[0];

    return;
}

/*****************************************************************
 * swim: Bottom-up reheapify.

 * If the heap order is violated because a node's key becomes larger than
 * that node's parents key, then we can make progress toward fixing the
 * violation by exchanging the node with its parent. After the exchange, the
 * node is larger than both its children (one is the old parent, and the
 * other is smaller than the old parent because it was a child of that node)
 * but the node may still be larger than its parent. We can fix that
 * violation in the same way, and so forth, moving up the heap until we reach
 * a node with a larger key, or the root.
 ****************************************************************/
void swim(HTPQ *tree, int k) {
   while (k > 1 && less(tree, k/2, k)) {
      exch(tree, k, k/2);
      k = k/2;
   }
}

void sink(HTPQ *tree, int k) {
   while (2*k <= tree->size) {
      int j = 2*k;
      if (j < tree->size && less(tree, j, j+1)) j++;
      if (!less(tree, k, j)) break;
      exch(tree, k, j);
      k = j;
   }
}

void new_HTPQ(HTPQ **tree, int size)
{
    size += size % 2 ? 1 : 0;
    printf("creating tree with size %d\n", size);
    *tree = malloc(sizeof(**tree));
    (*tree)->nodes = calloc(size, sizeof(*((*tree)->nodes)));
    (*tree)->size = size;
    (*tree)->len = 0;
}

void grow(HTPQ *tree) {
    printf("growing %d -> %d\n", tree->size, tree->size * 2);
    tree->size *= 2;
    realloc(tree->nodes, sizeof(*tree->nodes) * tree->size);
}

void put(HTPQ *tree, int priority, void *data)
{
    tree->len++;
    if ((tree->len + 1) >= tree->size) {
        grow(tree);
    }
    printf("putting p %d at pos %d on tree with size %d\n",
           priority, tree->len, tree->size);
    tree->nodes[tree->len].priority = priority;
    tree->nodes[tree->len].data = data;

    swim(tree, tree->len);
}

void pop(HTPQ *tree, void **data)
{
    if (!tree->len)
    {
        *data = NULL;
        return;
    }
    *data = tree->nodes[tree->len--].data;

    sink(tree, tree->len);

    return;
}

int main(void)
{
    HTPQ *pq = NULL;
    new_HTPQ(&pq, 1);

    put(pq, 38, "38");
    put(pq, 47, "47");
    put(pq,  1, "01");
/*
    put(pq, 46, "46");
    put(pq, 45, "45");
    put(pq, 43, "43");
    put(pq, 42, "42");
    put(pq, 41, "41");
    put(pq, 40, "40");
    put(pq, 39, "39");
    put(pq, 37, "37");
    put(pq, 36, "36");
    put(pq,  2, "02");
    put(pq, 35, "35");
    put(pq, 34, "34");
    put(pq, 33, "33");
    put(pq, 32, "32");
    put(pq, 31, "31");
    put(pq, 30, "30");
    put(pq, 29, "29");
    put(pq, 28, "28");
    put(pq, 27, "27");
    put(pq, 26, "26");
    put(pq, 25, "25");
    put(pq, 44, "44");
    put(pq, 24, "24");
    put(pq, 23, "23");
    put(pq, 22, "22");
    put(pq, 21, "21");
    put(pq, 20, "20");
    put(pq, 19, "19");
    put(pq, 18, "18");
    put(pq, 17, "17");
    put(pq, 16, "16");
    put(pq, 15, "15");
    put(pq, 14, "14");
    put(pq, 13, "13");
    put(pq, 12, "12");
    put(pq, 11, "11");
    put(pq, 10, "10");
    put(pq,  9, "09");
    put(pq,  8, "08");
    put(pq,  7, "07");
    put(pq,  6, "06");
    put(pq,  5, "05");
    put(pq,  4, "04");
    put(pq,  3, "03");
    put(pq, 48, "48");
    put(pq, 49, "49");
*/


    char *data = NULL;

    pop(pq, (void **)&data);
    puts(data);

    pop(pq, (void **)&data);
    puts(data);

    pop(pq, (void **)&data);
    puts(data);

    return 0;
}
