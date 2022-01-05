#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

void permuteRec(int arr[], int arrLen, int index) {
    if(index >= arrLen) {
        for(int i = 0; i < arrLen; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        return;
    }

    for(int i = index; i < arrLen; i++) {
        //swap
        int tmp = arr[i];
        arr[i] = arr[index];
        arr[index] = tmp;

        permuteRec(arr, arrLen, index + 1);

        //swap back
        arr[index] = arr[i];
        arr[i] = tmp;
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
