
#include "player.h"

#include "input.h"
#include "settings.h"
#include "enemy.h"
#include "particle.h"
#include "random.h"

Player *player = NULL;

Player::Player() {

   position.set(0.0f, 0.0f, -10.0f);
   velocity.set(0.0f, 0.0f, 0.0f);

   z_rotation = 0.0;

   thrusting = 0;
   shooting = 0;


   dl_cockpit = glGenLists(5);

   printf("dl_cockpit = %d\n", dl_cockpit);
   
// blue material
static GLfloat mat_0_diffuse[] = { 0.225564, 0.273684, 0.108271, 1.000000 };
static GLfloat mat_0_ambient[] = { 0.112782, 0.136842, 0.054135, 1.0 };
static GLfloat mat_0_specular[] = { 0.669308, 0.432385, 0.000000, 1.0 };
static GLfloat mat_0_emission[] = { 0.000000, 0.000000, 0.000000, 1.0 };
static GLfloat mat_0_shine = 112.439216;
// blue.001 material
static GLfloat mat_1_diffuse[] = { 0.071111, 0.253784, 0.278197, 1.000000 };
static GLfloat mat_1_ambient[] = { 0.035555, 0.126892, 0.139098, 1.0 };
static GLfloat mat_1_specular[] = { 0.294823, 0.421626, 0.306765, 1.0 };
static GLfloat mat_1_emission[] = { 0.000000, 0.000000, 0.000000, 1.0 };
static GLfloat mat_1_shine = 42.164706;
// green material
static GLfloat mat_2_diffuse[] = { 0.210526, 0.348872, 0.060150, 1.000000 };
static GLfloat mat_2_ambient[] = { 0.105263, 0.174436, 0.030075, 1.0 };
static GLfloat mat_2_specular[] = { 0.527154, 0.787770, 0.000000, 1.0 };
static GLfloat mat_2_emission[] = { 0.000000, 0.000000, 0.000000, 1.0 };
static GLfloat mat_2_shine = 84.329412;
// grey material
static GLfloat mat_3_diffuse[] = { 0.195489, 0.481203, 0.000000, 1.000000 };
static GLfloat mat_3_ambient[] = { 0.097744, 0.240601, 0.000000, 1.0 };
static GLfloat mat_3_specular[] = { 0.458160, 0.541462, 0.000000, 1.0 };
static GLfloat mat_3_emission[] = { 0.000000, 0.000000, 0.000000, 1.0 };
static GLfloat mat_3_shine = 94.870588;


// cockpit.002

   glNewList(dl_cockpit+0, GL_COMPILE);

 glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_1_diffuse);
 glMaterialfv(GL_FRONT, GL_AMBIENT, mat_1_ambient);
 glMaterialfv(GL_FRONT, GL_SPECULAR, mat_1_specular);
 glMaterialf(GL_FRONT, GL_SHININESS, mat_1_shine);
 glMaterialfv(GL_FRONT, GL_EMISSION, mat_1_emission);
