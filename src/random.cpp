
#include "random.h"


float gaussian_random_float(float mean, float stdev) {

   static int phase = 1;
   static float x, y, w;
   float k;

   if(phase) {

      do {
         x = 2.0* rand()/RAND_MAX - 1.0;
         y = 2.0* rand()/RAND_MAX - 1.0;
         w = x*x + y*y;
      }
      while(w >= 1.0 || w == 0.0);

      k = mean + stdev * x * sqrt( -2.0*log(w) / w);
   }
   else {
      k = mean + stdev * y * sqrt( -2.0*log(w) / w);
   }

   phase = !phase;

   return k;
}

