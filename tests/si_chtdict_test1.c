#include <assert.h>
#include <stdio.h>

#include "si_chtdict.h"


int main(void) {
    SI_DictData d1 = {.key = "bla"};
    SI_DictData d2 = {.key = "bla"};
    assert(si_chtdict_match((void *)&d1, (void *)&d2) == 1);

    CHTDict dict;
    si_chtdict_new(&dict, 1);

    si_chtdict_add(&dict, "one", 1);
    si_chtdict_get(&dict, "one");
    printf("dict.size%d\n", dict.size);

    si_chtdict_add(&dict, "two", 2);
    printf("dict.size%d\n", dict.size);

    si_chtdict_add(&dict, "three", 3);
    printf("dict.size%d\n", dict.size);

    printf("%d\n", si_chtdict_pop(&dict));
    printf("%d\n", si_chtdict_pop(&dict));
    printf("%d\n", si_chtdict_pop(&dict));


    si_chtdict_destroy(&dict);

    return 0;
}
