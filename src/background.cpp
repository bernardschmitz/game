
#include "background.h"
#include "settings.h"
#include "player.h"
#include "texture.h"

Background::Background() : Actor(ACT_BACKGROUND, vector3(0.0, 0.0, 0.0), vector3(0.0, 0.0, 0.0), vector3(0.0, 0.0, 1.0)) {


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

/*
   // nice
   static vector4 map[8] = { vector4( 0.5, 0.0, 0.0, 0.0   ), 
                             vector4( 0.5, 0.3, 0.0, 0.1   ),
                             vector4( 0.5, 0.5, 0.5, 0.0   ),
                             vector4( 0.5, 0.5, 0.0, 0.1   ),
                             vector4( 0.5, 0.0, 0.0, 0.0   ),
                             vector4( 0.0, 0.5, 0.0, 0.1   ),
                             vector4( 0.5, 0.4, 0.0, 0.0   ),
                             vector4( 0.5, 0.6, 0.0, 0.1  )  };

*/

   static vector4 map[8] = { vector4( 0.0, 0.0, 0.5, 0.0   ), 
                             vector4( 0.0, 0.0, 0.4, 0.1   ),
                             vector4( 0.0, 0.5, 0.4, 0.0   ),
                             vector4( 0.5, 0.4, 0.0, 0.1   ),
                             vector4( 0.5, 0.5, 0.0, 0.0   ),
                             vector4( 0.0, 0.4, 0.5, 0.1   ),
                             vector4( 0.0, 0.0, 0.4, 0.0   ),
                             vector4( 0.0, 0.0, 0.5, 0.1  )  };



   palette = new vector4[256];

   for(int i=0; i<8; i++) {
      for(int j=0; j<32; j++) {

         palette[i*32+j] = map[i]*(1.0f-j/32.0f) + map[(i+1)&0x7]*j/32.0f;

//         sgLerpVec4(palette[i*32+j], map[i], map[(i+1)&0x7], j/32.0);
         //printf("%d : %f %f %f\n", i*32+j, palette[i*32+j][0], palette[i*32+j][1], palette[i*32+j][2]);
      }
   }


   u = 0.0;

   ux = uy = uz = 0.0;

   hex_tex = TextureManager::getInstance()->load("hex.png");




   // make triangle strips

   float s = 5.0;
   float d = s + fabs(-45) + fabs(-40);

   float sx = floor(d/s)*s;
   float sy = s+floor((d*0.75)/s)*s;

   int w = (int)(sx*2.0/s);
   int h = (int)(sy*2.0/s);

   int n_verts = (h+1)*2;

/*
   strips = new float[n_verts*4 * w];
   cols   = new float[n_verts*4 * w];

   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(4, GL_FLOAT, 0, strips);
   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer(4, GL_FLOAT, 0, cols);
*/

   strips = new unsigned char[w*n_verts*sizeof(float)*4 + w*n_verts*sizeof(unsigned char)*4];
   //cols   = new float[n_verts*4 * w];

  glInterleavedArrays(GL_C4UB_V3F, sizeof(unsigned char)*4+sizeof(float)*4, strips);

/*
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(4, GL_FLOAT, sizeof(float)*4, strips+sizeof(float)*4);
   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer(4, GL_FLOAT, sizeof(float)*4, strips);
*/
}


Background::~Background() {

   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);

   delete [] palette;

   delete [] strips;
//   delete [] cols;
}

