

#include "particle.h"
#include "random.h"

ActorList<ParticleSystem> alParticles;




ParticleSystem::ParticleSystem() : Actor() {

   init();

   GLuint gluerr;
   GLubyte tex[128][128][4];
   int x,y,t;
   int hole_size = 63*63; //3300; // ~ == 57.45 ^ 2.

   // Generate a texture index, then bind it for future operations.
   // Iterate across the texture array.

   for(y=0;y<128;y++) {
      for(x=0;x<128;x++) {

        // Make a round dot in the texture's alpha-channel.

         // Calculate distance to center (squared).
         t = (x-64)*(x-64) + (y-64)*(y-64) ;

         if ( t < hole_size) {// Don't take square root; compare squared.
            //tex[x][y]= 240 - (240 * t) / hole_size + ourRand(15);
            tex[x][y][0]=0;   // Outside of the dot, it's transparent.
            tex[x][y][1]=0;   // Outside of the dot, it's transparent.
            tex[x][y][2]=0;   // Outside of the dot, it's transparent.
            tex[x][y][3]=0;   // Outside of the dot, it's transparent.

            tex[x][y][0]= 240 - (240 * t) / hole_size + uniform_random_int(0, 15);
            tex[x][y][1]= 240 - (240 * t) / hole_size + uniform_random_int(0, 15);
         //   tex[x][y][2]= 240 - (240 * t) / hole_size + uniform_random_int(0, 15);
            tex[x][y][3]= 240 - (240 * t) / hole_size + uniform_random_int(0, 15);
         }
         else {
            tex[x][y][0]=0;   // Outside of the dot, it's transparent.
            tex[x][y][1]=0;   // Outside of the dot, it's transparent.
            tex[x][y][2]=0;   // Outside of the dot, it's transparent.
            tex[x][y][3]=0;   // Outside of the dot, it's transparent.
         }


 
      }
   }


   glGenTextures(1, &texture_id);
   glBindTexture(GL_TEXTURE_2D, texture_id);

   // The GLU library helps us build MipMaps for our texture.

   if ((gluerr=gluBuild2DMipmaps(GL_TEXTURE_2D, 4, 128, 128, GL_RGBA, GL_UNSIGNED_BYTE, (void *)tex))) {

      fprintf(stderr,"GLULib%s\n",gluErrorString(gluerr));
   }

   // Some pretty standard settings for wrapping and filtering.
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);


   // Some pretty standard settings for wrapping and filtering.
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
   //glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

   // We start with GL_MODULATE mode.
   glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   //glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

}

void ParticleSystem::init() {

   n = 1000;
   p = new Particle[n];

   alive = n;

   for(int i=0; i<n; i++) {
      p[i].pos.x = uniform_random_float(-0.01, 0.01); 
      p[i].pos.y = uniform_random_float(-0.01, 0.01); 
      p[i].pos.z = -10.0;
      p[i].oldPos = p[i].pos;
      p[i].vel.x = uniform_random_float(-1.0, 1.0); 
      p[i].vel.y = uniform_random_float(-1.0, 1.0); 
      p[i].vel.z = uniform_random_float(-1.0, 1.0); 
      //p[i].vel[2] = 0.0;

      p[i].vel.normalize();
      //sgScaleVec3(p[i].vel, uniform_random_float(0.01, 0.15));
      p[i].vel *= 0.15*gaussian_random_float(0.0, 2.0);

      p[i].color.x = uniform_random_float(0.5, 1.0); 
      p[i].color.y = uniform_random_float(0.5, 1.0); 
      p[i].color.z = uniform_random_float(0.5, 1.0); 
      p[i].color.w = 1.0;

      p[i].size = uniform_random_float(0.02, 0.2);
      p[i].max_energy = p[i].energy = uniform_random_int(10, 50);
   }

   for(int i=0; i<250; i++) {
      p[i].size = uniform_random_float(0.1, 0.3);

      //sgScaleVec3(p[i].vel, uniform_random_float(1.5, 2.5));
      p[i].vel.normalize();
      p[i].vel *= 0.15*gaussian_random_float(0.0, 1.0);

      p[i].max_energy = p[i].energy = uniform_random_int(45, 75);
   }

   vector3 u(0.0, 0.0, 0.0);

   for(int i=0; i<n; i++)
      p[i].vel += u;

}

