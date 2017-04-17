#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define N (100)

void gen_subset(bool B[], int n, int cur)
{
    if(cur == n) {
	printf("{ ");
	for(int j = 0; j < n; ++j) {

	    if(B[j]) {
		printf("%d ", j);
	    }
	}
	printf(" }\n");
    } else {
	B[cur] = false;
	gen_subset(B, n, cur+1);
	B[cur] = true;
	gen_subset(B, n, cur+1);
    }
}

int main(int argc, char* argv[])
{
    if(argc < 2) {
	printf("gen_subset N\n");
	return EXIT_SUCCESS;
    }

    /* generate subset from A */
    int n = N;
    bool B[N] = { false };
    int x = atoi(argv[1]);
    n = (x <= N) ? x : N;
    gen_subset(B, n, 0);
}