inline int plasma(float x, float y, float z) {

   // this is the best one so far
   //float k = 0.25*(sin(x/60)+sin(y/30)+sin(z/23)+sin(x*y*z)/100);

   float k = (sin(sqrt(x*x+y*y)/16.0) * cos(sqrt(x*x+z*z)/-23.0)) / 1.0;
//   float k = (sin(sqrt(x*x+y*y)/16.0) + cos(sqrt(x*x+z*z)/-23.0)) / 2.0;

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

void Background::action(float dt) {

   u += M_PI/400.0*50.0*dt;

   ux = 20.0*cos(u) ;// + center.x;
   uy = 45.0*sin(u) ;//+ center.y; // + 15.0*cos(u/2.0);
   uz = 35.0*cos(u) ;//+ center.z; // + 25.0*cos(u/4.0);

   float s= 5.0;


   float cx = rint(center.x/s)*s;
   float cy = rint(center.y/s)*s;
   float cz = rint(center.z/s)*s;

   float z,d,sx,sy;

   z = -40.0;
   d = s+fabs(cz) + fabs(z);

   sx = floor((d)/s)*s;
   sy = s+floor((d*0.75)/s)*s;


   int w = (int)(sx*2.0/s);
   int h = (int)(sy*2.0/s);

   int n_verts = (h+1)*2;

   unsigned char *v = strips;
   //float *c = cols;

   for(float x=-sx; x<sx; x+=s) {
      //glBegin(GL_TRIANGLE_STRIP);
      for(float y=-sy; y<=sy; y+=s) {
         //glColor4f(0.5, 0.5, 0.0, 1.0);
         vector4 cc = palette[plasma(cx+ux+x, cy+uy+y, uz+z)&0xff] * 0.5;
         *v++ = (unsigned char)(cc.x*255.0);
         *v++ = (unsigned char)(cc.y*255.0);
         *v++ = (unsigned char)(cc.z*255.0);
         *v++ = 0xff;
         //glVertex3f(x, y, 0.0);
         *((float *)v) = x;
         v += sizeof(float);
         *((float *)v) = y;
         v += sizeof(float);
         *((float *)v) = 0.0;
         v += sizeof(float);
         v += sizeof(float);
         //glColor4f(0.0, 0.5, 0.5, 1.0);
         cc = palette[plasma(cx+ux+x+s, cy+uy+y, uz+z)&0xff] * 0.5;
         *v++ = (unsigned char)(cc.x*255.0);
         *v++ = (unsigned char)(cc.y*255.0);
         *v++ = (unsigned char)(cc.z*255.0);
         *v++ = 0xff;
         //glVertex3f(x+s, y, 0.0);
         *((float *)v) = x+s;
         v += sizeof(float);
         *((float *)v) = y;
         v += sizeof(float);
         *((float *)v) = 0.0;
         v += sizeof(float);
         v += sizeof(float);
      }
      //glEnd();
   }


}

void Background::render() {

//center.z *= 0.5;
#if 0
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



   float dd;

   float z = f;
//#if 0

   int t = SDL_GetTicks();

   glClear(GL_COLOR_BUFFER_BIT);

   // use quad strip
   glBegin(GL_QUADS);
//   for(int i=0; i<p; i++) {
      //z += zs;
      dd = fabs(z)-cz;

      int w = (int)((dd*2.0+1)/s);
      int h = (int)((dd*2.0*0.75+1)/s);

      float y = cy-(h*s/2.0);
      for(int i=0; i<h; i++) {
         for(float x=cx-dd; x<=cx+dd; x+=s) {
             vector4 c;
             c = palette[plasma(ux+x, uy+y, uz+z)&0xff] * 0.5;
             glColor4f(c.x, c.y, c.z, 1.0);
             glColor4f(1.0, 0.0, 0.0, 1.0);
             glVertex3f(x, y, z);

             c = palette[plasma(ux+x+s, uy+y, uz+z)&0xff] * 0.5;
             glColor4f(c.x, c.y, c.z, 1.0);
             glColor4f(0.0, 1.0, 0.0, 1.0);
             glVertex3f(x+s, y, z);

             c = palette[plasma(ux+x+s, uy+y+s, uz+z)&0xff] * 0.5;
             glColor4f(c.x, c.y, c.z, 1.0);
             glColor4f(0.0, 0.0, 1.0, 1.0);
             glVertex3f(x+s, y+s, z);

             c = palette[plasma(ux+x, uy+y+s, uz+z)&0xff] * 0.5;
             glColor4f(c.x, c.y, c.z, 1.0);
             glColor4f(1.0, 1.0, 0.0, 1.0);
             glVertex3f(x, y+s, z);

         }
         y += s;
      }
//   }
   glEnd();

   int plasma_time = SDL_GetTicks();

   float g = s/gap;

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE);

/*
  glBegin(GL_QUADS);
   z = f+zs;
   for(int i=0; i<p; i++) {
      dd = (fabs(z)-cz)*1.0;

      //printf("dd = %f\n", dd);

      dd = fabs(z)-cz;
      for(float y=cy-dd; y<cy+dd+s; y+=s) {
         for(float x=cx-dd; x<cx+dd+s; x+=s) {
             vector4 c;
             c = palette[plasma(ux+x, uy+y, uz+z)&0xff];
             glColor4f(c.x, c.y, c.z, c.w);
             glVertex3f(x+g, y+g, z);

             c = palette[plasma(ux+x+s, uy+y, uz+z)&0xff];
             glColor4f(c.x, c.y, c.z, c.w);
             glVertex3f(x+s-g, y+g, z);

             c = palette[plasma(ux+x+s, uy+y+s, uz+z)&0xff];
             glColor4f(c.x, c.y, c.z, c.w);
             glVertex3f(x+s-g, y+s-g, z);

             c = palette[plasma(ux+x, uy+y+s, uz+z)&0xff];
             glColor4f(c.x, c.y, c.z, c.w);
             glVertex3f(x+g, y+s-g, z);

         }
      }
      z += zs;
   }
   glEnd();
*/

/*
      int tf = 0;

   s = s*2.0;
   cx = floor(center.x/s)*s;
   cy = floor(center.y/s)*s;
   cz = floor(center.z/s)*s;

   z = f+zs;
   for(int i=0; i<p; i++) {
      dd = (fabs(z)-cz)*1.0;

      //printf("dd = %f\n", dd);

if(i==2){
   s = s/2.0;
   cx = floor(center.x/s)*s;
   cy = floor(center.y/s)*s;
   cz = floor(center.z/s)*s;
}

      float offset = 0.0;
      for(float y=cy-dd; y<cy+dd+s; y+=s) {
         for(float x=cx-dd; x<cx+dd+s; x+=s) {

            glBegin(GL_TRIANGLE_FAN);

            float x0 = x+s/2.0;
            float y0 = y+s/2.0;
            float r0 = s*0.4;
            int sides = 6;

               //vector4 c = palette[plasma(ux+y0, uy+x0, uz+z)&0xff];
               //glColor4f(c.x, c.y, c.z, c.w);
               //glVertex3f(x0, y0, z);

            if(i < 2) {
                 vector4 c = palette[plasma(ux+y0, uy+x0+r0, uz+z)&0xff];
                 glColor4f(c.x, c.y, c.z, c.w);
            }

            for(int j=0; j<sides; j++) {
               float angle = 2.0*M_PI/sides*j;
               float x1 = x0+r0*cos(angle);
               float y1 = y0+r0*sin(angle);

               if(i == 2 ) {
                 vector4 c = palette[plasma(ux+y1, uy+x1, uz+z)&0xff];
                 glColor4f(c.x, c.y, c.z, c.w);
               }
               glVertex3f(x1, y1, z);
            }
            glEnd();
            tf++;

         }
      }
      z += zs;
   }

//printf("%d triangles fans\n", tf);


*/


  int tf = 0;

   glEnable(GL_TEXTURE_2D);
   TextureManager::getInstance()->bind(hex_tex);

   z = z+zs;
   for(int i=0; i<p-1; i++) {
      dd = (fabs(z)-cz)*1.0;

      //printf("dd = %f\n", dd);

      float offset = 0.0;
      for(float y=cy-dd; y<cy+dd+s; y+=s) {
         for(float x=cx-dd; x<cx+dd+s; x+=s) {

            glBegin(GL_QUADS);

            float x0 = x+s/2.0;
            float y0 = y+s/2.0;
            float r0 = s*0.4;
            int sides = 4;


               float angle = 2.0*M_PI/sides*0;
               float x1 = x0+r0*cos(angle);
               float y1 = y0+r0*sin(angle);
               vector4 c = palette[plasma(ux+y1, uy+x1, uz+z)&0xff];
               glColor4f(c.x, c.y, c.z, c.w);
               glTexCoord2f(0.0, 0.0);
               glVertex3f(x1, y1, z);


               angle = 2.0*M_PI/sides*1;
               x1 = x0+r0*cos(angle);
               y1 = y0+r0*sin(angle);
               c = palette[plasma(ux+y1, uy+x1, uz+z)&0xff];
               glColor4f(c.x, c.y, c.z, c.w);
               glTexCoord2f(0.0, 1.0);
               glVertex3f(x1, y1, z);

               angle = 2.0*M_PI/sides*2;
               x1 = x0+r0*cos(angle);
               y1 = y0+r0*sin(angle);
               c = palette[plasma(ux+y1, uy+x1, uz+z)&0xff];
               glColor4f(c.x, c.y, c.z, c.w);
               glTexCoord2f(1.0, 1.0);
               glVertex3f(x1, y1, z);


               angle = 2.0*M_PI/sides*3;
               x1 = x0+r0*cos(angle);
               y1 = y0+r0*sin(angle);
               c = palette[plasma(ux+y1, uy+x1, uz+z)&0xff];
               glColor4f(c.x, c.y, c.z, c.w);
               glTexCoord2f(1.0, 0.0);
               glVertex3f(x1, y1, z);

            glEnd();
         }
      }
      z += zs;
   }

   glDisable(GL_TEXTURE_2D);

      dd = (fabs(z)-cz)*1.0;

      //printf("dd = %f\n", dd);

      float offset = 0.0;
      for(float y=cy-dd; y<cy+dd+s; y+=s) {
         for(float x=cx-dd; x<cx+dd+s; x+=s) {

            glBegin(GL_TRIANGLE_FAN);

            float x0 = x+s/2.0;
            float y0 = y+s/2.0;
            float r0 = s*0.4;
            int sides = 6;

               //vector4 c = palette[plasma(ux+y0, uy+x0, uz+z)&0xff];
               //glColor4f(c.x, c.y, c.z, c.w);
               //glVertex3f(x0, y0, z);

            for(int j=0; j<sides; j++) {
               float angle = 2.0*M_PI/sides*j;
               float x1 = x0+r0*cos(angle);
               float y1 = y0+r0*sin(angle);

                 vector4 c = palette[plasma(ux+y1, uy+x1, uz+z)&0xff];
                 glColor4f(c.x, c.y, c.z, c.w);
               glVertex3f(x1, y1, z);
            }
            glEnd();
            tf++;

         }
      }
 
//printf("%d triangles fans\n", tf);




   int hex_time = SDL_GetTicks();
//#endif

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



   int grid_time = SDL_GetTicks();
#endif

 
//   glClear(GL_COLOR_BUFFER_BIT);

   glDisable(GL_LIGHTING);
   glDisable(GL_DEPTH_TEST);

   // grid size
   float s = 5.0;

   // nearest grid from center
   float cx;
   float cy;
   float cz;

   float z, d, sx, sy;

   cx = rint(center.x/s)*s;
   cy = rint(center.y/s)*s;
   cz = rint(center.z/s)*s;

   //printf("c %f %f %f cx %f cy %f cz %f\n", center.x, center.y, center.z, cx, cy, cz);

   glPushMatrix();
   glTranslatef(cx,cy,-40.0);

   z = -40.0;
   d = s+fabs(cz) + fabs(z);

   sx = floor((d)/s)*s;
   sy = s+floor((d*0.75)/s)*s;

   ////printf("0 z %f d %f sx %f sy %f\n", z, d, sx, sy);

/*
   glBegin(GL_LINES);
   glColor4f(0.0, 0.0, 0.5, 1.0);
   for(float y=-sy; y<=sy; y+=s) {
      glVertex3f(-sx, y, 0.0);         
      glVertex3f(sx, y, 0.0);         
   }
   for(float x=-sx; x<=sx; x+=s) {
      glVertex3f(x, sy, 0.0);         
      glVertex3f(x, -sy, 0.0);         
   }
   glEnd();
*/

   int  ct = 0;
   int n = 0;

   int w = (int)(sx*2.0/s);
   int h = (int)(sy*2.0/s);

   int n_verts = (h+1)*2;

   for(int i=0; i<w; i++) {
      glDrawArrays(GL_TRIANGLE_STRIP, i*n_verts, n_verts);
   }

/*
   glBegin(GL_LINES);
    glColor4f(1.0, 1.0, 0.0, 1.0);
    glVertex3f(0.0, 5.0, 0.0);
    glVertex3f(0.0, -5.0, 0.0);
    glVertex3f(-5.0, 0.0, 0.0);
    glVertex3f(5.0, 0.0, 0.0);
   glEnd();
*/


   glPopMatrix();


   glPushMatrix();
   glTranslatef(cx,cy,-10.0);

   

   z = -10.0;
   d = s+fabs(cz) + fabs(z);

   s = s/ 2;

   sx = floor((d)/s)*s;
   sy = floor((d*0.75)/s)*s;

   //printf("1 z %f d %f sx %f sy %f\n", z, d, sx, sy);

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE);

   glBegin(GL_LINES);
   glColor4f(0.75, 0.75, 0.75, 0.1);
   for(float y=-sy; y<=sy; y+=s) {
      glVertex3f(-sx, y, 0.0);         
      glVertex3f(sx, y, 0.0);         
   }
   for(float x=-sx; x<=sx; x+=s) {
      glVertex3f(x, sy, 0.0);         
      glVertex3f(x, -sy, 0.0);         
   }
   glEnd();

/*
   glBegin(GL_LINES);
    glColor4f(1.0, 0.0, 0.0, 1.0);
    glVertex3f(0.0, 5.0, 0.0);
    glVertex3f(0.0, -5.0, 0.0);
    glVertex3f(-5.0, 0.0, 0.0);
    glVertex3f(5.0, 0.0, 0.0);
   glEnd();
*/

   glPopMatrix();






   glEnable(GL_LIGHTING);
   glEnable(GL_DEPTH_TEST);
   glDisable(GL_BLEND);


//   printf("plasma %d hex %d grid %d total %d\n", plasma_time-t, hex_time-plasma_time, grid_time-hex_time, grid_time-t);

}

