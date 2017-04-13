/* algorithm reference to
http://faculty.cs.niu.edu/~hutchins/csci241/eval.htm
*/
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<assert.h>
#include<stdbool.h>

#define MAX_EXPR_LEN (1024) /* in bytes */
#define MAX_OPS (100)
#define PARSING_ERR (-1)

static char op_stack[MAX_OPS];
static int op_top = -1;
#define OP_NOT_EMPTY() op_top >= 0
#define OP_PUSH(a) do { op_stack[++op_top] = (a); } while(0)
#define OP_POP() op_top --
#define OP_TOP() ((op_top < 0) ? '\0' : op_stack[op_top])
#define P_OP_STACK() do {			\
	for(int i = 0; i <= op_top ; ++i)	\
	    putchar(op_stack[i]);		\
	putchar('\n');				\
    } while(0)
#define OP_CLEAR() op_top = -1

int pred(char c) {
    int result = 0;
    switch(c) {
    case ')':
	result = 99;
	break;
    case '/':
    case '*':
    case '%':
	result = 3;
	break;
    case '+':
    case '-':
	result = 2;
	break;
    case '(':
	result = 1;
	break;
    default:
	result = -1;
	break;
    }
    return result;
}

bool is_op(char c) {
    bool result = false;
    switch(c) {
    case '+':
    case '-':
    case '*':
    case '%':
    case '/':
	result = true;
	break;
    }
    return result;
}

int postfix_expr(char * dest, const char * src)
{
    const char *s = src;
    char *d = dest;
    char c = '\0';
    while('\0' != (c = *s)) {
	if(isdigit(c)) {
	    *d = *s;
	    d++; s++;
	} else {
	    /* whenever read in an operator, means the last operand has been all read in and place
	       a space here. */
	    *d++ = ' ';
	    /* process operator */
	    switch(c) {
	    case ' ':
		break;
	    case '(':
		OP_PUSH(c);
		break;

	    case ')':
	    {
		while(OP_NOT_EMPTY() && OP_TOP() != '(') {
		    *(d++) = ' '; *(d++) = OP_TOP(); *(d++) = ' ';
		    OP_POP();
		}
		assert(OP_TOP() == '(' || !OP_NOT_EMPTY());
		OP_POP();
	    }
	    break;

	    case '+':
	    case '-':
	    case '*':
	    case '%':
	    case '/':
	    {
		while(OP_NOT_EMPTY() && OP_TOP() != '(' && pred(OP_TOP()) > pred(c)) {
		    *(d++) = ' '; *(d++) = OP_TOP(); *(d++) = ' ';
		    OP_POP();
		}
		OP_PUSH(c);
	    }
	    break;
	    }
	    #ifdef _MY_DEBUG
	    P_OP_STACK();
	    #endif
	    s++;
	}
    }

    /* dump out the rest of stack */
    while(OP_NOT_EMPTY()) {
	if (OP_TOP() == '(') {
	    fprintf(stderr, "postfix_expr() parsing Error %s\n", src);
	    return PARSING_ERR;
	} else {
	    *(d++) = ' '; *(d++) = OP_TOP(); *(d++) = ' ';
	    OP_POP();
	}
    }
    *d = '\0';
    #ifdef _MY_DEBUG
    printf("pexpr: %s\n", dest);
    #endif
}

#define MAX_VAL (2 * MAX_OPS)

static int vstack[MAX_VAL];
static int vtop = -1;
#define V_NOT_EMPTY() vtop >= 0
#define V_TOP() vstack[vtop]
#define V_PUSH(a) do { vstack[++vtop] = (a); } while(0)
#define V_POP() vtop--;
#define P_V_STACK() do {			\
    for(int i = 0; i <= vtop ; ++i)		\
	printf("[%d]", vstack[i]);		\
	putchar('\n');				\
    } while(0)
#define V_CLEAR() vtop = -1

int eval_pexpr(char * pexpr)
{
    char *token = pexpr;
    token = strtok(pexpr, " ");
    while(token != NULL) {
	int len = strlen(token);
	if(is_op(*token)) {
	    int val = 0;
	    int a = V_TOP(); V_POP();
	    int b = V_TOP(); V_POP();

	    /* Now, evaluate ( b op a ) to new val. Note the order of a and b! */
	    switch(*token) {
	    case '+':
		val = b + a;
		break;
	    case '-':
		val = b - a;
		break;
	    case '*':
		val = b * a;
		break;
	    case '/':
		val = b / a;
		break;
	    case '%':
		val = b % a;
		break;
	    }
	    V_PUSH(val);
	} else {
	    int a = atoi(token);
	    V_PUSH(a);
	}
	#ifdef _MY_DEBUG
	P_V_STACK();
	#endif
	token = strtok(NULL, " ");
    }
    if(!(V_NOT_EMPTY())) {
	fprintf(stderr, "eval_pexpr() parsing error: %s\n", pexpr);
    }
    return V_TOP();
}

/* expr: infix expression */
int eval(const char* expr)
{
    static char pexpr[MAX_EXPR_LEN]; /* postfix expression */
    memset(pexpr, 0, sizeof(pexpr));
    if(PARSING_ERR != postfix_expr(pexpr, expr)) {
	return eval_pexpr(pexpr);
    } else {
	fprintf(stderr, "Parsing Error: %s\n", expr);
    }

}

int main(int argc, char *argv[])
{
    memset(op_stack, 0, sizeof(op_stack));
    if(argc < 2) {
	printf("Usage: eval expr1 ...\n");
	return EXIT_SUCCESS;
    }

    for(int j = 1; j < argc; ++ j) {
	int result = 0;
	OP_CLEAR();
	V_CLEAR();
	result = eval(argv[j]);
	printf("%s => %d\n", argv[j], result);
    }
    return EXIT_SUCCESS;
}
