#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//  [1, 2, 3, 4, 5]
int binarySearchRec(int arr[], int start, int end, int target) {
    if(start > end) return -1;

    int mid = (end + start) / 2;
    if(arr[mid] == target) return mid;

    if(target > arr[mid]) return binarySearchRec(arr, mid + 1, end, target);
    return binarySearchRec(arr, start, mid - 1, target);
}

int binarySearch(int arr[], int size, int target) {
    return binarySearchRec(arr, 0, size, target);
}

int cmp(const void* a_, const void* b_) {
    int a = *(int*)a_;
    int b = *(int*)b_;

    return (a > b) - (a < b); 
}

int doubleEpsilon(double a, double b) {
    double epsilon = 5e-5;

    if(fabs(a - b) < epsilon) return 0;
    if(a > b) return 1;
    return -1;
}

int main(void) {

    int arr[456];
    for(int i = 1; i < 456; i++) {
        arr[i] = i;
    }
    int arrSize = sizeof(arr)/sizeof(int);
    qsort(arr, arrSize, sizeof(int), cmp);

    //print the array
    /*printf("[");
    for(int i = 0; i < arrSize; i++) {
        printf("%d", arr[i]);
        if(i != arrSize - 1) {
            printf(", ");
        }
    }
    printf("]\n");*/

    printf("%d\n", binarySearch(arr, arrSize, 4));
    printf("%d\n", doubleEpsilon(3.3333333333, 3.33353333332));

    const char* str = "Hello world, how are you?";
    //splice -> world
    char dest[6];
    strncpy(dest, str + 6, 5);
    printf("%s\n", dest);

    const char* str2 = "Hello world, how are you?";
    //splice -> world are
    char dest2[10] = {0}; 
    strncpy(dest2, str2 + 6, 5);
    strncpy(dest2 + 5, str2 + 6 + 5 + 5, 4);
    printf("%s\n", dest2);

    const char* str3 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //splice -> ACEGIKMOQSUWY
    char dest3[15] = {0}; 
    for(int i = 0; i < 14; i++) {
        strncpy(dest3 + i, str3 + 2 * i, 1);
    }
    printf("%s\n", dest3);

    const char* str4 = "Bunny";
    //result -> Bunynynynynynny
    char dest4[16] = {0}; 
    strncpy(dest4, str4, 2);
    for(int i = 2; i < 10 + 2; i+=2) {
        strncpy(dest4 + i, str4 + 3, 2);
    }
    strncpy(dest4 + 10 + 2, str4 + 2, 3);
    printf("%s\n", dest4);

    return 0;
}
