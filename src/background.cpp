
#include "background.h"
#include "settings.h"
#include "player.h"

Background::Background() {




   // default
/*
   static vector4 map[8] = { vector4( 0.5, 0.0, 0.0, 0.0   ), 
                             vector4( 0.0, 0.5, 0.0, 0.1   ),
                             vector4( 0.0, 0.0, 0.5, 0.0   ),
                             vector4( 0.0, 0.5, 0.0, 0.1   ),
                             vector4( 0.5, 0.0, 0.0, 0.0   ),
                             vector4( 0.0, 0.0, 0.5, 0.1   ),
                             vector4( 0.5, 0.5, 0.0, 0.0   ),
                             vector4( 0.0, 0.0, 0.0, 0.1  )  };
*/

   static vector4 map[8] = { vector4( 0.5, 0.0, 0.0, 0.0   ), 
                             vector4( 0.5, 0.3, 0.0, 0.1   ),
                             vector4( 0.5, 0.5, 0.5, 0.0   ),
                             vector4( 0.5, 0.5, 0.0, 0.1   ),
                             vector4( 0.5, 0.0, 0.0, 0.0   ),
                             vector4( 0.0, 0.5, 0.0, 0.1   ),
                             vector4( 0.5, 0.4, 0.0, 0.0   ),
                             vector4( 0.5, 0.6, 0.0, 0.1  )  };


   // blue yellow
/*
   static sgVec4 map[8] = { { 0.0, 0.0, 0.3, 0.1 },
                            { 0.3, 0.3, 0.0, 0.2 },
                            { 0.3, 0.0, 0.0, 0.1 },
                            { 0.3, 0.3, 0.0, 0.3 },
                            { 0.0, 0.3, 0.3, 0.1 },
                            { 0.3, 0.3, 0.0, 0.2 },
                            { 0.0, 0.0, 0.0, 0.0 },
                            { 0.0, 0.0, 0.3, 0.1 }  };

*/
/*

   // blah
   static sgVec4 map[9] = { { 0.7, 0.0, 0.5, 0.1 },
                            { 0.1, 0.5, 0.0, 0.1 },
                            { 0.2, 0.0, 0.0, 0.1 },
                            { 0.3, 0.3, 0.0, 0.1 },
                            { 0.9, 0.5, 0.5, 0.1 },
                            { 0.3, 0.0, 0.0, 0.1 },
                            { 0.2, 0.0, 0.0, 0.1 },
                            { 0.1, 0.1, 0.5, 0.1 },
                            { 0.7, 0.0, 0.5, 0.1 }  };

*/

/*
   // dark
   static sgVec4 map[9] = { { 0.3, 0.0, 0.0, 0.5 },
                            { 0.0, 0.0, 0.4, 0.25 },
                            { 0.0, 0.0, 0.0, 0.25 },
                            { 0.0, 0.2, 0.0, 0.125 },
                            { 0.5, 0.8, 0.0, 0.5 },
                            { 0.0, 0.0, 0.3, 0.25 },
                            { 0.2, 0.0, 0.7, 0.125 },
                            { 0.0, 0.4, 0.2, 0.25 },
                            { 0.3, 0.0, 0.0, 0.5 }  };
*/

/*
   // reds
   static sgVec4 map[8] = { { 1.0, 0.0, 0.0, 0.125 },
                            { 1.0, 1.0, 0.0, 0.25 },
                            { 1.0, 0.0, 0.0, 0.125 },
                            { 1.0, 1.0, 0.0, 0.125 },
                            { 1.0, 1.0, 1.0, 0.25 },
                            { 1.0, 1.0, 0.0, 0.125 },
                            { 1.0, 0.0, 0.0, 0.25 },
                            { 1.0, 1.0, 0.0, 0.125 }  };
*/

   palette = new vector4[256];

   for(int i=0; i<8; i++) {
      for(int j=0; j<32; j++) {

         palette[i*32+j] = map[i]*(1.0f-j/32.0f) + map[(i+1)&0x7]*j/32.0f;

//         sgLerpVec4(palette[i*32+j], map[i], map[(i+1)&0x7], j/32.0);
         //printf("%d : %f %f %f\n", i*32+j, palette[i*32+j][0], palette[i*32+j][1], palette[i*32+j][2]);
      }
   }

}


Background::~Background() {

   delete [] palette;
}

