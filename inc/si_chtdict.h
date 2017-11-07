#ifndef DICT_H
#define DICT_H

#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "chtbl.h"
#include "hashpjw.h"


typedef CHTbl CHTDict;

typedef struct SI_DictData_ {
    char *key;
    int  value;
} SI_DictData;


int si_chtdict_hash(const void *data_, int buckets);

int si_chtdict_match(const void *data1_, const void *data2_);

#define si_chtdict_destroy chtbl_destroy

void si_chtdict_add(CHTDict *dict, char * key, int value);

int si_chtdict_get(CHTDict *dict, char * key);

int si_chtdict_pop(CHTDict *dict);

void si_chtdict_new(CHTDict *dict, int size);
