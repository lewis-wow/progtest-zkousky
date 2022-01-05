#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int rec(unsigned int x,unsigned int y)
{
   if(x+y==0) return 0;
   return x%2 + rec(x/2,y/2) - (y%2);
}

//1 + (1 + (1 + (1 + 0 - 0) - 1) - 0) - 1
int main ( void )
{
  int x,y;
x=rec(4,8);
y=rec(15,5);
printf("%d\n", x);
 printf("%d\n", y);
 printf("%d\n", 2 / 2);

  return 0;
}