int plasma(float x, float y, float z) {

   // this is the best one so far
   //float k = 0.25*(sin(x/60)+sin(y/30)+sin(z/23)+sin(x*y*z)/100);

   float k = (sin(sqrt(x*x+y*y)/16.0) + cos(sqrt(x*x+z*z)/-23.0)) / 2.0;
   //float k = sin(sqrt(x*x+y*y)/20)*sin(z/60); //+sin(y/100)+sin(z/80);


   return int(128.0+127.0*k);
}

#if 0
void Background::render(vector3 center, int flags) {


   glDisable(GL_LIGHTING);
   glDisable(GL_DEPTH_TEST);


   float s = settings.background_step;
   float n = settings.background_near;
   float f = settings.background_far;
   float gap = settings.background_gap;
   int p = settings.background_planes;
   float zs;

   if(p == 0)
      zs = 0.0;
   else
      zs = (n - f) / (p-1);

   float cx = floor(center.x/s)*s;
   float cy = floor(center.y/s)*s;


   static float u = 0.0;

   u += M_PI/400.0;

   float ux = 20.0*cos(u);
   float uy = 45.0*sin(u); // + 15.0*cos(u/2.0);
   float uz = 35.0*cos(u); // + 25.0*cos(u/4.0);

   // use quad strip
   glBegin(GL_QUADS);
   float z = f;
//   for(int i=0; i<p; i++) {
      //z += zs;
      float dd = fabs(z);
      for(float y=cy-dd; y<cy+dd+s; y+=s) {
         for(float x=cx-dd; x<cx+dd+s; x+=s) {
             vector4 c;
             c = palette[plasma(ux+x, uy+y, uz+z)&0xff] * 0.5;
             glColor4f(c.x, c.y, c.z, 1.0);
             glVertex3f(x, y, z);

             c = palette[plasma(ux+x+s, uy+y, uz+z)&0xff] * 0.5;
             glColor4f(c.x, c.y, c.z, 1.0);
             glVertex3f(x+s, y, z);

             c = palette[plasma(ux+x+s, uy+y+s, uz+z)&0xff] * 0.5;
             glColor4f(c.x, c.y, c.z, 1.0);
             glVertex3f(x+s, y+s, z);

             c = palette[plasma(ux+x, uy+y+s, uz+z)&0xff] * 0.5;
             glColor4f(c.x, c.y, c.z, 1.0);
             glVertex3f(x, y+s, z);

         }
      }
//   }
   glEnd();

   float g = s/gap;

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE);

   flags = 0;

   if(!flags) {


//   glBegin(GL_QUADS);
   z = f+zs;
   for(int i=0; i<p; i++) {
      dd = fabs(z);
      float offset = 0.0;
      for(float y=cy-dd; y<cy+dd+s; y+=s) {
         for(float x=cx-dd; x<cx+dd+s; x+=s) {

            glBegin(GL_POLYGON);

            float x0 = x+s/2.0;
            float y0 = y+s/2.0;
            float r0 = s*0.4;
            int sides = 6;
            for(int i=0; i<sides; i++) {
               float angle = 2.0*M_PI/sides*i;
               float x1 = x0+r0*cos(angle);
               float y1 = y0+r0*sin(angle);

               vector4 c = palette[plasma(ux+y1, uy+x1, uz+z)&0xff];
               glColor4f(c.x, c.y, c.z, c.w);
               glVertex3f(x1, y1, z);
            }
            glEnd();
/*
             glColor4fv(palette[plasma(ux+x+s, uy+y+s, uz+z)&0xff]);
             glVertex3f(x+g, y+g, z);

             glColor4fv(palette[plasma(ux+x, uy+y+s, uz+z)&0xff]);
             glVertex3f(x+s-g, y+g, z);

             glColor4fv(palette[plasma(ux+x, uy+y, uz+z)&0xff]);
             glVertex3f(x+s-g, y+s-g, z);

             glColor4fv(palette[plasma(ux+x+s, uy+y, uz+z)&0xff]);
             glVertex3f(x+g, y+s-g, z);
*/
         }
      }
      z += zs;
   }
   glEnd();

}

//   sgVec3 vel;
//   player->getVelocity(vel);

   glBegin(GL_LINES);

   //sgVec4 white = { 0.6, 0.6, 0.6, 0.3 };
   float white[] = { 0.75, 0.75, 0.75, 0.1 };

