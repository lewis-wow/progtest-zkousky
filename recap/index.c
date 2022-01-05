#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

/////////////////permutations/////////////////
void permuteRec(int arr[], int arrLen, int index) {
    if(index >= arrLen) {
        for(int i = 0; i < arrLen; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        return;
    }

    for(int i = index; i < arrLen; i++) {
        //perform swap
        int tmp = arr[index];
        arr[index] = arr[i];
        arr[i] = tmp;

        //recursively do permutations again of another combination in array
        permuteRec(arr, arrLen, index + 1);
    }
}

void permute(int arr[], int arrLen) {
    permuteRec(arr, arrLen, 0);
}

/////////////////binary search/////////////////
int binSearchRec(int arr[], int start, int end, int target) {
    if(start > end) return -1;

    int mid = (start + end) / 2;
    if(arr[mid] == target) return mid;

    if(target > arr[mid]) return binSearchRec(arr, mid + 1, end, target);
    return binSearchRec(arr, start, mid - 1, target);
}

int binSearch(int arr[], int arrLen, int target) {
    return binSearchRec(arr, 0, arrLen, target);
}

int cmp(const void* a_, const void* b_) {
    int a = *(int*)a_;
    int b = *(int*)b_;

    return (a > b) - (a < b);
}

/////////////////Dynamic 2d array in O(n) for list all items/////////////////
typedef struct {
    int x;
    int y;
} Coords;

Coords newCoords(int x, int y) {
    Coords c;
    c.x = x;
    c.y = y;

    return c;
}

typedef struct {
    Coords** data;
    size_t size;
    size_t used;
    int serialize;
} Array;

void initArray(Array* a, size_t initSize, int serialize) {
    //O(1)
    a->data = (Coords**)malloc(sizeof(*(a->data)) * initSize);
    a->size = initSize;
    a->used = 0;
    a->serialize = serialize;
}

void pushArray(Array* a, Coords item) {
    //O(1)
    if(a->size == a->used) {
        a->size *= 2;
        a->data = (Coords**)realloc(a->data, sizeof(*(a->data)) * a->size);
    }

    if(a->used % a->serialize == 0) {
        a->data[a->used / a->serialize] = (Coords*)malloc(sizeof(Coords) * a->serialize);
    }

    a->data[a->used / a->serialize][a->used % a->serialize] = item;
    a->used += 1;
}

void freeArray(Array* a) {
    //O(n)
    for(size_t i = 0; i < (size_t)ceil((double)a->used / a->serialize); i++) {
        free(a->data[i]);
    }
    free(a->data);
    a->data = NULL;
    a->size = a->used = 0;
}

void printArray(Array* a) {
    //O(n) - 2d array
    for(size_t i = 0; i < a->used; i++) {
        printf("%d-%d ", a->data[i / a->serialize][i % a->serialize].x, a->data[i / a->serialize][i % a->serialize].y);
        if(i % a->serialize == a->serialize - 1) {
            printf("\n");
        }
    }
}

typedef struct {
    int** data;
    size_t size;
    size_t used;
} Array2d;

void initArray2d(Array2d* a, size_t initSize) {
    a->data = (int**)malloc(sizeof(*(a->data)) * initSize);
    a->size = initSize;
    a->used = 0;
}

void pushArray2d(Array2d* a, int* arr, int arrLen) {
    if(a->size == a->used) {
        a->size *= 2;
        a->data = (int**)realloc(a->data, sizeof(*(a->data)) * a->size);
    }
    a->data[a->used] = (int*)malloc(sizeof(int) * arrLen);
    for(size_t i = 0; i < arrLen; i++) {
        a->data[a->used][i] = arr[i];
    }
    a->used += 1;
}

void freeArray2d(Array2d* a) {
    /*for(size_t i = 0; i < a->used; i++) {
        free(a->data[i]);
    }*/
    free(a->data);
    a->data = NULL;
    a->size = a->used = 0;
}

void printArray2d(Array2d* a) {
    printf("[\n");
    for(size_t i = 0; i < a->used; i++) {
        printf("  [");
        for(size_t j = 0; j < sizeof(*(a->data[i])) + 1; j++) {
            printf("%d", a->data[i][j]);
            if(j != sizeof(*(a->data[i]))) {
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
    /////////////////Permutations/////////////////
    printf("\nPermutations: \n");
    int n = 3;
    int arr[3] = {1, 2, 3};
    permute(arr, n);

    /////////////////Binary search/////////////////
    printf("\nBinary search: \n");
    int n2 = 3;
    int arr2[3] = {5, 2, 9};
    qsort(arr2, n2, sizeof(int), cmp);

    printf("%d\n", binSearch(arr2, n2, 3));

    /////////////////string sandbox/////////////////
    printf("\nString sandbox: \n");
    const char* str = "This is String sandbox for progtest.";
    //output -> This is prog sandtest
    char* dst = (char*)calloc((strlen("This is prog sandtest") + 1), sizeof(char));
    strncpy(dst, str, strlen("This is "));
    strncpy(dst + strlen("This is "), str + strlen("This is String sandbox for "), strlen("prog"));
    strncpy(dst + strlen("This is prog"), str + strlen("This is String"), strlen(" sand"));
    strncpy(dst + strlen("This is prog sand"), str + strlen("This is String sandbox for prog"), strlen("test"));
    printf("%s\n", dst);

    /////////////////Dynamic 2d O(n) array/////////////////
    printf("\nDynamic 2d array: \n");
    Array a;
    initArray(&a, 10, 3);
    for(int i = 0; i < 30; i++) {
        pushArray(&a, newCoords(i ,i));
    }

    printArray(&a);

    freeArray(&a);

    /////////////////Dynamic 2d O(n^2) array/////////////////
    Array2d a2d;
    initArray2d(&a2d, 10);
    for(int i = 0; i < 5; i++) {
        int arrInside[5] = {1, 2, 3, 4, 5};
        pushArray2d(&a2d, arrInside, 5);
    }

    printArray2d(&a2d);

    freeArray2d(&a2d);
    return 0;
}