ParticleSystem::~ParticleSystem() {

   delete [] p;
}

void ParticleSystem::action() {

   alive = 0;

   for(int i=0; i<n; i++) {
      p[i].energy--;
      if(p[i].energy > 0) {
         p[i].oldPos = p[i].pos;

         // acceleration
/*        
         sgVec3 k;
         sgSetVec3(k, 5.0, 5.0, -10.0); 
         sgVec3 dir;
         sgSubVec3(dir, k, p[i].pos);

         sgNormalizeVec3(dir);
         sgAddScaledVec3(p[i].vel, dir, 0.01);

*/
         p[i].pos += p[i].vel;
         p[i].color.w = p[i].energy*1.0/p[i].max_energy;

      }
      else {
         p[i].energy = 0;
         alive++;
/*
      p[i].pos[0] = uniform_random_float(-0.01, 0.01); 
      p[i].pos[1] = uniform_random_float(-0.01, 0.01); 
      p[i].pos[2] = -10.0;
      sgCopyVec3(p[i].oldPos, p[i].pos);
      p[i].vel[0] = uniform_random_float(-1.0, 1.0); 
      p[i].vel[1] = uniform_random_float(-1.0, 1.0); 
      p[i].vel[2] = 0.0;
      sgNormalizeVec3(p[i].vel);
      sgScaleVec3(p[i].vel, uniform_random_float(0.01, 0.5));

      p[i].color[0] = uniform_random_float(0.5, 1.0); 
      p[i].color[1] = uniform_random_float(0.5, 1.0); 
      p[i].color[2] = uniform_random_float(0.5, 1.0); 
      p[i].color[3] = 1.0;

      p[i].size = 0.25;
      p[i].energy = random_int(100, 250);
*/
       }
   }
}

void ParticleSystem::render() {

   glPushMatrix();

   glTranslatef(pos.x, pos.y, pos.z);

   glDisable(GL_LIGHTING);

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
      if(p[i].energy > 0) {

         glColor4f(p[i].color.x, p[i].color.y, p[i].color.z, p[i].color.w);

         vector3 dir;
         dir = ~(p[i].pos - p[i].oldPos) * p[i].size;

         vector3 up, down, back;

         up.x = -dir.y;
         up.y = dir.x;
         up.z = 0.0f;

         down = -up;

         back = -dir;

         vector3 p0, p1, p2, p3;

         p0 = p[i].oldPos + up + back;

         p1 = p[i].oldPos + down + back;

         p2 = p[i].pos + down + dir;

         p3 = p[i].pos + up + dir;

               glTexCoord2f(0.0, 0.0);
               glVertex3f(p0.x, p0.y, p0.z);
               glTexCoord2f(0.0, 1.0);
               glVertex3f(p1.x, p1.y, p1.z);
               glTexCoord2f(1.0, 1.0);
               glVertex3f(p2.x, p2.y, p2.z);
               glTexCoord2f(1.0, 0.0);
               glVertex3f(p3.x, p3.y, p3.z);



/*
         glTexCoord2f(0.0, 0.0);
         glVertex3f(p[i].pos[0]-p[i].size, p[i].pos[1]+p[i].size, p[i].pos[2]);
         glTexCoord2f(0.0, 1.0);
         glVertex3f(p[i].pos[0]-p[i].size, p[i].pos[1]-p[i].size, p[i].pos[2]);
         glTexCoord2f(1.0, 1.0);
         glVertex3f(p[i].pos[0]+p[i].size, p[i].pos[1]-p[i].size, p[i].pos[2]);
         glTexCoord2f(1.0, 0.0);
         glVertex3f(p[i].pos[0]+p[i].size, p[i].pos[1]+p[i].size, p[i].pos[2]);
*/
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

