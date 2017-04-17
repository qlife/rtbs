#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_N (64)

/*
R stands for root node, length == 1.
prefix :   {R|#LEFT_SUBTREE|#RIGHT_SUBTREE}
infix:     {#LEFT_SUBTREE|R|#RIGHT_SUBTREE}

build output - postfix seq.
posfix     {#LEFT_SUBTREE|#RIGHT_SUBTREE|R}

This is recursively valid of every subtreej of any binary tree.
*/

void build(int n_nodes, char *s_pre, char *s_infix, char *s_post)
{
    if(n_nodes <= 0) return;
    char *root_p = &s_pre[0];
    size_t p = strchr(s_infix, *root_p) - s_infix;
    build(p, s_pre+1, s_infix, s_post);
    build(n_nodes-p-1, s_pre+p+1, s_infix+p+1, s_post+p);
    s_post[n_nodes-1] = *root_p;
}


int main(void)
{
    char prefix[MAX_N];
    char infix[MAX_N];
    char postfix[MAX_N];

    while(2 == scanf("%s %s", prefix, infix))
    {
	memset(postfix, 0, sizeof(postfix));
	build(strlen(prefix), prefix, infix, postfix);
	printf("%s\n", postfix);
    }
}