glBegin(GL_TRIANGLES);
  glNormal3f(-0.422864, 0.113376, 0.899045);
  glVertex3f(-0.272303, -0.133636, 0.383475);
  glNormal3f(0.000000, 0.244972, 0.969512);
  glVertex3f(-0.000000, 0.460622, 0.436603);
  glNormal3f(-0.525193, 0.211585, 0.824244);
  glVertex3f(-0.377465, 0.387925, 0.214742);
  glNormal3f(0.000000, 0.244972, 0.969512);
  glVertex3f(-0.000000, 0.460622, 0.436603);
  glNormal3f(0.422864, 0.113376, 0.899045);
  glVertex3f(0.272303, -0.133636, 0.383475);
  glNormal3f(0.525193, 0.211585, 0.824244);
  glVertex3f(0.377465, 0.387925, 0.214742);
  glNormal3f(0.000000, 0.074862, 0.997192);
  glVertex3f(0.000000, -0.066485, 0.476179);
  glNormal3f(0.422864, 0.113376, 0.899045);
  glVertex3f(0.272303, -0.133636, 0.383475);
  glNormal3f(0.000000, 0.244972, 0.969512);
  glVertex3f(-0.000000, 0.460622, 0.436603);
  glNormal3f(0.000000, 0.074862, 0.997192);
  glVertex3f(0.000000, -0.066485, 0.476179);
  glNormal3f(0.000000, 0.244972, 0.969512);
  glVertex3f(-0.000000, 0.460622, 0.436603);
  glNormal3f(-0.422864, 0.113376, 0.899045);
  glVertex3f(-0.272303, -0.133636, 0.383475);
  glNormal3f(0.000000, 0.330638, 0.943754);
  glVertex3f(-0.000000, 1.017013, 0.241674);
  glNormal3f(0.000000, 0.244972, 0.969512);
  glVertex3f(-0.000000, 0.460622, 0.436603);
  glNormal3f(0.525193, 0.211585, 0.824244);
  glVertex3f(0.377465, 0.387925, 0.214742);
  glNormal3f(0.000000, 0.330638, 0.943754);
  glVertex3f(-0.000000, 1.017013, 0.241674);
  glNormal3f(-0.525193, 0.211585, 0.824244);
  glVertex3f(-0.377465, 0.387925, 0.214742);
  glNormal3f(0.000000, 0.244972, 0.969512);
  glVertex3f(-0.000000, 0.460622, 0.436603);
 glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_0_diffuse);
 glMaterialfv(GL_FRONT, GL_AMBIENT, mat_0_ambient);
 glMaterialfv(GL_FRONT, GL_SPECULAR, mat_0_specular);
 glMaterialf(GL_FRONT, GL_SHININESS, mat_0_shine);
 glMaterialfv(GL_FRONT, GL_EMISSION, mat_0_emission);
  glNormal3f(-0.893857, 0.371014, 0.251717);
  glVertex3f(-0.940514, 0.212359, 0.123862);
  glNormal3f(-0.692251, 0.444258, 0.568651);
  glVertex3f(-0.385512, 0.781300, -0.064236);
  glNormal3f(-0.823237, -0.392560, 0.410047);
  glVertex3f(-0.940514, -0.403633, -0.157114);
  glNormal3f(0.000000, -0.763359, 0.645924);
  glVertex3f(0.000000, -1.000000, 0.000000);
  glNormal3f(0.000000, -0.674398, 0.738334);
  glVertex3f(-0.000000, -0.845510, 0.182575);
  glNormal3f(-0.823237, -0.392560, 0.410047);
  glVertex3f(-0.940514, -0.403633, -0.157114);
  glNormal3f(-0.369610, 0.422926, 0.827326);
  glVertex3f(-0.377465, 0.387925, 0.214742);
  glNormal3f(-0.692251, 0.444258, 0.568651);
  glVertex3f(-0.385512, 0.781300, -0.064236);
  glNormal3f(-0.893857, 0.371014, 0.251717);
  glVertex3f(-0.940514, 0.212359, 0.123862);
  glNormal3f(-0.484695, -0.413648, 0.770653);
  glVertex3f(-0.582912, -0.395008, 0.239925);
  glNormal3f(-0.823237, -0.392560, 0.410047);
  glVertex3f(-0.940514, -0.403633, -0.157114);
  glNormal3f(0.000000, -0.674398, 0.738334);
  glVertex3f(-0.000000, -0.845510, 0.182575);
  glNormal3f(0.000000, -0.346538, 0.938017);
  glVertex3f(0.000000, -0.457044, 0.366407);
  glNormal3f(-0.278207, -0.113712, 0.953734);
  glVertex3f(-0.272303, -0.133636, 0.383475);
  glNormal3f(-0.484695, -0.413648, 0.770653);
  glVertex3f(-0.582912, -0.395008, 0.239925);
  glNormal3f(-0.692251, 0.444258, 0.568651);
  glVertex3f(-0.385512, 0.781300, -0.064236);
  glNormal3f(0.000000, 0.372814, 0.927885);
  glVertex3f(-0.000000, 1.017013, 0.241674);
  glNormal3f(0.000000, 0.294900, 0.955504);
  glVertex3f(0.000000, 1.800000, 0.000000);
  glNormal3f(0.823237, -0.392560, 0.410047);
  glVertex3f(0.940514, -0.403633, -0.157114);
  glNormal3f(0.692251, 0.444258, 0.568651);
  glVertex3f(0.385512, 0.781300, -0.064236);
  glNormal3f(0.893857, 0.371014, 0.251717);
  glVertex3f(0.940514, 0.212359, 0.123862);
  glNormal3f(0.000000, -0.763359, 0.645924);
  glVertex3f(0.000000, -1.000000, 0.000000);
  glNormal3f(0.823237, -0.392560, 0.410047);
  glVertex3f(0.940514, -0.403633, -0.157114);
  glNormal3f(0.000000, -0.674398, 0.738334);
  glVertex3f(-0.000000, -0.845510, 0.182575);
  glNormal3f(0.000000, 0.372814, 0.927885);
  glVertex3f(-0.000000, 1.017013, 0.241674);
  glNormal3f(0.369610, 0.422926, 0.827326);
  glVertex3f(0.377465, 0.387925, 0.214742);
  glNormal3f(0.692251, 0.444258, 0.568651);
  glVertex3f(0.385512, 0.781300, -0.064236);
  glNormal3f(0.893857, 0.371014, 0.251717);
  glVertex3f(0.940514, 0.212359, 0.123862);
  glNormal3f(0.484695, -0.413648, 0.770653);
  glVertex3f(0.582912, -0.395008, 0.239925);
  glNormal3f(0.823237, -0.392560, 0.410047);
  glVertex3f(0.940514, -0.403633, -0.157114);
  glNormal3f(0.484695, -0.413648, 0.770653);
  glVertex3f(0.582912, -0.395008, 0.239925);
  glNormal3f(0.278207, -0.113712, 0.953734);
  glVertex3f(0.272303, -0.133636, 0.383475);
  glNormal3f(0.000000, -0.346538, 0.938017);
  glVertex3f(0.000000, -0.457044, 0.366407);
  glNormal3f(0.000000, 0.294900, 0.955504);
  glVertex3f(0.000000, 1.800000, 0.000000);
  glNormal3f(0.000000, 0.372814, 0.927885);
  glVertex3f(-0.000000, 1.017013, 0.241674);
  glNormal3f(0.692251, 0.444258, 0.568651);
  glVertex3f(0.385512, 0.781300, -0.064236);
  glNormal3f(0.278207, -0.113712, 0.953734);
  glVertex3f(0.272303, -0.133636, 0.383475);
  glNormal3f(0.484695, -0.413648, 0.770653);
  glVertex3f(0.582912, -0.395008, 0.239925);
  glNormal3f(0.893857, 0.371014, 0.251717);
  glVertex3f(0.940514, 0.212359, 0.123862);
  glNormal3f(0.000000, -0.346538, 0.938017);
  glVertex3f(0.000000, -0.457044, 0.366407);
  glNormal3f(0.278207, -0.113712, 0.953734);
  glVertex3f(0.272303, -0.133636, 0.383475);
  glNormal3f(0.000000, -0.270577, 0.962676);
  glVertex3f(0.000000, -0.066485, 0.476179);
  glNormal3f(0.000000, -0.674398, 0.738334);
  glVertex3f(-0.000000, -0.845510, 0.182575);
  glNormal3f(0.484695, -0.413648, 0.770653);
  glVertex3f(0.582912, -0.395008, 0.239925);
  glNormal3f(0.000000, -0.346538, 0.938017);
  glVertex3f(0.000000, -0.457044, 0.366407);
  glNormal3f(0.369610, 0.422926, 0.827326);
  glVertex3f(0.377465, 0.387925, 0.214742);
  glNormal3f(0.278207, -0.113712, 0.953734);
  glVertex3f(0.272303, -0.133636, 0.383475);
  glNormal3f(0.893857, 0.371014, 0.251717);
  glVertex3f(0.940514, 0.212359, 0.123862);
  glNormal3f(0.484695, -0.413648, 0.770653);
  glVertex3f(0.582912, -0.395008, 0.239925);
  glNormal3f(0.000000, -0.674398, 0.738334);
  glVertex3f(-0.000000, -0.845510, 0.182575);
  glNormal3f(0.823237, -0.392560, 0.410047);
  glVertex3f(0.940514, -0.403633, -0.157114);
  glNormal3f(0.369610, 0.422926, 0.827326);
  glVertex3f(0.377465, 0.387925, 0.214742);
  glNormal3f(0.893857, 0.371014, 0.251717);
  glVertex3f(0.940514, 0.212359, 0.123862);
  glNormal3f(0.692251, 0.444258, 0.568651);
  glVertex3f(0.385512, 0.781300, -0.064236);
  glNormal3f(0.000000, -0.270577, 0.962676);
  glVertex3f(0.000000, -0.066485, 0.476179);
  glNormal3f(-0.278207, -0.113712, 0.953734);
  glVertex3f(-0.272303, -0.133636, 0.383475);
  glNormal3f(0.000000, -0.346538, 0.938017);
  glVertex3f(0.000000, -0.457044, 0.366407);
  glNormal3f(-0.893857, 0.371014, 0.251717);
  glVertex3f(-0.940514, 0.212359, 0.123862);
  glNormal3f(-0.484695, -0.413648, 0.770653);
  glVertex3f(-0.582912, -0.395008, 0.239925);
  glNormal3f(-0.278207, -0.113712, 0.953734);
  glVertex3f(-0.272303, -0.133636, 0.383475);
  glNormal3f(0.000000, -0.674398, 0.738334);
  glVertex3f(-0.000000, -0.845510, 0.182575);
  glNormal3f(0.000000, -0.346538, 0.938017);
  glVertex3f(0.000000, -0.457044, 0.366407);
  glNormal3f(-0.484695, -0.413648, 0.770653);
  glVertex3f(-0.582912, -0.395008, 0.239925);
  glNormal3f(-0.893857, 0.371014, 0.251717);
  glVertex3f(-0.940514, 0.212359, 0.123862);
  glNormal3f(-0.278207, -0.113712, 0.953734);
  glVertex3f(-0.272303, -0.133636, 0.383475);
  glNormal3f(-0.369610, 0.422926, 0.827326);
  glVertex3f(-0.377465, 0.387925, 0.214742);
  glNormal3f(-0.484695, -0.413648, 0.770653);
  glVertex3f(-0.582912, -0.395008, 0.239925);
  glNormal3f(-0.893857, 0.371014, 0.251717);
  glVertex3f(-0.940514, 0.212359, 0.123862);
  glNormal3f(-0.823237, -0.392560, 0.410047);
  glVertex3f(-0.940514, -0.403633, -0.157114);
  glNormal3f(0.000000, 0.372814, 0.927885);
  glVertex3f(-0.000000, 1.017013, 0.241674);
  glNormal3f(-0.692251, 0.444258, 0.568651);
  glVertex3f(-0.385512, 0.781300, -0.064236);
  glNormal3f(-0.369610, 0.422926, 0.827326);
  glVertex3f(-0.377465, 0.387925, 0.214742);
  glNormal3f(0.013825, 0.060854, -0.998047);
  glVertex3f(-0.385512, 0.781300, -0.064236);
  glNormal3f(0.000000, -0.039460, -0.999207);
  glVertex3f(-0.000000, -0.262944, -0.122576);
  glNormal3f(0.041353, -0.031373, -0.998627);
  glVertex3f(-0.940514, -0.403633, -0.157114);
  glNormal3f(0.041353, -0.031373, -0.998627);
  glVertex3f(-0.940514, -0.403633, -0.157114);
  glNormal3f(0.000000, -0.039460, -0.999207);
  glVertex3f(-0.000000, -0.262944, -0.122576);
  glNormal3f(0.000000, -0.164037, -0.986450);
  glVertex3f(0.000000, -1.000000, 0.000000);
  glNormal3f(0.000000, -0.039460, -0.999207);
  glVertex3f(-0.000000, -0.262944, -0.122576);
  glNormal3f(0.013825, 0.060854, -0.998047);
  glVertex3f(-0.385512, 0.781300, -0.064236);
  glNormal3f(0.000000, 0.059297, -0.998230);
  glVertex3f(0.000000, 1.800000, 0.000000);
  glNormal3f(-0.041353, -0.031373, -0.998627);
  glVertex3f(0.940514, -0.403633, -0.157114);
  glNormal3f(0.000000, -0.039460, -0.999207);
  glVertex3f(-0.000000, -0.262944, -0.122576);
  glNormal3f(-0.013825, 0.060854, -0.998047);
  glVertex3f(0.385512, 0.781300, -0.064236);
  glNormal3f(0.000000, -0.164037, -0.986450);
  glVertex3f(0.000000, -1.000000, 0.000000);
  glNormal3f(0.000000, -0.039460, -0.999207);
  glVertex3f(-0.000000, -0.262944, -0.122576);
  glNormal3f(-0.041353, -0.031373, -0.998627);
  glVertex3f(0.940514, -0.403633, -0.157114);
  glNormal3f(0.000000, -0.039460, -0.999207);
  glVertex3f(-0.000000, -0.262944, -0.122576);
  glNormal3f(0.000000, 0.059297, -0.998230);
  glVertex3f(0.000000, 1.800000, 0.000000);
  glNormal3f(-0.013825, 0.060854, -0.998047);
  glVertex3f(0.385512, 0.781300, -0.064236);
