
#include <math.h>

#include "vector.h"

/*
   Calculate the line segment PaPb that is the shortest route between
   two lines P1P2 and P3P4. Calculate also the values of mua and mub where
      Pa = P1 + mua (P2 - P1)
      Pb = P3 + mub (P4 - P3)
   Return FALSE if no solution exists.
*/

// TODO use a line segment class

bool LineLineIntersect(const vector3& p1, const vector3& p2, 
                       const vector3& p3, const vector3& p4, 
                       vector3& pa, vector3& pb,
                       float& mua, float& mub)
{
   vector3 p13, p43, p21;
   float d1343, d4321, d1321, d4343, d2121;
   float numer, denom;

   p13.x = p1.x - p3.x;
   p13.y = p1.y - p3.y;
   p13.z = p1.z - p3.z;

   p43.x = p4.x - p3.x;
   p43.y = p4.y - p3.y;
   p43.z = p4.z - p3.z;

   if(fabs(p43.x) < tiny && fabs(p43.y) < tiny && fabs(p43.z) < tiny)
      return false;

   p21.x = p2.x - p1.x;
   p21.y = p2.y - p1.y;
   p21.z = p2.z - p1.z;

   if (fabs(p21.x) < tiny && fabs(p21.y) < tiny && fabs(p21.z) < tiny)
      return false;

   d1343 = p13.x * p43.x + p13.y * p43.y + p13.z * p43.z;
   d4321 = p43.x * p21.x + p43.y * p21.y + p43.z * p21.z;
   d1321 = p13.x * p21.x + p13.y * p21.y + p13.z * p21.z;
   d4343 = p43.x * p43.x + p43.y * p43.y + p43.z * p43.z;
   d2121 = p21.x * p21.x + p21.y * p21.y + p21.z * p21.z;

   denom = d2121 * d4343 - d4321 * d4321;
   if (fabs(denom) < tiny)
      return false;

   numer = d1343 * d4321 - d1321 * d4343;

   mua = numer / denom;
   mub = (d1343 + d4321 * mua) / d4343;

   pa.x = p1.x + mua * p21.x;
   pa.y = p1.y + mua * p21.y;
   pa.z = p1.z + mua * p21.z;

   pb.x = p3.x + mub * p43.x;
   pb.y = p3.y + mub * p43.y;
   pb.z = p3.z + mub * p43.z;

   return true;
}
