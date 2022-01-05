#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>

typedef struct {
    char** keywords;
    size_t size;
    size_t used;
} MagicKeywords;

void initMagicKeywords(MagicKeywords* m, size_t initSize) {
    m->keywords = (char**)malloc(sizeof(*(m->keywords)) * initSize);
    m->size = initSize;
    m->used = 0;
}

void pushMagicKeywords(MagicKeywords* m, char* line, int start, int end) {
    if(m->size == m->used) {
        m->size *= 2;
        m->keywords = (char**)realloc(m->keywords, sizeof(*(m->keywords)) * m->size);
    }
    m->keywords[m->used] = (char*)calloc((end - start + 1), sizeof(char));
    strncpy(m->keywords[m->used], line + start, end - start);
    m->used += 1;
}

void freeMagicKeywords(MagicKeywords* m) {
    for(size_t i = 0; i < m->used; i++) {
        free(m->keywords[i]);
    }
    free(m->keywords);
    m->keywords = NULL;
    m->size = m->used = 0;
}

void xorSwap(char* x, char* y) {
    *x = (ptrdiff_t)*x^(ptrdiff_t)*y^(ptrdiff_t)((*y=*x));
}

void permute(MagicKeywords* m, int index) {

    if(index >= m->used) {
        printf("> ");
        for(size_t i = 0; i < m->used; i++) {
            printf("%s ", m->keywords[i]);
        }
        printf("\n");
        return;
    }

    for(size_t i = index; i < m->used; i++) {
        char* tmp = m->keywords[index];
        m->keywords[index] = m->keywords[i];
        m->keywords[i] = tmp;

        permute(m, index + 1);

        m->keywords[i] = m->keywords[index];
        m->keywords[index] = tmp;
    }
    
}

void shuffleMagicKeywords(MagicKeywords* m) {
    permute(m, 0);
}

void tokenize(MagicKeywords* m, char* line) {
    char* string = line;
    int start = 0, end = 0;
    int wasSpaceBefore = 1;

    while(*line) {

        if(isspace(*line)) {
            if(!wasSpaceBefore) {
                pushMagicKeywords(m, string, start, end);
                wasSpaceBefore = 1;
            }
            start = end + 1;
        } else {
            wasSpaceBefore = 0;
        }

        end++;
        line++;
    }
    
    pushMagicKeywords(m, string, start, end);
}

int main(void) {

    char* line = NULL;
    int lineLen = 0;
    size_t size = 0;

    MagicKeywords magic;
    initMagicKeywords(&magic, 10);

    printf("Vstup:\n");
    lineLen = getline(&line, &size, stdin);
    line[lineLen - 1] = '\0';

    tokenize(&magic, line);

    shuffleMagicKeywords(&magic);

    free(line);
    freeMagicKeywords(&magic);
    return 0;
}
