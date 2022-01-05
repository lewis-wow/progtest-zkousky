#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int rec2(char* a) {
    return (a[0] && a[1]) ? 1 + rec2(a+2) : 0;
}
 
void rec(char* a) {
    a[rec2(a)]=0;
}

int main(void) {
    char a[7] = "abcdef";
    rec(a);
    printf("%s\n", a);
    return 0;
}
