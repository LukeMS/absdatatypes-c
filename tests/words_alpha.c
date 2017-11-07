#include <stdio.h>
#include <stdlib.h>

#include "list.h"


int read_char(FILE *stream) {
    int ch = fgetc(stream);

    if (ch == '\n' || ch == '\t') {
        return ' ';
    }
    return ch;
}


char* read_word(FILE *stream) {
    long start, end;
    start = ftell(stream);
    int ch;

    while ((ch = read_char(stream)) == ' ') {
        start++;
    }
    end = start;
    if (ch == EOF) {
        return NULL;
    }
    while (ch != ' ' && ch != EOF) {
        ch = read_char(stream);
        end++;
    }
    int size = end-start;
    char * word = malloc(size + 1);
    fseek(stream, end-size, SEEK_SET);
    fread(word, 1, size, stream);
    fseek(stream, end+1, SEEK_SET);
    word[size] = 0;
    return word;
}

void words_alpha(List *words) {
    list_init(words, &free);

    FILE *fp;
    char *word = NULL;

    fp = fopen("words_alpha.txt", "r");
    puts("reading");
    for (int i = 0; ; i++) {
        word = read_word(fp);
        if (word == NULL) {
            free(word);
            break;
        } else {
            list_ins_next(words, list_tail(words), word);
        }
    }
    fclose(fp);

    return;
}
