

#include "particle.h"
#include "random.h"


// TODO render ideas
// trangle, point at oldpos, base at pos
// as above with fuzzy blob at pos


/*
truct ParticleDesc {
   int n;                                         // total number
   int spawn_rate;                                // number spawned each time step

   vector3 actor_pos, actor_vel;                  // position and velocity of actor

   vector3 spawn_pos;                             // particles are spawned here, relative to actor_pos
   float spawn_radius;

   int min_energy, max_energy;                    // particle energy range
   float min_size, max_size;                      // particle size range

   bool enery_in_alpha;                           // puts energy in alpha so particles appear to fade
   bool size_from_velocity;                       // scales particle size based on velocity, faster = longer

   bool respawn_on_death;                         // indicates that a particle should respawn when dead

   vector4 color;
   GLuint texture_id;

   Particle *p;   
*/

ParticleSystem::ParticleSystem(const vector3& vp, const vector3& vv, const ParticleDesc& pd) : 
   Actor(ACT_PARTICLE, "Particle", vp, vv) {

   desc = pd;

   texture_id = pd.texture_id;

   n = pd.n;

   if(pd.p == NULL)
      p = new Particle[n];
   else
      p = pd.p;
      //memcpy(p, pd.p, sizeof(Particle)*n);

   old_p = new Particle[n];

   // make all particles dead
   alive = 0;
   for(int i=0; i<n; i++)
      p[i].dead = true;

//   printf("particle sys %d %d\n", n, alive);
   spawn(desc.spawn_init);
}


int ParticleSystem::find_dead_particle() {

   if(alive == n)
      return -1;

   for(int i=0; i<n; i++)
      if(p[i].dead)
         return i;

   return -1;
}

void ParticleSystem::spawn(int k) {

//printf("spawn k=%d\n", k);
   if(k > n-alive)
      k = n-alive;
//printf(" k=%d\n", k);

   for(int j=0; j<k; j++) {
      int i = find_dead_particle();
//printf("spawn i j = %d %d\n", j, i);
      if(i >= 0) {
         float r = uniform_random_float(0.0, M_PI*2.0);
         p[i].position = position + desc.spawn_pos + vector3(cos(r)*desc.spawn_radius, sin(r)*desc.spawn_radius, 0.0);

         p[i].velocity = velocity;

         vector3 v(uniform_random_float(-1.0, 1.0), uniform_random_float(-1.0, 1.0), uniform_random_float(-1.0, 1.0)); 
         v.normalize();
         v *= 0.15*gaussian_random_float(0.0, 2.0);

         p[i].friction = 0.0;
         p[i].drag = 0.0;

         p[i].mass = 1.0;
         p[i].force = v*1000.0;
   
         p[i].color.x = uniform_random_float(0.5, 1.0); 
         p[i].color.y = uniform_random_float(0.5, 1.0); 
         p[i].color.z = uniform_random_float(0.5, 1.0); 
         p[i].color.w = 1.0;
   
         p[i].size = uniform_random_float(desc.min_size, desc.max_size);
         p[i].max_life = p[i].life = uniform_random_float(desc.min_life, desc.max_life);
         p[i].dead = false;

         old_p[i] = p[i];
      }
   }
}

ParticleSystem::~ParticleSystem() {

   // TODO check this
   delete [] p;
   delete [] old_p;
}

/*
void Actor::update(float dt) {

   //printf("update with %f\n", dt);

   action(dt);

   float speed2 = velocity.lengthSquared();

   vector3 negv = -(!velocity);

   if(drag > 0.0)
      force += negv*(drag*speed2);

   if(speed2 > 0.0 && friction > 0.0)
      force += negv*friction;

   acceleration = force / mass;
   velocity += acceleration * dt;
   position += velocity * dt;

}
*/

