
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "main.h"

class Player {

   private:
      vector3 position;
      vector3 velocity;

      float z_rotation;
      int thrusting;
      int shooting;

      GLuint dl_cockpit;
      GLuint dl_left_wing;
      GLuint dl_right_wing;
      GLuint dl_left_engine;
      GLuint dl_right_engine;

   public:

      Player();
      ~Player();

      vector3 getPosition() { return position; }
      vector3 getVelocity() { return velocity; }

      int action();
      int render();
};


extern Player *player;

#endif

