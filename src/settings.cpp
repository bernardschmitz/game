
#include "settings.h"

Settings settings = Settings();


Settings::Settings() { 

   screen_width = 800;
   screen_height = 600;

   world_width = 1000.0;
   world_height = 1000.0;

   background_far = -45.0;
   background_near = -15.0;
   background_step = 8.0;
   background_width = 1000.0;
   background_height = 1000.0;
   background_gap = 1.0;

}