glEnd();

glEndList();

// engine
 dl_right_engine = dl_cockpit + 1;
 glNewList(dl_right_engine, GL_COMPILE);

 glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_3_diffuse);
 glMaterialfv(GL_FRONT, GL_AMBIENT, mat_3_ambient);
 glMaterialfv(GL_FRONT, GL_SPECULAR, mat_3_specular);
 glMaterialf(GL_FRONT, GL_SHININESS, mat_3_shine);
 glMaterialfv(GL_FRONT, GL_EMISSION, mat_3_emission);
glBegin(GL_TRIANGLES);
  glNormal3f(0.620930, 0.140233, -0.771203);
  glVertex3f(1.815618, -2.273985, -0.017416);
  glNormal3f(0.081484, 0.314493, -0.945738);
  glVertex3f(1.377251, -2.370869, -0.387990);
  glNormal3f(-0.011200, 0.064058, -0.997864);
  glVertex3f(0.391991, 3.228739, -0.017416);
  glNormal3f(0.081484, 0.314493, -0.945738);
  glVertex3f(1.377251, -2.370869, -0.387990);
  glNormal3f(-0.654805, 0.130833, -0.744346);
  glVertex3f(0.913988, -2.370869, -0.017416);
  glNormal3f(-0.011200, 0.064058, -0.997864);
  glVertex3f(0.391991, 3.228739, -0.017416);
  glNormal3f(-0.654805, 0.130833, -0.744346);
  glVertex3f(0.913988, -2.370869, -0.017416);
  glNormal3f(0.081484, 0.314493, -0.945738);
  glVertex3f(1.377251, -2.370869, -0.387990);
  glNormal3f(0.006195, 0.489547, -0.871944);
  glVertex3f(1.356453, -2.634609, -0.550990);
  glNormal3f(-0.654805, 0.130833, -0.744346);
  glVertex3f(0.913988, -2.370869, -0.017416);
  glNormal3f(0.006195, 0.489547, -0.871944);
  glVertex3f(1.356453, -2.634609, -0.550990);
  glNormal3f(-0.686911, 0.237281, -0.686880);
  glVertex3f(0.805463, -2.634609, -0.000000);
  glNormal3f(0.081484, 0.314493, -0.945738);
  glVertex3f(1.377251, -2.370869, -0.387990);
  glNormal3f(0.620930, 0.140233, -0.771203);
  glVertex3f(1.815618, -2.273985, -0.017416);
  glNormal3f(0.640187, 0.193243, -0.743461);
  glVertex3f(1.907444, -2.634609, 0.000000);
  glNormal3f(0.081484, 0.314493, -0.945738);
  glVertex3f(1.377251, -2.370869, -0.387990);
  glNormal3f(0.640187, 0.193243, -0.743461);
  glVertex3f(1.907444, -2.634609, 0.000000);
  glNormal3f(0.006195, 0.489547, -0.871944);
  glVertex3f(1.356453, -2.634609, -0.550990);
  glNormal3f(0.000000, -1.000000, 0.000000);
  glVertex3f(1.356453, -2.634609, 0.550990);
  glNormal3f(0.000000, -1.000000, 0.000000);
  glVertex3f(0.805463, -2.634609, -0.000000);
  glNormal3f(0.000000, -1.000000, 0.000000);
  glVertex3f(1.356453, -2.634609, -0.550990);
  glNormal3f(0.000000, -1.000000, 0.000000);
  glVertex3f(1.356453, -2.634609, 0.550990);
  glNormal3f(0.000000, -1.000000, 0.000000);
  glVertex3f(1.356453, -2.634609, -0.550990);
  glNormal3f(0.000000, -1.000000, 0.000000);
  glVertex3f(1.907444, -2.634609, 0.000000);
  glNormal3f(-0.619709, 0.151494, 0.770043);
  glVertex3f(0.913988, -2.370869, -0.017416);
  glNormal3f(-0.048189, 0.335002, 0.940947);
  glVertex3f(1.340985, -2.284365, 0.309189);
  glNormal3f(-0.009980, 0.057405, 0.998291);
  glVertex3f(0.391991, 3.228739, -0.017416);
  glNormal3f(0.606098, 0.234352, 0.760063);
  glVertex3f(1.815618, -2.273985, -0.017416);
  glNormal3f(-0.009980, 0.057405, 0.998291);
  glVertex3f(0.391991, 3.228739, -0.017416);
  glNormal3f(-0.048189, 0.335002, 0.940947);
  glVertex3f(1.340985, -2.284365, 0.309189);
  glNormal3f(0.606098, 0.234352, 0.760063);
  glVertex3f(1.815618, -2.273985, -0.017416);
  glNormal3f(-0.048189, 0.335002, 0.940947);
  glVertex3f(1.340985, -2.284365, 0.309189);
  glNormal3f(-0.026063, 0.514420, 0.857112);
  glVertex3f(1.356453, -2.634609, 0.550990);
  glNormal3f(0.606098, 0.234352, 0.760063);
  glVertex3f(1.815618, -2.273985, -0.017416);
  glNormal3f(-0.026063, 0.514420, 0.857112);
  glVertex3f(1.356453, -2.634609, 0.550990);
  glNormal3f(0.691397, 0.209449, 0.691397);
  glVertex3f(1.907444, -2.634609, 0.000000);
  glNormal3f(-0.048189, 0.335002, 0.940947);
  glVertex3f(1.340985, -2.284365, 0.309189);
  glNormal3f(-0.619709, 0.151494, 0.770043);
  glVertex3f(0.913988, -2.370869, -0.017416);
  glNormal3f(-0.629688, 0.351085, 0.692953);
  glVertex3f(0.805463, -2.634609, -0.000000);
  glNormal3f(-0.048189, 0.335002, 0.940947);
  glVertex3f(1.340985, -2.284365, 0.309189);
  glNormal3f(-0.629688, 0.351085, 0.692953);
  glVertex3f(0.805463, -2.634609, -0.000000);
  glNormal3f(-0.026063, 0.514420, 0.857112);
  glVertex3f(1.356453, -2.634609, 0.550990);


