#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "bistree.h"
#include "list.h"
#include "words_alpha.h"

typedef struct BisTreeData_ {
    char *key;
    int  value;
} BisTreeData;


void bistree_destroydata(void *data_) {
    BisTreeData *data = data_;
    free(data->key);
    free(data);
};


int bistree_match(const void *data1, const void *data2) {
    const BisTreeData *data_ptr_1 = data1;
    const BisTreeData *data_ptr_2 = data2;
    return (strcmp((const char *) (data_ptr_1->key),
                   (const char *) (data_ptr_2->key)
                   ));
}


void bistree_newnode(BisTreeData **node, char * key) {
    *node = malloc(sizeof(**node));
    (*node)->key = malloc(sizeof(*key) * (strlen(key) + 1));
    strcpy((*node)->key, key);
}


void bistree_add(BisTree *tree, char * key, int value) {
    BisTreeData *node;
    bistree_newnode(&node, key);
    node->value = value;
    bistree_insert(tree, (const void *)node);
}


int bistree_get(BisTree *tree, char * key) {
    BisTreeData *node;
    bistree_newnode(&node, key);
    printf("bistree_lookup(%s) : %s ",
           key,
           bistree_lookup(tree, (void **)&node) == 0 ? "ok" : "error");
    int v = node->value;
    bistree_destroydata(node);
    return v;
}

int main(void)
{
    BisTree tree;
    bistree_init(&tree, &bistree_match, &bistree_destroydata);

    List words;
    words_alpha(&words);
    int i;
    ListElmt *element;

    puts("adding");
    for (i = 0, element = list_head(&words);
         element != NULL ;
         i++, element=list_next(element)
    ) {
        //printf("add %s %d\n", element->data, i);
        bistree_add(&tree, element->data, i);
    }

    puts("getting");
    for (i = 0, element = list_head(&words);
         element != NULL ;
         i++, element=list_next(element)
    ) {
        assert(bistree_get(&tree, element->data) == i);
    }

    list_destroy(&words);
    bistree_destroy(&tree);


    return 0;
}
