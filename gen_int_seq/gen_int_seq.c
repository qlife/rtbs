#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define BLK_SZ (1024 * 1024 * 1024)
#define BLK_CNT (UINT_MAX / BLK_SZ)
static unsigned int m[BLK_SZ];

int main(int argc, char *argv[])
{
    FILE* fp = NULL;

    if(argc < 2)
    {
	printf("Usage: %s ofile\n", argv[0]);
	return EXIT_FAILURE;
    }

    fp = fopen(argv[1], "wb");
    unsigned int val = 0;
    for(int j = 0 ; j < BLK_CNT; ++ j)
    {
	for(size_t i = 0; i < BLK_SZ; ++ i)
	{
	    m[i] = val++;
	}
	fwrite(m, sizeof(unsigned int), BLK_SZ, fp);
    }

    fclose(fp);
    return EXIT_SUCCESS;
}
