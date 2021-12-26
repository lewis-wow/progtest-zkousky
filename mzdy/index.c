#include <stdio.h>
#include <stdlib.h>

/*
    UKOL:
    https://www.fit-wiki.cz/%C5%A1kola/p%C5%99edm%C4%9Bty/bi-pa1/pa1_zkouska_2018_8_1
*/

int charToIndex(char c) {
    return (c - 'A');
}

int readBrackets(char tmp) {
    char bracket;
    if(scanf(" %c", &bracket) != 1 || bracket != tmp) {
        return 0;
    }

    return 1;
}

int readWages(double* arr) {

    if(!readBrackets('{')) {
        printf("Nespravny vstup.\n");
        return 0;
    }

    int scanfRes;
    char delim, region;
    double val;

    while((scanfRes = scanf(" %lf %c %c", &val, &region, &delim)) != EOF) {
        if(scanfRes != 3 || region < 'A' || region > 'Z') {
            printf("Nespravny vstup.\n");
            return 0;
        }

        if(delim != ',' && delim != '}') {
            printf("Nespravny vstup.\n");
            return 0;
        }

        arr[charToIndex(region)] = val; 
        if(delim == '}') return 1;
    }

    return 1;
}

int readQuery(double* arr, int* used) {
    scanf(" "); //prevent space on very begging!

    char key;
    double sum = 0;
    int qLen = 0;

    while((key = getchar())) {
        if((key != ' ' && key != '\n' && (key < 'A' || key > 'Z')) || qLen > 81) {
            printf("Nespravny vstup.\n");
            return 0;
        }

        if(key == ' ' || key == '\n') {
            if(qLen == 0) {
                printf("N/A\n");
            } else {
                printf("= %lf, %d\n", sum, qLen);
                printf("= %lf\n", (double)sum / qLen);
            }
            sum = 0;
            qLen = 0;
            for(int i = 0; i < ('Z' - 'A'); i++) {
                used[i] = 0;
            }
        } else {
            int index = charToIndex(key);
            if(!used[index]) {
                sum += arr[index];
                qLen++;
                used[index] = 1;
            }
        }
    }

    return 1;
}

int main(void) {

    double data['Z' - 'A'] = {0};
    int used['Z' - 'A'] = {0};

    printf("Mzdy: \n");
    if(!readWages(data)) {
        return 1;
    }

    printf("Dotazy: \n");
    if(!readQuery(data, used)) {
        return 1;
    }

    return 0;
}