void ParticleSystem::update(float dt) {

   action(dt);

   alive = 0;

   for(int i=0; i<n; i++) {

      old_p[i] = p[i];

      if(!p[i].dead) {

         alive++;

         float s2 = p[i].velocity.lengthSquared();
         if(s2 < tiny) {
            s2 = 0.0;
            p[i].velocity.set(0.0, 0.0, 0.0);
         }
         vector3 nv = -(!p[i].velocity);
         vector3 tf(force);
         if(p[i].drag > 0.0)
            tf += nv*(p[i].drag*s2);
         if(s2 > 0.0 && p[i].friction > 0.0)
            tf += nv*p[i].friction;

         p[i].acceleration = tf / p[i].mass;
         p[i].velocity += p[i].acceleration * dt;
         p[i].position += p[i].velocity * dt;

         // TODO may not want this!
         p[i].color.w = p[i].life*1.0/p[i].max_life;
      }
   }

   if(alive == 0)
      flags = ACT_REMOVE;
}





void ParticleSystem::action(float dt) {

   spawn(desc.spawn_rate);

   for(int i=0; i<n; i++) {
//printf("action i=%d\n", i);
      p[i].life -= dt;
      if(p[i].life > 0.0) {
         // calculate forces here...
         //p[i].force = p[i].vel * dt;
      }
      else 
         p[i].dead = true;
   }
}


void ParticleSystem::render() {

   glPushMatrix();

//   glTranslatef(pos.x, pos.y, pos.z);

   glDisable(GL_LIGHTING);

   glBindTexture(GL_TEXTURE_2D, texture_id);
   glEnable(GL_TEXTURE_2D);

   glEnable(GL_BLEND);
   //glBlendFunc(GL_SRC_ALPHA,GL_ONE);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE);

   // Enable flat shading -- no need for smooth.
   glShadeModel(GL_FLAT);

   glDisable(GL_DEPTH_TEST);

   static float pink[] = { 1.0, 1.0, 1.0, 1.0 };
   glColor4fv(pink);

   glBegin(GL_QUADS);
   for(int i=0; i<n; i++) {
      if(!p[i].dead) {

         glColor4f(p[i].color.x, p[i].color.y, p[i].color.z, p[i].color.w);

         vector3 dir;
         dir = p[i].position - old_p[i].position;
         dir.z = 0.0;
         dir.normalize();
         dir *= p[i].size;
        
         //dir = ~(p[i].pos - p[i].oldPos) * p[i].size;

         vector3 up, down, back;

         up.x = -dir.y;
         up.y = dir.x;
         up.z = dir.z;

         down = -up;

         back = -dir;

         vector3 p0, p1, p2, p3;

         p0 = old_p[i].position + up + back;

         p1 = old_p[i].position + down + back;

         p2 = p[i].position + down + dir;

         p3 = p[i].position + up + dir;

               glTexCoord2f(0.0, 0.0);
               glVertex3f(p0.x, p0.y, p0.z);
               glTexCoord2f(0.0, 1.0);
               glVertex3f(p1.x, p1.y, p1.z);
               glTexCoord2f(1.0, 1.0);
               glVertex3f(p2.x, p2.y, p2.z);
               glTexCoord2f(1.0, 0.0);
               glVertex3f(p3.x, p3.y, p3.z);
      }
   }
   glEnd();

/*
   glBegin(GL_LINES);
   for(int i=0; i<n; i++) {
      if(p[i].energy > 0) {
         glColor4fv(p[i].color);
         glVertex3f(p[i].oldPos[0], p[i].oldPos[1], p[i].oldPos[2]);
         glVertex3f(p[i].pos[0], p[i].pos[1], p[i].pos[2]);
      }
   }
   glEnd();
*/

   glEnable(GL_LIGHTING);
   glDisable(GL_TEXTURE_2D);

   glDisable(GL_BLEND);

   // Enable flat shading -- no need for smooth.
   glShadeModel(GL_SMOOTH);

   glEnable(GL_DEPTH_TEST);
   glPopMatrix();
}

