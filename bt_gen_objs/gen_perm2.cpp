#include<cstdio>
#include<algorithm>

int main(void)
{
    int n, p[10];
    ::scanf("%d", &n);
    for(int i = 0; i < n; ++ i)
	scanf("%d", &p[i]);

    std::sort(p, p+n);

    do {
	for(int i = 0; i < n; i ++)
	    printf("%d ", p[i]);
	printf("\n");
    } while(std::next_permutation(p, p+n));
    return 0;
}
