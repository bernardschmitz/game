
#include <assert.h>

#include "background.h"
#include "settings.h"
#include "player.h"
#include "texture.h"

Background::Background() : Actor(ACT_BACKGROUND, "Background") {


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



   palette = new unsigned char[256*4];

   vector4 vv;

   for(int i=0; i<8; i++) {
      for(int j=0; j<32; j++) {

         vv.linear_interpolate(map[i], map[(i+1)&0x07], j/32.0);

         palette[i*32*4+j*4+0] = (int)(vv.x*255.0)&0xff;
         palette[i*32*4+j*4+1] = (int)(vv.y*255.0)&0xff;
         palette[i*32*4+j*4+2] = (int)(vv.z*255.0)&0xff;
         palette[i*32*4+j*4+3] = (int)(vv.w*255.0)&0xff;

         //palette[i*32+j] = map[i]*(1.0f-j/32.0f) + map[(i+1)&0x7]*j/32.0f;

         //printf("%d : %f %f %f\n", i*32+j, palette[i*32+j][0], palette[i*32+j][1], palette[i*32+j][2]);
      }
   }

   half_palette = new unsigned char[256*4];

   for(int i=0; i<256*4; i++)
      half_palette[i] = palette[i]>>1;

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

   strips = new Vertex[n_verts*w];

   //glInterleavedArrays(GL_C4UB_V3F, 0, strips);

   glEnableClientState(GL_VERTEX_ARRAY);
//   glVertexPointer(3, GL_FLOAT, sizeof(vert), &strips[0].x);
   glEnableClientState(GL_COLOR_ARRAY);
//   glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(vert), strips);

   Vertex *v = strips;

   // create grid of w strips of 2*h vertices
   float x = -sx;
   for(int i=0; i<w; i++) {
      float y = -sy;
      for(int j=0; j<=h; j++) {
         v->x = x;
         v->y = y;
         v->z = 0.0;
         ++v;

         v->x = x+s;
         v->y = y;
         v->z = 0.0;
         ++v;

         y += s;
      }
      x += s;
   }

   max_w = w;
   max_h = h;
   max_v = n_verts;

   printf("max w %d h %d v %d\n", max_w, max_h, max_v);






   int p = 1;
   float z = -20.0f;

   d = s+fabs(-45) + fabs(z);

   sx = floor((d)/s)*s;
   sy = s+floor((d*0.75)/s)*s;

   w = (int)(sx*2.0/s);
   h = (int)(sy*2.0/s);

   max_hv = h*6;

   hexes = new Vertex[max_hv*w];

   Vertex *hv = hexes;

   float zs = -10.0f;
//   for(int i=0; i<p; i++) {
      for(float x=-sx; x<sx; x+=s) {
         for(float y=-sy; y<sy; y+=s) {

//            glBegin(GL_TRIANGLE_FAN);

            float x0 = x+s/2.0;
            float y0 = y+s/2.0;
            float r0 = s*0.4;
            int sides = 6;

            for(int j=0; j<sides; j++) {
               float angle = 2.0*M_PI/sides*j;
               float x1 = x0+r0*cos(angle);
               float y1 = y0+r0*sin(angle);

               //int c = plasma(cx+ux+y1, cy+uy+x1, uz+z)&0xff;

               //glColor4ub(palette[c*4+0], palette[c*4+1], palette[c*4+2], palette[c*4+3]);

               hv->r = 0xff;
               hv->g = 0xff*j/sides;
               hv->b = 0x00;
               hv->a = 0xff;
               
               //glVertex3f(x1, y1, 0.0);
               hv->x = x1;
               hv->y = y1;
               hv->z = 0.0f;

               ++hv;
            }
//            glEnd();

         }
      }

      z += zs;
//   }


   max_hw = w;
   max_hh = h;

   printf("max hex w %d h %d v %d\n", max_hw, max_hh, max_hv);

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



void Background::action(float dt) {


   float s= 5.0;
   assert(center.z > -45.0);

   cx = rint(center.x/s)*s;
   cy = rint(center.y/s)*s;
   cz = rint(center.z/s)*s;


   static float rate = 1.0/30.0;
   static float now = 0.0;

   bool update = true;

   now -= dt;

   if(now > 0.0)
      return;

   now = rate;
 

   //u += M_PI/400.0*50.0*dt;
   u += M_PI/400.0*50.0*rate;

   ux = 20.0*cos(u) ;// + center.x;
   uy = 45.0*sin(u) ;//+ center.y; // + 15.0*cos(u/2.0);
   uz = 35.0*cos(u) ;//+ center.z; // + 25.0*cos(u/4.0);

   float z,d,sx,sy;

   z = -40.0;
   d = s+fabs(-45) + fabs(z);

   sx = floor((d)/s)*s;
   sy = s+floor((d*0.75)/s)*s;


   int w = (int)(sx*2.0/s);
   int h = (int)(sy*2.0/s);

   int n_verts = (h+1)*2;

   int isx = (int)((cx-sx)/s);
   int isy = (int)((cy-sy)/s);

   int buf_o = n_verts*isx + 2*isy;

   int buf_l = 2 * (int)(2*sy/s);







   z = -40.0;
   d = s+fabs(cz) + fabs(z);

   sx = floor((d)/s)*s;
   sy = s+floor((d*0.75)/s)*s;


   w = (int)(sx*2.0/s);
   h = (int)(sy*2.0/s);

   n_verts = (h+1)*2;

   int ow = (max_w - w) / 2;
   int oh = (max_h - h) / 2;

   idx = ow*max_v+oh*2;

   //printf("cx %f cy %f cz %f w %d h %d sx %f sy %f isx %d isy %d n_verts %d buf_o %d buf_l %d\n", cx, cy, cz, w, h, sx, sy, isx, isy, n_verts, buf_o, buf_l);
   //printf("ow %d oy %d idx %d\n", ow, oh, idx);


   //float *c = cols;
if(update) {
   for(int i=0; i<w; i++) {
      Vertex *v = &strips[idx+i*max_v];

      for(int j=0; j<=h; j++) {

         int cc = plasma(cx+ux+v->x, cy+uy+v->y, uz+z)&0xff;

         v->r = half_palette[cc*4+0];
         v->g = half_palette[cc*4+1];
         v->b = half_palette[cc*4+2];
         v->a = 0xff;

         ++v;

         cc = plasma(cx+ux+v->x, cy+uy+v->y, uz+z)&0xff;

         v->r = half_palette[cc*4+0];
         v->g = half_palette[cc*4+1];
         v->b = half_palette[cc*4+2];
         v->a = 0xff;

         ++v;


      }
   }
}


   z = -20.0;
   d = s+fabs(cz) + fabs(z);

   sx = floor((d)/s)*s;
   sy = s+floor((d*0.75)/s)*s;


   w = (int)(sx*2.0/s);
   h = (int)(sy*2.0/s);

   int p = 1;

   ow = (max_hw - w) / 2;
   oh = (max_hh - h) / 2;

   int vi = ow*max_hv+6*oh;

   float zs = -10.0f;

if(update) {

   for(int i=0; i<w; i++) {
         Vertex *v = &hexes[vi + i*max_hv];

      for(int j=0; j<h*6; j++) {

//            glBegin(GL_TRIANGLE_FAN);

               int c = plasma(cx+ux+v->x, cy+uy+v->y, uz+z)&0xff;

               //glColor4ub(palette[c*4+0], palette[c*4+1], palette[c*4+2], palette[c*4+3]);

               v->r = palette[c*4+0];
               v->g = palette[c*4+1];
               v->b = palette[c*4+2];
               v->a = palette[c*4+3];

               ++v;
//            glEnd();

         }
      }

      z += zs;
}

}

void Background::render() {



   glDisable(GL_LIGHTING);
   glDisable(GL_DEPTH_TEST);

   // grid size
   float s = 5.0;

   // nearest grid from center

   float z, d, sx, sy;

#if 0
/*
   cx = rint(center.x/s)*s;
   cy = rint(center.y/s)*s;
   cz = rint(center.z/s)*s;
*/
   //printf("c %f %f %f cx %f cy %f cz %f\n", center.x, center.y, center.z, cx, cy, cz);

   glPushMatrix();
   glTranslatef(cx,cy,-40.0);

   z = -40.0;
   d = s+fabs(cz) + fabs(z);

   sx = floor((d)/s)*s;
   sy = s+floor((d*0.75)/s)*s;


   int  ct = 0;
   int n = 0;

   int w = (int)(sx*2.0/s);
   int h = (int)(sy*2.0/s);

   int n_verts = (h+1)*2;

   //printf("idx %d n_Verts %d\n", idx, n_verts);

//   glClear(GL_COLOR_BUFFER_BIT);


   glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &strips[0].x);
   glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex), strips);

   for(int i=0; i<w; i++) {
      int l = idx+i*max_v;
      glDrawArrays(GL_TRIANGLE_STRIP, l, n_verts);
   }

   glPopMatrix();


   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE);

   glPushMatrix();
   z = -20.0;

   glTranslatef(cx,cy,z);

   glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &hexes[0].x);
   glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex), hexes);


   d = s+fabs(cz) + fabs(z);

   sx = floor((d)/s)*s;
   sy = s+floor((d*0.75)/s)*s;

   w = (int)(sx*2.0/s);
   h = (int)(sy*2.0/s);

   int ow = (max_hw - w) / 2;
   int oh = (max_hh - h) / 2;

   int k = ow*max_hv+oh*6;
   assert(k >= 0);

   for(int i=0; i<w; i++) {
      for(int j=0; j<h; j++) {
         glDrawArrays(GL_TRIANGLE_FAN, k+j*6, 6);
      }
      k += max_hv;
   }
   
   glPopMatrix();






   glPopMatrix();

#endif


   // TODO remove this
   //glClearColor(0.0, 0.0, 0.6, 1.0);
   glClear(GL_COLOR_BUFFER_BIT);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE);


   glPushMatrix();
   glTranslatef(cx,cy,-10.0);

   

   z = -10.0;
   d = s+fabs(cz) + fabs(z);

   s = s/ 2;

   sx = s+floor((d)/s)*s;
   sy = s+floor((d*0.75)/s)*s;

   //printf("1 z %f d %f sx %f sy %f\n", z, d, sx, sy);

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


   glPopMatrix();






   glEnable(GL_LIGHTING);
   glEnable(GL_DEPTH_TEST);
   glDisable(GL_BLEND);


//   printf("plasma %d hex %d grid %d total %d\n", plasma_time-t, hex_time-plasma_time, grid_time-hex_time, grid_time-t);

}

