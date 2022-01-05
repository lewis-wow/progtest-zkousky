#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
    int* data;
    size_t size;
    size_t used;
} Array;

void initArray(Array* a, size_t initSize) {
    a->data = (int*)malloc(sizeof(int) * initSize);
    a->size = initSize;
    a->used = 0;
}

void pushArray(Array* a, int el) {
   if(a->size == a->used) {
        a->size *= 2;
        a->data = (int*)realloc(a->data, sizeof(int) * a->size);
    }
    a->data[a->used] = el;
    a->used += 1;
}

typedef struct {
    Array* data;
    size_t size;
    size_t used;
} Array2d;

void initArray2d(Array2d* a, size_t initSize) {
    a->data = (Array*)malloc(sizeof(Array) * initSize);
    a->size = initSize;
    a->used = 0;
}

void pushArray2d(Array2d* a, Array arr) {
    if(a->size == a->used) {
        a->size *= 2;
        a->data = (Array*)realloc(a->data, sizeof(Array) * a->size);
    }
    a->data[a->used] = arr;
    a->used += 1;
} 

void freeArray2d(Array2d* a) {
    for(size_t i = 0; i < a->used; i++) {
        free(a->data[i].data);
    }
    free(a->data);
    a->data = NULL;
    a->size = a->used = 0;
} 

void printArray2d(Array2d* a) {
    printf("[\n");
    for(size_t i = 0; i < a->used; i++) {
        printf("   [");
        for(size_t j = 0; j < a->data[i].used; j++) {
            printf("%d", a->data[i].data[j]);
            if(j != a->data[i].used - 1) {
                printf(", ");
            }
        }
        printf("]");
        if(i != a->used - 1) {
            printf(",");
        }
        printf("\n");
    }
    printf("]\n");
}

int main(void) {

    Array2d mainArr;
    initArray2d(&mainArr, 10);

    for(int i = 0; i < 3; i++) {
        Array inside;
        initArray(&inside, 10);

        for(int j = 0; j < 10; j++) {
            pushArray(&inside, j);
        }
        pushArray2d(&mainArr, inside);
    }

    printArray2d(&mainArr);

    freeArray2d(&mainArr);
    return 0;
}
