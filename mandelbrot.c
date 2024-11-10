/*
	five months later, I look back at this, and realise
 	that I've seen (though I haven't tried it) that
  	there is actually a standardlibrary of complex
   	numbers.... ehh, the implementation here wasn't
    	too complicated a anyway :3
*/

#include <math.h>
#include <stdio.h>


struct complex {
	float r;
	float i;
};


struct complex square(struct complex z) {
	float routput = z.r*z.r - z.i*z.i;
	float ioutput = 2*z.r*z.i;

	struct complex output = {routput, ioutput};
	return output;
}


struct complex add(struct complex z, struct complex w) {
	struct complex output = {z.r + w.r, z.i + w.i};
	return output;
}


float abso(struct complex z) {
	float output = sqrt(z.r*z.r + z.i*z.i);
	return output;
}


int check(struct complex c){
	struct complex z = {0, 0};

	for(int i=0; i<25; i++) {
		z = add(square(z), c);

		if(abso(z) > 2) return 0;
	}

	return 1;
}


int main(){
	int width = 300;
	int height = 600;

	for(int i = 0; i < width; i++) {
		for(int j=0; j<height; j++) {

			float x = ((float) i) / ((float) width)  * 4 - 2;
			float y = ((float) j) / ((float) height) * 4 - 2;

			struct complex c = {y, x};

			if(check(c)) {
				printf("0");
			} else {
				printf(" ");
			}
		}
		printf("\n");
	}

	return 0;
}

