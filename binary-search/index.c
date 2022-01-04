#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

    printf("%d", binarySearch(arr, arrSize, 4));
    return 0;
}
