
#ifndef __INPUT_H__
#define __INPUT_H__

#include "main.h"

struct Input {

   int rotate_left;
   int rotate_right;
   int thrust;
   int fire;
   int bomb;

   Input() { rotate_left = rotate_right = thrust = fire = bomb = 0; }

   void process();
};

extern Input input;

#endif

