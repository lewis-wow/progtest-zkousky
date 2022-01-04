#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX 100

int loadInput(int arr[], int* used) {

    char deli = 0;
    if(scanf(" %c", &deli) != 1 || deli != '{') {
        printf("Nespravny vstup.\n");
        return 0;
    }

    int num, scanfRes;
    while((scanfRes = scanf(" %d %c", &num, &deli)) != EOF) {
        if(scanfRes != 2 || (deli != ',' && deli != '}')) {
            printf("Nespravny vstup.\n");
            return 0;
        }

        arr[*used] = num;
        *used += 1;

        if(deli == '}') {
            break;
        }   

    }

    return 1;
}

int cmp(const void* a_, const void* b_) {
    int a = *(int*)a_;
    int b = *(int*)b_;

    return (a - b);
}

double avg(int arr[], int used) {
    int sum = 0;
    for(int i = 0; i < used; i++) {
        sum += arr[i];
    }

    return (double)sum / used;
}

double median(int arr[], int used) {
    if(used % 2 == 1) {
        //liche
        return (double)arr[used / 2];
    }

    //sude
    int cr[2] = {
        arr[used / 2 - 1],
        arr[used / 2]
    };

    return (double)avg(cr, 2);
}

int main(void) {

    int a[MAX], aUsed = 0;

    printf("Vstup a:\n");
    if(!loadInput(a, &aUsed)) {
        return 1;
    };
    qsort(a, aUsed, sizeof(int), cmp);


    printf("pouzito: %d\n", aUsed);
    printf("pole: { ");
    for(int i = 0; i < aUsed; i++) {
        printf("%d", a[i]);
        if(i != (aUsed-1)) {
            printf(", ");
        }
    }
    printf(" }\n");
    printf("prumer: %f\n", avg(a, aUsed));
    printf("median: %f\n", median(a, aUsed));

    return 0;
}
