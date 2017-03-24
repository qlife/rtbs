/*
 * transpose matrix
 *
 * [3 7 2]  : 1 x 3 matrix
 * [4 ; 7 ; 2] : 3 x 1 matrix
 */

#include<stdio.h>
#include<stdlib.h>

struct elem
{
    int val, row, col;
};

/*
 * Sorting by column index.
 */
int cmp_by_col(const void* a, const void* b)
{
    return ((struct elem*)a)->col - ((struct elem*)b)->col;
}

/*
 * Sorting by row index.
 */
int cmp_by_row(const void* a, const void* b)
{
    return ((struct elem*) a)->row - ((struct elem*)b)->row;
}

/*
 * Printing a mxn matrix. For example, for matrix [3 7 2], u should do
 *
 * dump_matrix(matrix, 1,  3);
 */
void dump_matrix(const struct elem *matrix, int row_count, int col_count)
{
    for(int i = 0; i < row_count; ++ i)
    {
	for(int j = 0; j < col_count; ++ j)
	{
	    printf("%8d", matrix[i*col_count + j].val);
	}
	printf("\n");
    }
}

int main()
{
    int m, n, T;
    struct elem *matrix = NULL;

    scanf("%d", &T);
    while(T--)
    {
	if(2 == scanf("%d %d", &m, &n) && m != 0 && n != 0)
	{
	    matrix = malloc(sizeof(struct elem) * m * n);
	    for(int i = 0; i < m; ++ i)
		for(int j = 0; j < n; ++ j)
		{
		    int idx = i * n + j;
		    scanf("%d", &matrix[idx].val);
		    matrix[idx].row = i;
		    matrix[idx].col = j;
		}

	    qsort(matrix, m * n, sizeof(struct elem), cmp_by_col);
	    /* sort by m-group. Reason: [a_ij]m x n transpose into [a_ji]n x m */
	    for(int i = 0; i < n; ++ i)
	    {
		qsort(&matrix[i*m], m, sizeof(struct elem), cmp_by_row);
	    }
	}
	dump_matrix(matrix, n, m);
	printf("\n");
	free(matrix);
    }
}