// engine.003
  glNormal3f(-0.620930, 0.140233, -0.771203);
  glVertex3f(-1.812733, -2.273985, -0.017416);
  glNormal3f(0.011200, 0.064058, -0.997864);
  glVertex3f(-0.389106, 3.228739, -0.017416);
  glNormal3f(-0.081484, 0.314493, -0.945738);
  glVertex3f(-1.374366, -2.370869, -0.387990);
  glNormal3f(-0.081484, 0.314493, -0.945738);
  glVertex3f(-1.374366, -2.370869, -0.387990);
  glNormal3f(0.011200, 0.064058, -0.997864);
  glVertex3f(-0.389106, 3.228739, -0.017416);
  glNormal3f(0.654805, 0.130833, -0.744346);
  glVertex3f(-0.911103, -2.370869, -0.017416);
  glNormal3f(0.654805, 0.130833, -0.744346);
  glVertex3f(-0.911103, -2.370869, -0.017416);
  glNormal3f(-0.006195, 0.489547, -0.871944);
  glVertex3f(-1.353568, -2.634609, -0.550990);
  glNormal3f(-0.081484, 0.314493, -0.945738);
  glVertex3f(-1.374366, -2.370869, -0.387990);
  glNormal3f(0.654805, 0.130833, -0.744346);
  glVertex3f(-0.911103, -2.370869, -0.017416);
  glNormal3f(0.686911, 0.237281, -0.686880);
  glVertex3f(-0.802578, -2.634609, -0.000000);
  glNormal3f(-0.006195, 0.489547, -0.871944);
  glVertex3f(-1.353568, -2.634609, -0.550990);
  glNormal3f(-0.640187, 0.193243, -0.743461);
  glVertex3f(-1.904559, -2.634609, 0.000000);
  glNormal3f(-0.620930, 0.140233, -0.771203);
  glVertex3f(-1.812733, -2.273985, -0.017416);
  glNormal3f(-0.081484, 0.314493, -0.945738);
  glVertex3f(-1.374366, -2.370869, -0.387990);
  glNormal3f(-0.081484, 0.314493, -0.945738);
  glVertex3f(-1.374366, -2.370869, -0.387990);
  glNormal3f(-0.006195, 0.489547, -0.871944);
  glVertex3f(-1.353568, -2.634609, -0.550990);
  glNormal3f(-0.640187, 0.193243, -0.743461);
  glVertex3f(-1.904559, -2.634609, 0.000000);
  glNormal3f(0.000000, -1.000000, 0.000000);
  glVertex3f(-1.353568, -2.634609, 0.550990);
  glNormal3f(0.000000, -1.000000, 0.000000);
  glVertex3f(-1.353568, -2.634609, -0.550990);
  glNormal3f(0.000000, -1.000000, 0.000000);
  glVertex3f(-0.802578, -2.634609, -0.000000);
  glNormal3f(0.000000, -1.000000, 0.000000);
  glVertex3f(-1.353568, -2.634609, 0.550990);
  glNormal3f(0.000000, -1.000000, 0.000000);
  glVertex3f(-1.904559, -2.634609, 0.000000);
  glNormal3f(0.000000, -1.000000, 0.000000);
  glVertex3f(-1.353568, -2.634609, -0.550990);
  glNormal3f(0.619709, 0.151494, 0.770043);
  glVertex3f(-0.911103, -2.370869, -0.017416);
  glNormal3f(0.009980, 0.057405, 0.998291);
  glVertex3f(-0.389106, 3.228739, -0.017416);
  glNormal3f(0.048189, 0.335002, 0.940947);
  glVertex3f(-1.338100, -2.284365, 0.309189);
  glNormal3f(-0.606098, 0.234352, 0.760063);
  glVertex3f(-1.812733, -2.273985, -0.017416);
  glNormal3f(0.048189, 0.335002, 0.940947);
  glVertex3f(-1.338100, -2.284365, 0.309189);
  glNormal3f(0.009980, 0.057405, 0.998291);
  glVertex3f(-0.389106, 3.228739, -0.017416);
  glNormal3f(-0.606098, 0.234352, 0.760063);
  glVertex3f(-1.812733, -2.273985, -0.017416);
  glNormal3f(0.026063, 0.514420, 0.857112);
  glVertex3f(-1.353568, -2.634609, 0.550990);
  glNormal3f(0.048189, 0.335002, 0.940947);
  glVertex3f(-1.338100, -2.284365, 0.309189);
  glNormal3f(-0.606098, 0.234352, 0.760063);
  glVertex3f(-1.812733, -2.273985, -0.017416);
  glNormal3f(-0.691397, 0.209449, 0.691397);
  glVertex3f(-1.904559, -2.634609, 0.000000);
  glNormal3f(0.026063, 0.514420, 0.857112);
  glVertex3f(-1.353568, -2.634609, 0.550990);
  glNormal3f(0.048189, 0.335002, 0.940947);
  glVertex3f(-1.338100, -2.284365, 0.309189);
  glNormal3f(0.629688, 0.351085, 0.692953);
  glVertex3f(-0.802578, -2.634609, -0.000000);
  glNormal3f(0.619709, 0.151494, 0.770043);
  glVertex3f(-0.911103, -2.370869, -0.017416);
  glNormal3f(0.048189, 0.335002, 0.940947);
  glVertex3f(-1.338100, -2.284365, 0.309189);
  glNormal3f(0.026063, 0.514420, 0.857112);
  glVertex3f(-1.353568, -2.634609, 0.550990);
  glNormal3f(0.629688, 0.351085, 0.692953);
  glVertex3f(-0.802578, -2.634609, -0.000000);
