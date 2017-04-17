#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int gcd(int a, int b)
{
    return (b == 0) ? a : gcd(b, a % b);
}

int main(int argc, char *argv[])
{
    int _testcases;
    scanf("%d", &_testcases);
    while(_testcases--) {
	int a, b;
	if(2 == scanf("%d%d", &a, &b)) {
	    int g = gcd(a,b);
	    if(1 ==  g) {
		printf("%d %d are coprime.\n", a, b);
	    } else {
		printf("gcd(%d,%d) == %d\n", a, b, g);
	    }
	}
    }
    return EXIT_SUCCESS;
}
