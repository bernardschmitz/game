
#include "background.h"
#include "settings.h"

Background::Background() {



   // default
   static sgVec4 map[8] = { { 0.25, 0.0, 0.0, 0.1 },
                            { 0.0, 0.25, 0.0, 0.1 },
                            { 0.0, 0.0, 0.25, 0.1 },
                            { 0.25, 0.25, 0.0, 0.1 },
                            { 0.25, 0.0, 0.25, 0.1 },
                            { 0.25, 0.25, 0.25, 0.1 },
                            { 0.0, 0.25, 0.25, 0.1 },
                            { 0.25, 0.25, 0.25, 0.5 }  };


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
   static sgVec4 map[9] = { { 1.0, 0.0, 0.0, 0.125 },
                            { 1.0, 1.0, 0.0, 0.25 },
                            { 1.0, 0.0, 0.0, 0.125 },
                            { 1.0, 1.0, 0.0, 0.125 },
                            { 1.0, 1.0, 1.0, 0.25 },
                            { 1.0, 1.0, 0.0, 0.125 },
                            { 1.0, 0.0, 0.0, 0.25 },
                            { 1.0, 1.0, 0.0, 0.125 },
                            { 1.0, 0.0, 0.0, 0.125 }  };
*/
   palette = new sgVec4[256];

   for(int i=0; i<8; i++) {
      for(int j=0; j<32; j++) {
         sgLerpVec4(palette[i*32+j], map[i], map[(i+1)&0x7], j/32.0);
         printf("%d : %f %f %f\n", i*32+j, palette[i*32+j][0], palette[i*32+j][1], palette[i*32+j][2]);
      }
   }

}


Background::~Background() {

   delete [] palette;
}

int plasma(float x, float y, float z) {
   float k = (sin(sqrt(x*x+y*y)/16.0) + cos(sqrt(x*x+z*z)/-23.0)) / 2.0;
   //float k = sin(sqrt(x*x+y*y+z*z)/16.0) + cos(40.0+sqrt(y*y+z*z)/32.0) +  sin(90.0+sqrt(x*x+z*z)/6.0) + cos(-40.0+sqrt(z*z)/43.0);
   //float k = (sin(x*M_PI/40.0)*cos(y*M_PI/70.0)+sin(z*M_PI/80.0)) / 2.0;
   return int(128.0+127.0*k);


   //float k =  sin( x/(37.0+15.0*cos(y/74.0)) ) * cos( x/(31.0+11.0*sin(z/57.0))) ;
   //float k = (sin(x/50) + sin(z/40) + cos(y/90))/3.0 ;

   //return sin(sqrt(x*x)/20.0)*sin(sqrt(y*y)/20.0)*sin(sqrt(z*z)/20.0);
   //float k = sin(40.0+cos(x/20.0))+sin(y/20.0)+sin(z/20.0);
   //return sin( x/(37.0+15.0*cos(y/74.0)) ) * cos( x/(31.0+11.0*sin(z/57.0))) ;
}


void Background::render(sgVec3 center, int flags) {


   glDisable(GL_LIGHTING);
   glDisable(GL_DEPTH_TEST);

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE);


   float s = settings.background_step;
   float n = settings.background_near;
   float f = settings.background_far;
   float gap = settings.background_gap;

   float cx = floor(center[0]/s)*s;
   float cy = floor(center[1]/s)*s;


   sgVec4 white = { 0.5, 0.5, 0.5, 0.5 };
   glColor4fv(white);

   static float u = 0.0;

   u += M_PI/200.0;

   float ux = 20.0*cos(u);
   float uy = 45.0*sin(u) + 15.0*cos(u/2.0);
   float uz = 35.0*cos(u) + 25.0*cos(u/4.0);

   if(flags) {
      s = 2.0;
      n = f; 
   }

   glBegin(GL_QUADS);
   for(float d=f; d<n+s; d+=s) {
      float dd = fabs(d);
      for(float y=cy-dd; y<cy+dd+s; y+=s) {
         for(float x=cx-dd; x<cx+dd+s; x+=s) {
             glColor4fv(palette[plasma(ux+x+s, uy+y+s, uz+d)&0xff]);
             glVertex3f(x, y, d);

             glColor4fv(palette[plasma(ux+x, uy+y+s, uz+d)&0xff]);
             glVertex3f(x+s, y, d);

             glColor4fv(palette[plasma(ux+x, uy+y, uz+d)&0xff]);
             glVertex3f(x+s, y+s, d);

             glColor4fv(palette[plasma(ux+x+s, uy+y, uz+d)&0xff]);
             glVertex3f(x, y+s, d);

         }
      }
   }
   glEnd();

   glBegin(GL_LINES);

   glColor4fv(white);

   for(float d=f; d<n+s; d+=s) {
      float dd = fabs(d)+s;
      for(float y=cy-dd; y<cy+dd+s; y+=s) {
         glVertex3f(cx-dd, y, d);
         glVertex3f(cx+dd, y, d);
      }
      for(float x=cx-dd; x<cx+dd+s; x+=s) {
         glVertex3f(x, cy-dd, d);
         glVertex3f(x, cy+dd, d);
      }
   }

   glEnd();


   glEnable(GL_LIGHTING);
   glEnable(GL_DEPTH_TEST);
   glDisable(GL_BLEND);

}

