
#include "settings.h"

Settings settings = Settings();


Settings::Settings() { 

   screen_width = 800;
   screen_height = 600;

   world_width = 1000.0;
   world_height = 1000.0;

   background_far = -40.0; //-80.0;
   background_near = -20.0;
   background_step = 5.0;
   background_planes = 3.0;
   background_width = 1000.0;
   background_height = 1000.0;
   background_gap = 8.0;

}

