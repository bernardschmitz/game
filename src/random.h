
#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <stdlib.h>
#include <math.h>

inline int uniform_random_int(int min, int max) {

   return min+rand()/(RAND_MAX/(max-min+1)+1);
}

inline float uniform_random_float(float min, float max) {

   return min+((max-min)*rand()/(RAND_MAX+1.0));
}

// normal distribution
extern float gaussian_random_float(float mean, float stdev);

#endif

