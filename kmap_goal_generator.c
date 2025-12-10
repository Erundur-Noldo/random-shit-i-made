/*
   I was talking to random Discord computer science person,
     and he showed me kmaps and then I misunderstood what they were I guess,
      so I wanted to show him how to solve a 5-dimensional kmap and
  to give myself a kmap to solve I wrote this program, so enjoy I guess

    feel free to use it if you want for some reason????
       also you might wanna revert the shit that's printed I guess...
              I can't be bothered

was signed: 2025-12-10, 01:16:56

   ____
  /    \
 | _  _ |
 |      |
  \    /
   \  /
    \/
*/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main(int argc, char **argv) {
   if(argc < 2) {
      puts("provide number of dimensions");
      return 1;
   }
   int dimensions = atoi(argv[1]);
   if(dimensions == 0) {
      puts("not gonna do zero dimensions :v");
      return 1;
   }
   /* we only have 26 letters,
       also, it can't go higher than 32 bits because like, int32_t I guess,
           alsooooooooo
              why.. why would you need this much...
      pretty sure your hardware can't run it anyway x3 
   okay now it can because I made sure the bits are computed
      during printing instead of beforehand and put on the stack
           as before . . . . .     */
   if(dimensions > 26) {
      puts("no\n");
      return 1;
   }

   /* I'm doing it in this weird ass way to show off
        that I can also *not* just use printf I guess...
    I know the compiler can also just do it for me but ye */
   FILE *out = stdout;
   srand(time(NULL));

   for(int i=0; i < (1 << dimensions); i++) {
      if(rand() & 1) fputs("\033[32m", out);
      else fputs("\033[31m", out);
      for(int j=0; j<dimensions; j++) {
         /* the modulo and shit, in case you wanna do a *really* big one */
         fputc(('m' + j - 'a') % ('z' - 'a' + 1) + 'a', out); 
         if((1 << j) & i) fputc('\'', out);
         else fputc(' ', out);
      }
      fputc('\n', out);
   }
   fputs("\033[0m", out);
   return 0;
}
