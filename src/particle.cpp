

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

            tex[x][y][0]= 240 - (240 * t) / hole_size + rand()%15;
            tex[x][y][1]= 240 - (240 * t) / hole_size + rand()%15;
            //tex[x][y][2]= 240 - (240 * t) / hole_size + rand()%15;
            tex[x][y][3]= 240 - (240 * t) / hole_size + rand()%15;
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
      p[i].pos[0] = random_float(-0.01, 0.01); 
      p[i].pos[1] = random_float(-0.01, 0.01); 
      p[i].pos[2] = -10.0;
      sgCopyVec3(p[i].oldPos, p[i].pos);
      p[i].vel[0] = random_float(-1.0, 1.0); 
      p[i].vel[1] = random_float(-1.0, 1.0); 
      p[i].vel[2] = random_float(-1.0, 1.0); 
      //p[i].vel[2] = 0.0;
      sgNormalizeVec3(p[i].vel);
      sgScaleVec3(p[i].vel, random_float(0.01, 0.15));

      p[i].color[0] = random_float(0.5, 1.0); 
      p[i].color[1] = random_float(0.5, 1.0); 
      p[i].color[2] = random_float(0.5, 1.0); 
      p[i].color[3] = 1.0;

      p[i].size = random_float(0.02, 0.2);
      p[i].max_energy = p[i].energy = random_int(25, 50);
   }

   for(int i=0; i<250; i++) {
      p[i].size = random_float(0.1, 0.3);
      sgScaleVec3(p[i].vel, random_float(1.5, 2.5));
      p[i].max_energy = p[i].energy = random_int(45, 75);
   }


   sgVec3 u;
   sgSetVec3(u, 0.0, 0.0, 0.0);

   for(int i=0; i<n; i++)
      sgAddVec3(p[i].vel, u);

}

ParticleSystem::~ParticleSystem() {

   delete [] p;
}

void ParticleSystem::action() {

   alive = 0;

   for(int i=0; i<n; i++) {
      p[i].energy--;
      if(p[i].energy > 0) {
         sgCopyVec3(p[i].oldPos, p[i].pos);

         // acceleration
/*        
         sgVec3 k;
         sgSetVec3(k, 5.0, 5.0, -10.0); 
         sgVec3 dir;
         sgSubVec3(dir, k, p[i].pos);

         sgNormalizeVec3(dir);
         sgAddScaledVec3(p[i].vel, dir, 0.01);

*/
         sgAddVec3(p[i].pos, p[i].vel);
         p[i].color[3] = p[i].energy*1.0/p[i].max_energy;

      }
      else {
         p[i].energy = 0;
         alive++;
/*
      p[i].pos[0] = random_float(-0.01, 0.01); 
      p[i].pos[1] = random_float(-0.01, 0.01); 
      p[i].pos[2] = -10.0;
      sgCopyVec3(p[i].oldPos, p[i].pos);
      p[i].vel[0] = random_float(-1.0, 1.0); 
      p[i].vel[1] = random_float(-1.0, 1.0); 
      p[i].vel[2] = 0.0;
      sgNormalizeVec3(p[i].vel);
      sgScaleVec3(p[i].vel, random_float(0.01, 0.5));

      p[i].color[0] = random_float(0.5, 1.0); 
      p[i].color[1] = random_float(0.5, 1.0); 
      p[i].color[2] = random_float(0.5, 1.0); 
      p[i].color[3] = 1.0;

      p[i].size = 0.25;
      p[i].energy = random_int(100, 250);
*/
       }
   }
}

void ParticleSystem::render() {

   glPushMatrix();

   glTranslatef(pos[0], pos[1], pos[2]);

   glDisable(GL_LIGHTING);

   glEnable(GL_TEXTURE_2D);

   glEnable(GL_BLEND);
   //glBlendFunc(GL_SRC_ALPHA,GL_ONE);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE);

   // Enable flat shading -- no need for smooth.
   glShadeModel(GL_FLAT);

   glDisable(GL_DEPTH_TEST);

   static sgVec4 pink = { 1.0, 1.0, 1.0, 1.0 };
   glColor4fv(pink);

   glBegin(GL_QUADS);
   for(int i=0; i<n; i++) {
      if(p[i].energy > 0) {

         glColor4fv(p[i].color);

         sgVec3 dir;
         sgSubVec3(dir, p[i].pos, p[i].oldPos);
         sgNormalizeVec3(dir);

         sgScaleVec3(dir, p[i].size);

         sgVec3 up, down, back;

         up[0] = -dir[1];
         up[1] = dir[0];
         up[2] = 0.0;

         sgNegateVec3(down, up);

         sgNegateVec3(back, dir);


         sgVec3 p0, p1, p2, p3;

         sgAddVec3(p0, p[i].oldPos, up);
         sgAddVec3(p0, back);

         sgAddVec3(p1, p[i].oldPos, down);
         sgAddVec3(p1, back);

         sgAddVec3(p2, p[i].pos, down);
         sgAddVec3(p2, dir);

         sgAddVec3(p3, p[i].pos, up);
         sgAddVec3(p3, dir);


               glTexCoord2f(0.0, 0.0);
               glVertex3f(p0[0], p0[1], p0[2]);
               glTexCoord2f(0.0, 1.0);
               glVertex3f(p1[0], p1[1], p1[2]);
               glTexCoord2f(1.0, 1.0);
               glVertex3f(p2[0], p2[1], p2[2]);
               glTexCoord2f(1.0, 0.0);
               glVertex3f(p3[0], p3[1], p3[2]);



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

