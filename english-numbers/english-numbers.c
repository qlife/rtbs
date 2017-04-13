#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/*
   Group 1
   one, two, three, ... , nine, ten, eleven, twelve,
   Group 2
   thirteen, fourteen, fifteen, ..., nineteen

   above 20
   (twenty one, twenty two, ...
   thirty one, ...)

   Group 3
   thirty fourty, fifty, sixty, seventy, eighty, ninety

   Group 4
   hundred

   Group 5
   thousand - 10^3

   Group 6 - 10^6
   million

   Group 7 - 10^9
   billion
 */

/*
1424768

one million four hundred twenty four thousand seven hundred sixty eight

1024768

one million twenty four thousand seven hundred sixty eight

*/

#define TRI_DIGITS (3)
#define MAX_IN (12+1) /* 12 digits plus '\0' */
#define MAX_OUT (1024)

void eng_numb(char * dest, const char * src) {
    static char * c1[] = { "zero ", "one ", "two ", "three ", "four ", "five ", "six ", "seven ", "eight ", "nine ", "ten ", "eleven ", "twelve ",
			       "thirteen ", "fourteen ", "fifteen ", "sixteen ", "seventeen ", "eighteen ", "nineteen " };
    static char * c2[] = { "", "", "twenty ", "thirty ", "fourty ", "fifty ", "sixty ", "seventy ", "eighty ", "ninety " };
    static char * hundred = "hundred ";
    /* maximum number to be handled: 999,999,999,999. reason: only up to billion */
    static char * c3[] = { "", "thousand ", "million ", "billion " };

    const char * p_src = src;
    char *p_dest = dest;

    int len = strlen(p_src);
    int q = (len-1) / 3;

    while(len >= 0) {
	char buf[TRI_DIGITS+1];
	int ncpy = 0;
	int val = 0;
	int reminder = len % 3;
	ncpy = reminder ? reminder : TRI_DIGITS;
	memset(buf, 0, sizeof(buf));
	strncpy(buf, p_src, ncpy);
	len = len - ncpy;
	p_src = p_src + ncpy;
	val = atoi(buf);

	while(val > 0) {
	    if(val >= 100) {
		int hundred_digit = val / 100;
		strcpy(p_dest, c1[hundred_digit]);
		p_dest += strlen(c1[hundred_digit]);
		strcpy(p_dest, hundred);
		p_dest += strlen(hundred);
		val = val % 100;
	    } else if(val > 19) {
		int ten_digit = val / 10;
		strcpy(p_dest, c2[ten_digit]);
		p_dest += strlen(c2[ten_digit]);
		val = val % 10;
	    } else {
		strcpy(p_dest, c1[val]);
		p_dest += strlen(c1[val]);
		val = 0;
	    }
	}

	if(q > 0) {
	    strcpy(p_dest, c3[q]);
	    p_dest += strlen(c3[q]);
	    q--;
	}
    }
    *p_dest = '\0';
}

static char dest[MAX_OUT];
int main(int argc, char *argv[])
{
    char buf_in[MAX_IN];

    if(argc < 2) {
	printf("english-numbers ...\n");
	printf("Specify numbers in the arguments.\n");
    }

    for(int i = 1; i < argc; ++i) {
	char *arg = argv[i];
	char *bin = buf_in;
	while(*arg != '\0') {
	    if(isdigit(*arg)) {
		*bin = *arg;
		arg++; bin++;
	    } else {
		arg++;
	    }
	}
	*bin = '\0';
	eng_numb(dest, buf_in);
	printf("%s:\"%s\"\n", argv[i], dest);
    }

    return EXIT_SUCCESS;
}
