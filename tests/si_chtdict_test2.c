#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "si_chtdict.h"
#include "words_alpha.h"


int main(void) {
    SI_DictData d1 = {.key = "bla"};
    SI_DictData d2 = {.key = "bla"};
    assert(si_chtdict_match((void *)&d1, (void *)&d2) == 1);

    CHTDict dict;
    si_chtdict_new(&dict, 370101);

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
        si_chtdict_add(&dict, element->data, i);
    }

    puts("getting");
    for (i = 0, element = list_head(&words);
         element != NULL ;
         i++, element=list_next(element)
    ) {
        assert(si_chtdict_get(&dict, element->data) == i);
    }

    list_destroy(&words);

    si_chtdict_destroy(&dict);

    return 0;
}
