#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int binarySearchRec(int arr[], int start, int end, int target) {
    if(start > end) return 0;

    int mid = (start + end) / 2;
    if(arr[mid] == target) return 1;

    if(target > arr[mid]) return binarySearchRec(arr, mid + 1, end, target);
    return binarySearchRec(arr, start, mid - 1, target);
}


int binarySearch(int arr[], int arrLen, int target) {
    return binarySearchRec(arr, 0, arrLen, target);
}

int cmp(const void* a_, const void* b_) {
    int a = *(int*)a_;
    int b = *(int*)b_;

    return (a > b) - (a < b);
}

int main(void) {
    int arr[3] = {2, 3, 1};
    qsort(arr, 3, sizeof(int), cmp);

    printf("%d", binarySearch(arr, 3, 0));
    return 0;   
}
