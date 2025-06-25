/*
funny cal clone
written by Emika
uhh free to distribute for use as long as I am given credit
NOT for commercial purposes
not sure if this is enough to give it rights but maybe :3

it also highlights when the full moon is with *some* accuracy 

credits to harper.dev for wanting me
to upload this for some reason

  ____
 /    \  Emika
| _  _ | 
|      | 
 \    /    
  \  /    26th of June 
   \/    2025
*/

#include <stdio.h>
#include <time.h>
#include <string.h>

#define MASK "\
  ____  \
 /    \\ \
| _  _ |\
|      |\
 \\    / \
  \\  /  \
   \\/   "

#define mod(a, mod) (      \
   (a)>=0 ?                \
      (a)%(mod) :          \
      (a)%(mod) == 0 ?     \
         0 :               \
         (a)%(mod) + (mod) \
)


/*
this moon stuff, you can use as a sort of mini library
I'll also include the functions I wrote which i don't use in this program
basically, everything revolves around get_moon_age and MOON_CYCLE_LENGTH, though */

/* the first new moon since Epoch (in seconds from Epoch) */
#define NEW_MOON 588900
/* the amount of seconds the moon takes to go from new moon to new moon */
#define MOON_CYCLE_LENGTH 2551442

time_t get_moon_age(time_t current_time) {
   return mod((current_time - NEW_MOON), MOON_CYCLE_LENGTH);
}

int is_full_moon(time_t current_time) {
   time_t seconds_into_phase = get_moon_age(current_time);

   return (MOON_CYCLE_LENGTH / 2) - (MOON_CYCLE_LENGTH / 59) < seconds_into_phase
       && (MOON_CYCLE_LENGTH / 2) + (MOON_CYCLE_LENGTH / 59) > seconds_into_phase;
}

/*
float get_moon_cycle(time_t current_time) {
   int seconds_into_phase = get_moon_age(current_time);
   return (float) seconds_into_phase / (float) MOON_CYCLE_LENGTH;
}

time_t get_next_new_moon(time_t current_time) {
   time_t seconds_into_phase = get_moon_age(current_time);
   return current_time + (MOON_CYCLE_LENGTH - seconds_into_phase);
}
*/


void print_mask_line(int line) {
   static char mask[] = MASK;
   if(line < 7) printf("  \e[37;1m%.*s\e[0m\n", 8, &mask[8*line]);
   else printf("\n");
}



#define CALENDAR_WIDTH 20
int main() {
   time_t t = time(NULL);
   struct tm *tm = localtime(&t);

   char *month_name[12] = {
      "January",
      "February",
      "March",
      "April",
      "May",
      "June",
      "July",
      "August",
      "September",
      "October",
      "November",
      "December"
   };
   int month_len[12] = {
      31, 
      27 + (tm->tm_year % 4) - (tm->tm_year % 100) + (tm->tm_year % 400 == 100), 
      31, 30, 31, 30, 31, 31, 30, 31, 30, 31
   };

   int line = 0;


   /* space + 4 digits (if you use this after the year 9999, fuck you :3 */
   int str_len = strlen(month_name[tm->tm_mon]) + 5;
   for(int i=0; i < (CALENDAR_WIDTH - str_len + 1) / 2; i++) printf(" ");
   printf("%s %d", month_name[tm->tm_mon], 1900 + tm->tm_year);
   for(int i=0; i < (CALENDAR_WIDTH - str_len + 1) / 2; i++) printf(" ");
   print_mask_line(line++);


   printf("su mo tu we th fr sa ");
   print_mask_line(line++);

   int first_weekday = tm->tm_wday - (tm->tm_mday % 7 - 1);
   if(first_weekday < 0) first_weekday += 7;
   for(int i=0; i<first_weekday % 7; i++) {
      printf("   ");
   }

   for(int i=0; i<month_len[tm->tm_mon]; i++) {
      int weekday = (first_weekday + i) % 7;
      if(i != 0 && weekday == 0) print_mask_line(line++);

      int today = i+1 == tm->tm_mday;
      /* the following is very bad code. I should calculate *when* the full
      moon is, but I didn't because I'm lazy and it still executes in
      .01 seconds sooooooo */
      int full_moon = is_full_moon(t + (i - tm->tm_mday) * 24*3600);

      if(today && full_moon) {
         printf("\e[31;1m%2d\e[0m ", i+1);
      } else if(today) {
         printf("\e[7;1m%2d\e[0m ", i+1);
      } else if(full_moon) {
         printf("\e[97;1m%2d\e[0m ", i+1);
      } else {
         printf("%2d ", i+1);
      }
   }

   for(int i = (first_weekday + month_len[tm->tm_mon]) % 7; i<7; i++) {
      printf("   ");
   }
   print_mask_line(line++);
   for(int i=0; i<21; i++) printf(" ");
   print_mask_line(line++);

}
