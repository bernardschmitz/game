
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "main.h"

class Player : public Actor {

   private:

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

      float getZRot() { return z_rotation; }

      void action();
      void render();
};


extern Player *player;

#endif

