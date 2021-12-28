#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
    UKOL:
    https://www.fit-wiki.cz/%C5%A1kola/p%C5%99edm%C4%9Bty/bi-pa1/pa1_zkouska_2018_8_1
*/

int max(const char* str) {
    int strLen = (int)strlen(str);

    int res = 0;
    int depth = 0;

    for(int i = 0; i < strLen; i++) {
        if(str[i] != '(' && str[i] != ')') return -1;
        
        if(str[i] == '(') {
            for(int j = i; j < strLen; j++) {

                if(str[j] == '(') {
                    depth++;
                }

                else if(str[j] == ')') {
                    depth--;
                }

                if(depth < 0) break;

                else if(depth == 0) {
                    if((j - i) > res) {
                        res = j - i + 1;
                    }
                }

            }   
        }

        depth = 0;
    }

    return res;
}

int main(void) {

    assert ( max ("()()") == 4 );   // nejdelsi od indexu 0 po index 3
    assert ( max ("))())") == 2 );  // nejdelsi od indexu 2 po index 3
    assert ( max ("()()()()") == 8 );  // nejdelsi od indexu 0 po index 7
    assert ( max ("(()())()") == 8 );  // nejdelsi od indexu 0 po index 7
    assert ( max (")((((") == 0 );   // nevyskytuje se usek se spravnym uzavorkovanim
    assert ( max (")o(((") == -1 );  // jiny znak

    assert(max("((())()((()))))))))))))))))))()()()()()()()()") == 16);
    assert(max("(((((((()()()") == 6);
    assert(max("(())(())") == 8);
    assert(max("(())((())") == 4);
    assert(max("(())((())()") == 6);
    assert(max("(())((()))") == 10);

    return 0;
}