//-(sgScalarProductVec3(vel, vel)*0.3/(1.2*1.2)) };

   glColor4fv(white);

   s = s/2.0;
   float d = -10.0;
   //for(float d=f; d<n+s; d+=zs) {
      dd = fabs(d)+s;
      for(float y=cy-dd; y<cy+dd+s; y+=s) {
         glVertex3f(cx-dd, y, d);
         glVertex3f(cx+dd, y, d);
      }
      for(float x=cx-dd; x<cx+dd+s; x+=s) {
         glVertex3f(x, cy-dd, d);
         glVertex3f(x, cy+dd, d);
      }
   //}

   glEnd();




   glEnable(GL_LIGHTING);
   glEnable(GL_DEPTH_TEST);
   glDisable(GL_BLEND);

}
#endif



void Background::render(vector3 center, int flags) {


   glDisable(GL_LIGHTING);
   glDisable(GL_DEPTH_TEST);


   float s = settings.background_step;
   float n = settings.background_near;
   float f = settings.background_far;
   float gap = settings.background_gap;
   int p = settings.background_planes;
   float zs;

   if(p == 0)
      zs = 0.0;
   else
      zs = (n - f) / (p-1);

   float cx = floor(center.x/s)*s;
   float cy = floor(center.y/s)*s;
   float cz = floor(center.z/s)*s;


   static float u = 0.0;

   u += M_PI/400.0;

   float ux = 20.0*cos(u);
   float uy = 45.0*sin(u); // + 15.0*cos(u/2.0);
   float uz = 35.0*cos(u); // + 25.0*cos(u/4.0);

   float dd;

   // use quad strip
   glBegin(GL_QUADS);
   float z = f;
//   for(int i=0; i<p; i++) {
      //z += zs;
      dd = fabs(z)-cz;
      for(float y=cy-dd; y<cy+dd+s; y+=s) {
         for(float x=cx-dd; x<cx+dd+s; x+=s) {
             vector4 c;
             c = palette[plasma(ux+x, uy+y, uz+z)&0xff] * 0.5;
             glColor4f(c.x, c.y, c.z, 1.0);
             glVertex3f(x, y, z);

             c = palette[plasma(ux+x+s, uy+y, uz+z)&0xff] * 0.5;
             glColor4f(c.x, c.y, c.z, 1.0);
             glVertex3f(x+s, y, z);

             c = palette[plasma(ux+x+s, uy+y+s, uz+z)&0xff] * 0.5;
             glColor4f(c.x, c.y, c.z, 1.0);
             glVertex3f(x+s, y+s, z);

             c = palette[plasma(ux+x, uy+y+s, uz+z)&0xff] * 0.5;
             glColor4f(c.x, c.y, c.z, 1.0);
             glVertex3f(x, y+s, z);

         }
      }
//   }
   glEnd();

   float g = s/gap;

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE);

   flags = 0;

   if(!flags) {


//   glBegin(GL_QUADS);
   z = f+zs;
   for(int i=0; i<p; i++) {
      dd = fabs(z)-cz;
      float offset = 0.0;
      for(float y=cy-dd; y<cy+dd+s; y+=s) {
         for(float x=cx-dd; x<cx+dd+s; x+=s) {

            glBegin(GL_POLYGON);

            float x0 = x+s/2.0;
            float y0 = y+s/2.0;
            float r0 = s*0.4;
            int sides = 6;
            for(int i=0; i<sides; i++) {
               float angle = 2.0*M_PI/sides*i;
               float x1 = x0+r0*cos(angle);
               float y1 = y0+r0*sin(angle);

               vector4 c = palette[plasma(ux+y1, uy+x1, uz+z)&0xff];
               glColor4f(c.x, c.y, c.z, c.w);
               glVertex3f(x1, y1, z);
            }
            glEnd();

         }
      }
      z += zs;
   }
   glEnd();

}


//   sgVec3 vel;
//   player->getVelocity(vel);

   glBegin(GL_LINES);

   //sgVec4 white = { 0.6, 0.6, 0.6, 0.3 };
   float white[] = { 0.75, 0.75, 0.75, 0.1 };

//-(sgScalarProductVec3(vel, vel)*0.3/(1.2*1.2)) };

   glColor4fv(white);

   s = s/2.0;
   float d = -10.0;
   //for(float d=f; d<n+s; d+=zs) {
      dd = fabs(d)+s-cz;
      for(float y=cy-dd; y<cy+dd+s; y+=s) {
         glVertex3f(cx-dd, y, d);
         glVertex3f(cx+dd, y, d);
      }
      for(float x=cx-dd; x<cx+dd+s; x+=s) {
         glVertex3f(x, cy-dd, d);
         glVertex3f(x, cy+dd, d);
      }
   //}

   glEnd();




   glEnable(GL_LIGHTING);
   glEnable(GL_DEPTH_TEST);
   glDisable(GL_BLEND);

}

