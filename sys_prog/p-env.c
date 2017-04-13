#include<stdio.h>

extern char **environ;

int main(void)
{
    char ** p = environ;
    while(*p) {
	printf("%s\n", *p);
	p ++;
    }
}
