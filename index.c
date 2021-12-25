#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct EAN {
    char* code;
    int order;
    int times;
} Ean;

Ean createEan(char* code, size_t lineLen, int order) {
    Ean newEan;
    newEan.code = (char*)malloc(lineLen + 1);
    strcpy(newEan.code, code);
    newEan.order = order;
    newEan.times = 1;

    return newEan;
}

typedef struct {
    Ean* data;
    size_t size;
    size_t used;
} EanArray;

void initEanArray(EanArray* arr, size_t initSize) {
    arr->data = (Ean*)malloc(sizeof(*(arr->data)) * initSize);
    arr->size = initSize;
    arr->used = 0;
}

void pushEanArray(EanArray* arr, char* code, size_t lineLen, int* order) {
    if(arr->size == arr->used) {
        arr->size *= 2;
        arr->data = (Ean*)realloc(arr->data, sizeof(*(arr->data)) * arr->size);
    }

    arr->data[arr->used] = createEan(code, lineLen, *order);
    arr->used += 1;

    *order += 1;
}

void freeEanArray(EanArray* arr) {
    for(size_t i = 0; i < arr->used; i++) {
        free(arr->data[i].code);
    }
    free(arr->data);
    arr->data = NULL;
    arr->size = arr->used = 0;
}

int isInEanArray(EanArray* arr, char* line) {
    for(size_t i = 0; i < arr->used; i++) {
        if(!strcmp(arr->data[i].code, line)) {
            return i;
        }
    }
    return -1;
}

/////////////type checking/////////////
int isDigitsOnly(char* line) {
    while(*line) {
        if(!isdigit(*line)) return 0;
        line++;
    }
    return 1;
}

/////////////cmp/////////////
int cmp(const void* a_, const void* b_) {
    Ean* a = (Ean*)a_;
    Ean* b = (Ean*)b_;

    if(b->times == a->times) {
        return (a->order - b->order);
    }
    return b->times - a->times;
}

int readInput(EanArray* arr) {
    char* line = NULL;
    size_t size = 0;
    int used = 0;

    int EAN_ORDER = 0;

    while((used = getline(&line, &size, stdin)) != -1) {
        size_t lineLen = used - 1;
        line[lineLen] = '\0';

        if(lineLen < 5 || lineLen > 100 || !isDigitsOnly(line)) {
            free(line);
            line = NULL;
            printf("Nespravny vstup.\n");
            return 1;
        }

        int index;
        if((index = isInEanArray(arr, line)) != -1) {
            arr->data[index].times += 1;
        } else {
            pushEanArray(arr, line, lineLen, &EAN_ORDER);
        }
        
        free(line);
        line = NULL;
    }

    return 0;
}

int main(void) {
    EanArray arr;
    initEanArray(&arr, 10);

    int res = readInput(&arr);
    if(res == 1) return 1;

    qsort(arr.data, arr.used, sizeof(Ean), cmp);
    
    size_t until = (10 > arr.used ? arr.used : 10);
    for(size_t i = 0; i < until; i++) {
        printf("%s %d\n", arr.data[i].code, arr.data[i].times);
    }

    freeEanArray(&arr);

    return 0;
}
