#include<stdio.h>

#define LIST_LEN (25)
#define TEST_CASES_LEN (5)

int primes[LIST_LEN] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
		  41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

struct test_case {
    int val;
    int idx;
} c[TEST_CASES_LEN] = {
    { 2, 0,}, { 73, 20, }, { 83, 22, }, { 11, 4, }, {41, 12},
};

int do_search(int[], int);

int main()
{
    for(int j = 0; j < TEST_CASES_LEN; ++j)
    {
	int result = do_search(primes, c[j].val);
	if (result != c[j].idx)	{
	    printf("Error: test case primes %d expected %d result %d\n",
		   c[j].val, c[j].idx, result);
	}
    }
}

int do_search(int array[], int target)
{
    int min = 0;
    int max = LIST_LEN - 1;
    int guess = 0;

    if (max < min)
    {
	return -(min + 1);
    }


    while(min <= max)
    {
	/*
	   This below line is buggy.
	   guess = (min + max) / 2;

	   Please see the dicussion of the articles about how we compute the guess value:
	   https://research.googleblog.com/2006/06/extra-extra-read-all-about-it-nearly.html
	*/

	guess = ((unsigned int)min + (unsigned int)max) >> 1;
	int temp = array[guess];

	if(temp < target) {
	    min = guess + 1;
	} else if(temp > target) {
	    max = guess - 1;
	} else {
	    return guess;
	}

    }
    return -(min + 1);
}
