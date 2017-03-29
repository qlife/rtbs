#include<stdio.h>
#include<stdlib.h>

int cmp(const void* a, const void* b)
{
    return (*(int*)a) - (*(int*)b);
}

int main()
{
    int varr[10] = {1, 1, -3, 2, 1, 6, 8, 9, 5, 7};
    /* Try different values: 1, 2, 4, ... etc. And see how the two pointers runs */
    int target = 1;
    qsort(&varr, sizeof(varr)/sizeof(int), sizeof(int), cmp);

    int start, end, len;
    start = 0;
    len = sizeof(varr) / sizeof(int);
    end = len - 1;
    printf("Target %d\n", target);
    printf("Sorted input array {");
    for(int j = 0; j < len; ++j)
    {
	printf("%4d", varr[j]);
    }
    printf("}\n");

    while(start < end)
    {
	int sum = varr[start] + varr[end];
	printf("(%d, %d) -> %d\n", varr[start], varr[end], sum);

	if(sum == target) {
	    printf("Found %d and %d\n", varr[start], varr[end]);
	    break;
	} else if (sum < target) {
	    start ++;
	} else {
	    end --;
	}
    }
    return 0;
}
