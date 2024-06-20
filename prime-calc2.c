#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

	
	for(int k = 0; k < 1; k++){
		int upperBound = 1000000;
		int arraySize = 1.2 * (upperBound / log(upperBound)); //estimate for the number of primes under x
		int* primes = (int*)malloc(arraySize * sizeof(int));
		//int primes[arraySize];

		primes[0] = 2;
		primes[1] = 3;
		primes[2] = 5;
		primes[3] = 7;
		int primesFound = 4;

		printf ("%d\n", k);


		for (int i = 11; i < upperBound; i+=6){

			if(i % 390625 == 0) { printf ("%d\n", i); }

			int limit = sqrt(i);


			for (int j = 0; i % primes[j] != 0; j++) {
			 	if (primes[j] > limit) {
			 		primes[primesFound] = i;
			 		primesFound ++;
			 		break;
			 	}
			}

			// we don't update limit (=sqrt(i)) because (floor(sqrt(i+2)) - floor(sqrt(i)) < 2) is true for all i/geq 11 (which is all we care about)
			for (int j = 0; (i+2) % primes[j] != 0; j++) {
				//printf ("%d\n", ())
			 	if (primes[j] > limit) {
			 		primes[primesFound] = (i+2);
			 		primesFound ++;
			 		break;
			 	}
			} 
		}
	




		for (int i = 0; i < primesFound; i++) {
			printf ( "%d: ", i+1);
			printf ( "%d\n", primes[i]);
		}

		printf("\nthere are %d primes up to ", primesFound);
		printf("%d\n", upperBound);
		printf("the estimate was %lf\n", 1.2 * (upperBound / log(upperBound)));

    	free(primes);
    }

	return 0;
}