glEnd();

glEndList();

// wing
 dl_right_wing = dl_cockpit + 3;
 glNewList(dl_right_wing, GL_COMPILE);
 glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_2_diffuse);
 glMaterialfv(GL_FRONT, GL_AMBIENT, mat_2_ambient);
 glMaterialfv(GL_FRONT, GL_SPECULAR, mat_2_specular);
 glMaterialf(GL_FRONT, GL_SHININESS, mat_2_shine);
 glMaterialfv(GL_FRONT, GL_EMISSION, mat_2_emission);
glBegin(GL_TRIANGLES);
  glNormal3f(0.046480, -0.212592, 0.976012);
  glVertex3f(3.166326, -3.713438, -0.677015);
  glNormal3f(0.024659, -0.230598, 0.972716);
  glVertex3f(0.113321, -0.178436, 0.238452);
  glNormal3f(-0.141575, -0.360973, 0.921751);
  glVertex3f(-0.508937, -0.543261, 0.000000);
  glNormal3f(0.240761, -0.043153, 0.969604);
  glVertex3f(0.735932, 0.124324, 0.097324);
  glNormal3f(0.024659, -0.230598, 0.972716);
  glVertex3f(0.113321, -0.178436, 0.238452);
  glNormal3f(0.046480, -0.212592, 0.976012);
  glVertex3f(3.166326, -3.713438, -0.677015);
  glNormal3f(-0.002777, 0.161870, -0.986785);
  glVertex3f(3.166326, -3.713438, -0.677015);
  glNormal3f(-0.149541, 0.037599, -0.988037);
  glVertex3f(-0.508937, -0.543261, 0.000000);
  glNormal3f(-0.021088, 0.146702, -0.988952);
  glVertex3f(0.016931, 0.000000, -0.058908);
  glNormal3f(0.155278, 0.288949, -0.944639);
  glVertex3f(0.735932, 0.124324, 0.097324);
  glNormal3f(-0.002777, 0.161870, -0.986785);
  glVertex3f(3.166326, -3.713438, -0.677015);
  glNormal3f(-0.021088, 0.146702, -0.988952);
  glVertex3f(0.016931, 0.000000, -0.058908);
