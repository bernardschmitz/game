
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "main.h"

class Player : public Actor {

   private:

      float z_rotation;
      int thrusting;
      float shooting;

      GLuint dl_cockpit;
      GLuint dl_left_wing;
      GLuint dl_right_wing;
      GLuint dl_left_engine;
      GLuint dl_right_engine;
      int dot;

      bool left, right, thrust, shoot;
   public:

      Player();
      ~Player();

      float getZRot() { return z_rotation; }

      void action(float dt);
      void render();

};


extern Player *player;

#endif

