
#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "main.h"

struct Particle {
   sgVec3 pos, vel;
   sgVec3 oldPos;
   sgVec4 color;
   float size;
   int energy;
};


class ParticleSystem : public Actor {

   private:
      int n;                             // total number of particles
      Particle *p;                       // array of particles
      int alive;                         // number of alive particles

      GLuint texture_id;                 // particles texture

   public:
      ParticleSystem();
      virtual ~ParticleSystem();

      void init();

      virtual void action();
      virtual void render();
};

extern ActorList<ParticleSystem> alParticles;

#endif

