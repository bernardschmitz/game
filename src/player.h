
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "main.h"

class Player {

   private:
      sgVec3 position;
      sgVec3 velocity;

      float z_rotation;
      int thrusting;

      GLuint shape;

   public:

      Player();
      ~Player();

      void getPosition(sgVec3 pos) { sgCopyVec3(pos, position); }

      int action();
      int render();
};


extern Player *player;

#endif

