
#ifndef __SETTINGS_H__
#define __SETTINGS_H__

struct Settings { 

   int screen_width;
   int screen_height;

   float world_width;
   float world_height;
   
   float background_near;
   float background_far;
   float background_step;
   float background_planes;
   float background_width;   
   float background_height;   
   float background_gap;   

   Settings();

};

extern Settings settings;

#endif