glEnd();

glEndList();

// wing.001
 dl_left_wing = dl_cockpit + 4;
 glNewList(dl_left_wing, GL_COMPILE);
 glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_2_diffuse);
 glMaterialfv(GL_FRONT, GL_AMBIENT, mat_2_ambient);
 glMaterialfv(GL_FRONT, GL_SPECULAR, mat_2_specular);
 glMaterialf(GL_FRONT, GL_SHININESS, mat_2_shine);
 glMaterialfv(GL_FRONT, GL_EMISSION, mat_2_emission);
glBegin(GL_TRIANGLES);
  glNormal3f(0.002777, 0.161870, -0.986785);
  glVertex3f(-3.156896, -3.713438, -0.677015);
  glNormal3f(0.021088, 0.146702, -0.988952);
  glVertex3f(-0.007502, 0.000000, -0.058908);
  glNormal3f(0.149541, 0.037599, -0.988037);
  glVertex3f(0.518367, -0.543261, 0.000000);
  glNormal3f(-0.155278, 0.288949, -0.944639);
  glVertex3f(-0.726503, 0.124324, 0.097324);
  glNormal3f(0.021088, 0.146702, -0.988952);
  glVertex3f(-0.007502, 0.000000, -0.058908);
  glNormal3f(0.002777, 0.161870, -0.986785);
  glVertex3f(-3.156896, -3.713438, -0.677015);
  glNormal3f(-0.046480, -0.212592, 0.976012);
  glVertex3f(-3.156896, -3.713438, -0.677015);
  glNormal3f(0.141575, -0.360973, 0.921751);
  glVertex3f(0.518367, -0.543261, 0.000000);
  glNormal3f(-0.024659, -0.230598, 0.972716);
  glVertex3f(-0.103892, -0.178436, 0.238452);
  glNormal3f(-0.240761, -0.043153, 0.969604);
  glVertex3f(-0.726503, 0.124324, 0.097324);
  glNormal3f(-0.046480, -0.212592, 0.976012);
  glVertex3f(-3.156896, -3.713438, -0.677015);
  glNormal3f(-0.024659, -0.230598, 0.972716);
  glVertex3f(-0.103892, -0.178436, 0.238452);
