
#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <stdlib.h>

inline int random_int(int min, int max) {

   return min+(int)((max-min)*rand()/(RAND_MAX+1.0));
}

inline float random_float(float min, float max) {

   return min+((max-min)*rand()/(RAND_MAX+1.0));
}

#endif

