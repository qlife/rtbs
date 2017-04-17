#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

/*
At my Core i7 16GB laptop
test by ./gen N > /dev/null
So this does not count the I/O time in.

N = 7         0.013s
N = 8         0.058s
N = 9         0.354s
N = 10        3.355s
N = 11        43.830s

Consider most of online judge makes the TLE limitation as 3 seconds,
generate any permutation with the size of 10 is infeasible.
*/

void gen_perm(int A[], int n, int cur)
{
    int i, j;
    if(n == cur) {
	for(i = 0; i < n; ++i)
	    printf("%d ", A[i]);
	printf("\n");
    } else {
	for(i = 1; i <= n; ++ i) {
	    bool ok = true;
	    for(j = 0; j < cur; ++j) {
		if(A[j] == i) ok = false;
	    }
		if(ok) {
		    A[cur] = i;
		    gen_perm(A, n, cur+1);
		}

	}
    }
}

#define N (32)
int main(int argc, char * argv[])
{
    int A[N];
    int n = 0;

    if(argc < 2) {
	printf("gen N\n");
	return EXIT_SUCCESS;
    } else {
	n = atoi(argv[1]);
    }
    gen_perm(A, n, 0);
}