glEnd();

glEndList();


}

Player::~Player() {
   // do nothing
}

int Player::action() {

   // rotate player
   if(input.rotate_left) {
      z_rotation += 360.0/60.0;
   }

   if(input.rotate_right) {
      z_rotation -= 360.0/60.0;
   }

   // clamp rotation
   if(z_rotation > 360.0)
      z_rotation -= 360.0;
   if(z_rotation < 0.0)
      z_rotation += 360.0;

   // thrust
   if(input.thrust) {

      if(thrusting < 30)
         thrusting++;

      vector3 acceleration( cos(degToRad(z_rotation))/75.0f, sin(degToRad(z_rotation))/75.0f, 0.0f);
      velocity += acceleration;
   }
   else {
      if(thrusting > 0)
         thrusting--;
   }

   // shoot
   if(input.fire && shooting == 0) {
      shooting = 15;
      //vector3 acceleration( -cos(degToRad(z_rotation))/50.0f, -sin(degToRad(z_rotation))/50.0f, 0.0f);
      //velocity += acceleration;

      vector3 pp(uniform_random_float(-1.0, 1.0), uniform_random_float(-1.0, 1.0), 0.0);

      pp.normalize();
      pp.scale(10.0);

      alEnemy.insert(new Enemy(position+pp));

      alParticles.first()->init();
   }
   else {
      if(shooting > 0)
         shooting--;
   }

   // friction
   float vmag = velocity.lengthSquared();
   if(vmag > 0.0f) {
      vector3 friction(velocity);
      friction.normalize();
      velocity += friction * (-0.001f-0.05f*vmag/(1.2f*1.2f));
   }

   // clamp velocity
   if(velocity.lengthSquared() > 1.2f*1.2f) {
      vector3 n(velocity);
      n.normalize();

      velocity = n * 1.2f;
   }

   position += velocity;

/*
   // wrap pos

   if(position.x < -settings.world_width)
      position.x += settings.world_width*2.0;

   if(position[0] >  settings.world_width)
      position[0] -= settings.world_width*2.0;

   if(position[1] < -settings.world_height)
      position[1] += settings.world_height*2.0;

   if(position[1] >  settings.world_height)
      position[1] -= settings.world_height*2.0;
*/


   return 0;
}

int Player::render() {

   float  green[] = { 1.0, 1.0, 1.0, 1.0 };
   float  yellow[] = { 1.0, 1.0, 0.0, 1.0 };

   float thrust = 30.0*sin((float)thrusting/30.0*M_PI/2.0); 

   float shoot  = -1*sin((float)shooting/15.0*M_PI/2.0); 

   // ship
   glPushMatrix();

   glTranslatef(position.x, position.y, position.z);
   glRotatef(-90.0, 0.0, 0.0, 1.0);
   glRotatef(z_rotation, 0.0, 0.0, 1.0);

   glPushMatrix();
   glScalef(0.25, 0.25, 0.25);
   glCallList(dl_cockpit);

   glPushMatrix();
   glRotatef(0.0-thrust, 0.0, 0.0, 1.0);
   glCallList(dl_left_wing);
   glPopMatrix();
   
   glPushMatrix();
   glRotatef(0.0+thrust, 0.0, 0.0, 1.0);
   glCallList(dl_right_wing);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.0, shoot, 0.0);
   //glCallList(dl_left_engine);
   glCallList(dl_right_engine);

   glPopMatrix();

   glPopMatrix();

   glPopMatrix();

   // blocks
   for(float y = -30.0; y<=30.0; y+=10.0) {
      for(float x = -30.0; x<=30.0; x+=10.0) {
         glPushMatrix();
         glTranslatef(x, y, -10.0);
         glRotatef(z_rotation, 0.0, 0.0, 1.0);
         glBegin(GL_QUADS);
          glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow);
          glNormal3f( 0.0, 0.0, -1.0);
          glVertex3f( 0.5,  0.5, 0.0);
          glVertex3f(-0.5,  0.5, 0.0);
          glVertex3f(-0.5, -0.5, 0.0);
          glVertex3f( 0.5, -0.5, 0.0);
         glEnd();
         glPopMatrix();
      }
   }



