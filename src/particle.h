
#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "main.h"

struct Particle {
   sgVec3 pos, vel;
   sgVec3 oldPos;
   sgVec4 color;
   float size;
   int energy;
   int max_energy;
};

struct ParticleDesc {
   int n;                        // total number
   sgVec3 pos, vel;              // position and velocity of actor

   sgVec3 gen_pos;               // position of generated particles relative to actor pos
//   sgVec3 
   // dir and vel of parts
   // uniform or gaussian rand?
   // pos of generated parts
   // color, change due to vel?  alpha change due to vel
   // size, change due to vel?
   // generation speed, time, amount etc... gen automatically or not?
   // list of extra accels
   // list of avoid points, lines, planes, spheres etc...
   // list of attract points, lines, planes, spheres etc...
   // dt
   // what to do when particle dies?  
   // what to do when all particles are dead?
   // move mode eg follow, flock, repell etc...
   // inverse square for attraction or not?
   // use vel and pos from actor or not?
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

      //virtual void init(int n, sgVec3 pos, sgVec3 vel, GLuint tex);
      virtual void init();

      virtual void action();
      virtual void render();
};

extern ActorList<ParticleSystem> alParticles;

#endif

