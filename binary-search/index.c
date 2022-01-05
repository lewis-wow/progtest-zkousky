#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int binSearchRec(int arr[], int start, int end, int target) {
    if(start > end) return 0;
    int mid = (start + end) / 2;

    if(arr[mid] == target) return 1;
 
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

int main(void) {

    int arr[3] = {1, 2, 3};
    qsort(arr, 3, sizeof(int), cmp);

    printf("%d", binSearch(arr, 3, 0));
    return 0;
}
