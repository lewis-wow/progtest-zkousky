#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*
    UKOL:
    https://www.fit-wiki.cz/%C5%A1kola/p%C5%99edm%C4%9Bty/bi-pa1/pa1_zkouska_2016_25_1
*/

typedef struct TItem {
    struct TItem * m_Next;
    char           m_Digit;
} TITEM;
 
TITEM* createItem(char digit, TITEM * next) {
    TITEM * n = (TITEM*) malloc(sizeof(*n));
    n->m_Digit = digit;
    n->m_Next = next;
    return n;
}
 
void deleteList(TITEM * list) {
    while (list) {
        TITEM * tmp = list;
        list = list->m_Next;
        free(tmp);
    }
}

int convert(char c) {
    return (c - '0');
}

int getLength(TITEM* x, TITEM** start) {
    int len = 0;
    int numberWasInitialized = 0;

    while(x) {
        if(x->m_Digit != '0' || numberWasInitialized) {
            len++;
        }

        //skip 0 at start
        if(x->m_Digit != '0' && !numberWasInitialized) {
            numberWasInitialized = 1;
            *start = x;
        }

        x = x->m_Next;
    }
    return len;
}
 
TITEM * maxOf(TITEM ** x, int nr) {
    TITEM* max = x[0];
    TITEM* maxStart;
    int maxLen = getLength(max, &maxStart);
    TITEM* maxIter = maxStart;

    for(int i = 1; i < nr; i++) {
        TITEM* current = x[i];
        TITEM* currentStart;
        int currentLen = getLength(current, &currentStart);
        TITEM* currentIter = currentStart;

        if(currentLen > maxLen) {
            max = current;
            continue;
        }

        if(currentLen < maxLen) {
            continue;
        }

        while(currentIter) {
            if(convert(currentIter->m_Digit) > convert(maxIter->m_Digit)) {
                max = current;
                break;
            } else if(convert(currentIter->m_Digit) < convert(maxIter->m_Digit)) {
                break;
            }
            currentIter = currentIter->m_Next;
            maxIter = maxIter->m_Next;
        }

    }

    return max;
}

int main(void) {
    TITEM* a = createItem('0', NULL);
    TITEM* tmpA = a;
    a->m_Next = createItem('0', NULL);
    a->m_Next->m_Next = createItem('1', NULL);
    a->m_Next = createItem('1', NULL);
    a->m_Next->m_Next = createItem('4', NULL);

    TITEM* b = createItem('0', NULL);
    TITEM* tmpB = b;
    b->m_Next = createItem('1', NULL);
    b->m_Next->m_Next = createItem('2', NULL);
    b->m_Next->m_Next->m_Next = createItem('0', NULL);

    int n = 2;
    TITEM** arr = (TITEM**)calloc(n, sizeof(TITEM*));
    arr[0] = a;
    arr[1] = b;

    TITEM* max = maxOf(arr, n);
    while(max) {
        printf("%c%s", max->m_Digit, max->m_Next ? " -> " : "");
        max = max->m_Next;
    }

    free(arr);
    deleteList(tmpA);
    deleteList(tmpB);

    return 0;
}
