#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct TItem {
    struct TItem * m_Next;
    char *m_Word;
}TITEM;

TITEM* newItem(const char* string, int from, int to) {
    TITEM* item = (TITEM*)malloc(sizeof(*item));
    item->m_Word = (char*)calloc((to - from) + 1, sizeof(char));
    strncpy(item->m_Word, string + from, to - from);
    item->m_Next = NULL;

    return item;
}
 
TITEM* StringToList(const char* string_) {
    TITEM* before = NULL;
    TITEM* current = NULL;
    TITEM* first = NULL;

    const char* string = string_;

    int currentWordLen = 0;
    int startFrom = 0;

    while(*string) {
        currentWordLen++;

        if(isspace(*string)) {
            current = newItem(string_, startFrom, currentWordLen);
            
            startFrom = currentWordLen;

            if(before) {
                before->m_Next = current;
            } else {
                first = current;
            }

            before = current;
        }

        string++;
    }

    current = newItem(string_, startFrom, currentWordLen);
    if(before) {
        before->m_Next = current;
    } else {
        first = current;
    }

    return first;
}
 
void FreeList (TITEM* List) {
    if(List->m_Next) {
        FreeList(List->m_Next);
    }
    free(List->m_Word);
    free(List);
}

int main(void) {
    TITEM* test = StringToList("Hello, world! It works!");

    TITEM* tmp = test;
    while(tmp) {
        printf("%s\n", tmp->m_Word);
        tmp = tmp->m_Next;
    }

    FreeList(test);

    return 0;
}
