#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

static int a[30];

void foo() {
    printf("%zu\n", sizeof(a));
}

int main(void) {

    static int a[40];

    printf("%zu\n", sizeof(a));
    foo();
    return 0;
}