// under the ship...

    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glShadeModel(GL_FLAT);

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE);


    glPushMatrix();

   glTranslatef(position.x, position.y, position.z-1.0);

         glBegin(GL_QUADS);
          glColor4f(1.0, 1.0, 1.0, 0.25);
          glTexCoord2f(1.0, 0.0);
          glVertex3f( 1.3,  1.3, 0.0);
          glTexCoord2f(0.0, 0.0);
          glVertex3f(-1.3,  1.3, 0.0);
          glTexCoord2f(0.0, 1.0);
          glVertex3f(-1.3, -1.3, 0.0);
          glTexCoord2f(1.0, 1.0);
          glVertex3f( 1.3, -1.3, 0.0);
         glEnd();

   glPopMatrix(); 

   glDisable(GL_TEXTURE_2D);
   glEnable(GL_LIGHTING);
   glShadeModel(GL_SMOOTH);
   glDisable(GL_BLEND);

/*

   // target indicator
   vector3 target(0.0f, 0.0f, -10.0f);

   target -= position;

   float dist = target.length();

   target.normalize();

   float angle = radToDeg(acos(target * vector3(0.0f, 1.0f, 0.0f)));

   static int dir_finder_delay = 15;
   static int dir_finder_on = 0;

   if(dir_finder_delay > 0) {
      dir_finder_delay--;
   }
   else {
      dir_finder_delay = 15;
      dir_finder_on = !dir_finder_on;
   }

   if(dir_finder_on && dist > 20.0) {

   glDisable(GL_LIGHTING);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
   glDisable(GL_DEPTH_TEST);

   glPushMatrix();
  
   glTranslatef(position.x, position.y, position.z);
   glRotatef(angle, 0.0, 0.0, 1.0);
   glTranslatef(0.0, 3.0, 0.0); 

   float al = 0.6;

   if(dist < 70.0)
      al = ((dist-20.0)*0.6)/50.0;
  
   glBegin(GL_TRIANGLE_STRIP);
     glColor4f(0.5, 0.25, 0.0, al/1.5);
//    glColor4f(0.0, 1.0, 0.0, 0.2);
    glVertex3f(-0.25, -0.2, 0.0);
//    glColor4f(1.0, 1.0, 0.0, 0.1);
     glColor4f(0.7, 0.25, 0.0, al/2.0);
    glVertex3f(0.0, 0.0, 0.0);
    //glColor4f(1.0, 0.0, 0.0, 0.5);
     glColor4f(0.7, 0.25, 0.0, al);
    glVertex3f(0.0, 1.0, 0.0);
  //  glColor4f(0.0, 1.0, 0.0, 0.2);
     glColor4f(0.5, 0.25, 0.0, al/1.5);
    glVertex3f(0.25, -0.2, 0.0);
   glEnd();

   glPopMatrix();
  
   glEnable(GL_LIGHTING);
   glDisable(GL_BLEND);
   glEnable(GL_DEPTH_TEST);

   }
*/



/*
   glDisable(GL_DEPTH_TEST);
   glDisable(GL_LIGHTING);


   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE);

   float scale = 50.0;

   glPushMatrix();
   glTranslatef(position[0], position[1], position[2]);
   glTranslatef(-7.0, 4.5, 0.0); 
   glBegin(GL_QUADS);
    glColor4f(0.5, 0.5, 1.0, 0.1);
    glVertex3f( 2.5,  2.5, 0.0);
    glVertex3f(-2.5,  2.5, 0.0);
    glVertex3f(-2.5, -2.5, 0.0);
    glVertex3f( 2.5, -2.5, 0.0);

    glVertex3f( 10.0*2.5/scale,  7.5*2.5/scale, 0.0);
    glVertex3f(-10.0*2.5/scale,  7.5*2.5/scale, 0.0);
    glVertex3f(-10.0*2.5/scale, -7.5*2.5/scale, 0.0);
    glVertex3f( 10.0*2.5/scale, -7.5*2.5/scale, 0.0);
   glEnd();
   
   glEnable(GL_POINT_SMOOTH);
   glPointSize(3);
   glBegin(GL_POINTS);
     glVertex3f(0.0, 0.0, 0.0);

   Actor *pact = alEnemy.first();

   while(pact != alEnemy.head()) {
                sgVec3 p;
                pact->position(p);
 
                sgSubVec3(p, position);

                p[0] *= 2.5/scale;
                p[1] *= 2.5/scale;
                p[2] *= 0.0;

     if(p[0] > -2.5 && p[0] < 2.5 && p[1] > -2.5 && p[1] < 2.5)
        glVertex3f(p[0], p[1], p[2]);

                pact = alEnemy.next();
      }
      
     
   glEnd();

   glPopMatrix();

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);

   glDisable(GL_BLEND);

*/









   return 0;
}



