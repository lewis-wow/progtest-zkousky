#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
    UKOL:
    https://www.fit-wiki.cz/%C5%A1kola/p%C5%99edm%C4%9Bty/bi-pa1/pa1_zkouska_2015_1_9_0800
*/

typedef struct {
    char** words;
    size_t used;
    size_t size;
} Dictionary;

void initDictionary(Dictionary* d, size_t initSize) {
    d->words = (char**)malloc(sizeof(*(d->words)) * initSize);
    d->size = initSize;
    d->used = 0;
}

void pushDictionary(Dictionary* d, char* word, size_t wordLen) {
    if(d->size == d->used) {
        d->size *= 2;
        d->words = (char**)realloc(d->words, sizeof(*(d->words)) * d->size);
    }

    d->words[d->used] = (char*)malloc(sizeof(char) * wordLen + 1);
    strcpy(d->words[d->used], word);
    d->used += 1;
}

void freeDictionary(Dictionary* d) {
    free(d->words);
    d->words = NULL;
    d->size = d->used = 0;
}

int findDictionary(Dictionary* d, char* word) {
    for(size_t i = 0; i < d->used; i++) {
        if(!strcmp(d->words[i], word)) {
            return i;
        }
    }
    return -1;
}

void pushDictionaryFromTo(Dictionary* d, char* line, int from, int to) {
    char* word = (char*)calloc((to-from) + 1, sizeof(char));
    strncpy(word, line + from, to - from);
    pushDictionary(d, word, to-from);
    free(word);
}

void tokenize(Dictionary* d, char* line) {
    int currentSize = 0;
    int start = 0;

    char* string = line;

    while(*line) {
        currentSize++;
        if(isspace(*line)) {
            pushDictionaryFromTo(d, string, start, currentSize - 1);
            start = currentSize;
        }
        line++;
    }

    pushDictionaryFromTo(d, string, start, currentSize);
}

int checkWord(char* line) {
    while(*line) {
        if((*line < 'a' || *line > 'z') && (*line < 'A' || *line > 'Z')) return 0;
        line++;
    }
    return 1;
}

int main(void) {

    Dictionary dic;
    initDictionary(&dic, 10);

    printf("Slova: \n");
    char* line = NULL;
    size_t size = 0;
    int lineLen = 0;

    while(1) {
        lineLen = getline(&line, &size, stdin);
        if(lineLen == 1 && !strcmp(line, "\n")) break;

        line[lineLen - 1] = '\0';
        if(!checkWord(line)) {
            printf("Nespravny vstup.\n");
            return 1;
        }

        pushDictionary(&dic, line, lineLen);

        lineLen = 0;
        size = 0;
    }

    line = NULL;
    lineLen = 0;
    size = 0;

    printf("Vstup: \n");

    while((lineLen = getline(&line, &size, stdin)) != EOF) {
        line[lineLen - 1] = '\0';

        Dictionary sentence;
        initDictionary(&sentence, 10);
        tokenize(&sentence, line);

        for (size_t i = 0; i < sentence.used; i++) {
            if(findDictionary(&dic, sentence.words[i]) != -1) {
                printf("%s ", sentence.words[i]);
            } else {
                printf("<err>%s</err> ", sentence.words[i]);
            }
        }
        printf("\n");
        freeDictionary(&sentence);
    }
    free(line);

    freeDictionary(&dic);
    return 0;
}
