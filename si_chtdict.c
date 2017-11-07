#include <assert.h>
//#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "chtbl.h"
#include "hashpjw.h"

#include "si_chtdict.h"


int si_chtdict_hash(const void *data_, int buckets)
{
    const SI_DictData *data = data_;
    return (int)(hashpjw(data->key, buckets));
}


int si_chtdict_match(const void *data1, const void *data2) {
    const SI_DictData *dict_data_ptr_1 = data1;
    const SI_DictData *dict_data_ptr_2 = data2;
    int res = !(bool)(strcmp(
        (const char *) (dict_data_ptr_1->key),
        (const char *) (dict_data_ptr_2->key)
    ));

    return res;
}


void si_chtdict_new_node(SI_DictData **node, char * key) {
    *node = malloc(sizeof(**node));
    (*node)->key = malloc(sizeof(*key) * (strlen(key) + 1));
    strcpy((*node)->key, key);
}


void si_chtdict_destroy_data(void *data_) {
    SI_DictData *data = data_;
    free(data->key);
    free(data);
}


void si_chtdict_add(CHTDict *dict, char * key, int value) {
    SI_DictData *node;
    si_chtdict_new_node(&node, key);
    node->value = value;
    chtbl_insert(dict, (const void *)node);
}


int si_chtdict_get(CHTDict *dict, char * key) {
    SI_DictData *match, *match_ref;
    si_chtdict_new_node(&match, key);
    match_ref = match;
    chtbl_lookup(dict, (void **)&match);
    int v = match->value;
    si_chtdict_destroy_data(match_ref);
    return v;
}

int si_chtdict_pop(CHTDict *dict)
{
    void *data = NULL;

    if (!chtbl_pop(dict, &data))
    {
        return ((SI_DictData *)data)->value;
    }
    return -1;
}


void si_chtdict_new(CHTDict *dict, int size) {
    chtbl_init(dict, size, &si_chtdict_hash, &si_chtdict_match,
               &si_chtdict_destroy_data);
}
