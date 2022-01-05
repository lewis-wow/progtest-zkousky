#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

void permuteRec(int arr[], int arrLen, int index) {
    if(index >= arrLen) {
        for(int i = 0; i < arrLen; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        return;
    }

    for(int i = index; i < arrLen; i++) {
        int tmp = arr[index];
        arr[index] = arr[i];
        arr[i] = tmp;

        permuteRec(arr, arrLen, index + 1);

        arr[i] = arr[index];
        arr[index] = tmp;
    }
}

void permute(int arr[], int arrLen) {
    permuteRec(arr, arrLen, 0);
}

int main(void) {
    int arr[3] = {1, 2, 3};
    permute(arr, 3);
    return 0;
}
