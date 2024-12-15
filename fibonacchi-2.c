#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define ONE_OVER_GOLDEN_RATIO (float)0.6943
#define TRUE 1
#define FALSE 0




void add(uint64_t *a, uint64_t *b, uint size) {
	/* takes in two numbers of size bytes and adds them. the result is put into a, b is unaffected */
	/* a number is stores with the least significant long first */


	for(int i=0; i<size-1; i++) {

		if(*b > UINT64_MAX - *a) /* checking for overflow */
			(*(a+1))++;
		*a += *b;

		a++;
		b++;
	}

	/* do the last one seperately (since no overflow) */
	*a += *b;
}


void print_number(uint64_t *a, uint64_t size, int show_boundaries) {
	if(show_boundaries) { /* debug mode */
		for(int i=0; i<size; i++)
			printf("%016llx ", a[size-i-1]);
		printf("\n");
	} else { /* normal mode */
		while(a[size-1] == 0) size--;
		printf("%llx", a[size-1]);
		for(int i=1; i<size; i++)
			printf("%016llx", a[size-i-1]);
		printf("\n");
	}
}



uint longs_needed(unsigned int n) {
	/*
	for f_1, it takes one bit
	for f_2, it takes one bit
	for every n, f_n+1 >= f_n
	for any f_n+2, it takes at most f_n+1

	ehh I dunno, because it's approximately exponential, we can let the space grow linearly
	*/

	// return n/92+1;

	uint bits_needed = (int)(ONE_OVER_GOLDEN_RATIO*(float)n) + 1;
	return (bits_needed >> 6) + 1;
}




uint64_t *fibonacchi(unsigned int n) {
	/* returns the nth fibonacchi number */

	/* size of the number <2^n
	so n/8 is enough
	*/



	uint num_units = longs_needed(n);

	uint64_t a_array[num_units];
	uint64_t b_array[num_units];
	uint64_t *a = a_array;
	uint64_t *b = b_array;

	for(int i=1; i<num_units; i++) {
		a[i] = 0;
		b[i] = 0;
	}
	a[0] = 1;
	b[0] = 1;


	for(int i=2; i<=n; i++) {
		add(a, b, longs_needed(i));

		uint64_t *buffer = b;
		b = a;
		a = buffer;
	}



	uint64_t *output = malloc(num_units*sizeof(*output));
	memcpy(output, b, num_units*sizeof(*output));
	return output;
}




int main(int argc, char *argv[]) {
	int print_index = TRUE;
	int show_boundaries = FALSE;

	if(argc == 3 && strcmp(argv[2], "plain") == 0) {
		print_index = FALSE;
	} else if(argc == 3 && strcmp(argv[2], "debug") == 0) {
		show_boundaries = TRUE;
	} else if(argc != 2) {
		printf("print a number for which you want, or a range by using a hyphen in between\n");
		return 0;
	}

	int seen_hyphen = -1;
	for(int i=0; i<sizeof(argv[1]); i++)
		if(argv[1][i] == '-') {
			seen_hyphen = i;
			argv[1][i] = '\0'; /* like this, we split the string into two strings to use atoi() on */
			break;
		}

	unsigned long *number;
	unsigned int n = atoi(argv[1])-1;
	if(seen_hyphen == -1) { /* singular number */
		number = fibonacchi(n);
		if(print_index) printf("%d:\t", n+1);
		print_number(number, longs_needed(n), show_boundaries);
	} else { /* range */
		unsigned int end_range = atoi(argv[1] + seen_hyphen + 1) - 1;
		for(int m=n; m<=end_range; m++) {
			number = fibonacchi(m);
			if(print_index) printf("%d:\t", m+1);
			print_number(number, longs_needed(m), show_boundaries);
		}
	}




	return 0;
}