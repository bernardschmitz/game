
#ifndef __BULLET_H__
#define __BULLET_H__

#include "memcheck.h"
#include "actor.h"

// need a factory

class Bullet : public Actor {

   private:

      float life;
      bool squid;
      vector3 A,B,C,D, from;
      float range;

      vector3 oldpos;
      vector3 ff;

      vector3 pts[12];
      float ang[4], dis[4];

      int tex;
      int tex2;

   public:
      Bullet(vector3 p, vector3 v, vector3 f, float r=100.0);
      ~Bullet();

      void render();
      void action(float dt);   
};


#endif

