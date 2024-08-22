#include <stdio.h>

//practice using sprintf()
int main()
{
    int x = 5;
    char c = 'm';
    char str[] = "Hello World";

    char store[30];
    sprintf(store, "2 %d %c %s\n", x, c, str);

    printf("%s|", store);
    
}