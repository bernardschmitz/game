
#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "main.h"

struct Particle {
   vector3 position;
   vector3 velocity;
   vector3 acceleration;
   vector3 force;
   vector4 color;
   float friction, drag;
   float mass;
   float size;
   float life;            // life in seconds
   float max_life;
   bool dead;
};

struct ParticleDesc {
   int n;                                         // total number
   int spawn_init;                                // number spawned initially
   int spawn_rate;                                // number spawned each time step

   // initially particles spawn in a sphere
   // TODO have different spawn shapes
   vector3 spawn_pos;                             // particles are spawned here, relative to actor_pos
   float spawn_radius;

   float min_life, max_life;                    // particle energy range
   float min_size, max_size;                      // particle size range

   // TODO should be a bitfield
   bool energy_in_alpha;                           // puts energy in alpha so particles appear to fade
   bool size_from_velocity;                       // scales particle size based on velocity, faster = longer
   bool respawn_on_death;                         // indicates that a particle should respawn when dead

   vector4 color;
   GLuint texture_id;

   Particle *p;                                   // optional initial positions


//   vector3 gen_pos;               // position of generated particles relative to actor pos

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
      Particle *old_p;                       // array of particles
      int alive;                         // number of alive particles

      GLuint texture_id;                 // particles texture

      ParticleDesc desc;

      int find_dead_particle();
   public:
      ParticleSystem(const vector3& p, const vector3& v, const ParticleDesc& pd);
      virtual ~ParticleSystem();

      //virtual void init();

      // spawns min(k,n-alive)) particles
      void spawn(int k);

      // kills min(k,alive) particles
      void kill(int k);

      virtual void update(float dt);
      virtual void action(float dt);
      virtual void render();
};


#endif

