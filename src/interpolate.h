
#ifndef __INTERPOLATE_H__
#define __INTERPOLATE_H__

#include "main.h"

inline void linear_interpolate(sgVec3 dst, const sgVec3 a, const sgVec3 b, const float t) {

   sgLerpVec3(dst, a, b, t);
}

inline void cosine_interpolate(sgVec3 dst, const sgVec3 a, const sgVec3 b, const float t) {

   float tt = (1.0 - cos(t*M_PI)) * 0.5;

   sgLerpVec3(dst, a, b, tt);
}


inline void quadratic_interpolate(sgVec3 dst, const sgVec3 p0, const sgVec3 p1, const sgVec3 p2, const float t) {

   dst[0] = p0[0] + t*(2.0*(p1[0]-p0[0]) + t*(p2[0]-2.0*p1[0]+p0[0]));
   dst[1] = p0[1] + t*(2.0*(p1[1]-p0[1]) + t*(p2[1]-2.0*p1[1]+p0[1]));
   dst[2] = p0[2] + t*(2.0*(p1[2]-p0[2]) + t*(p2[2]-2.0*p1[2]+p0[2]));
}

inline void cubic_interpolate(sgVec3 dst, const sgVec3 p0, const sgVec3 p1, const sgVec3 p2, const sgVec3 p3, const float t) {

   dst[0] = p0[0] + 3.0*t*(p1[0]-p0[0]) + 3.0*t*t*(p2[0]-2.0*p1[0]+p0[0]) + t*t*t*(p3[0]-3.0*p2[0]+3.0*p1[0]-p0[0]);
   dst[1] = p0[1] + 3.0*t*(p1[1]-p0[1]) + 3.0*t*t*(p2[1]-2.0*p1[1]+p0[1]) + t*t*t*(p3[1]-3.0*p2[1]+3.0*p1[1]-p0[1]);
   dst[2] = p0[2] + 3.0*t*(p1[2]-p0[2]) + 3.0*t*t*(p2[2]-2.0*p1[2]+p0[2]) + t*t*t*(p3[2]-3.0*p2[2]+3.0*p1[2]-p0[2]);

//   dst[0] = p0[0] + t*(3.0*p1[0]-3.0*p0[0]+t*(3.0*p2[0]-6.0*p1[0]+p0[0]+t*(3.0+p3[0]-3.0*p2[0]+6.0*p1[0])));
//   dst[1] = p0[1] + t*(3.0*p1[1]-3.0*p0[1]+t*(3.0*p2[1]-6.0*p1[1]+p0[1]+t*(3.0+p3[1]-3.0*p2[1]+6.0*p1[1])));
//   dst[2] = p0[2] + t*(3.0*p1[2]-3.0*p0[2]+t*(3.0*p2[2]-6.0*p1[2]+p0[2]+t*(3.0+p3[2]-3.0*p2[2]+6.0*p1[2])));
}

//extern void bezier_curve(sgVec3 *p, int depth, const sgVec3 p0, const sgVec3 p1, const sgVec3 p2, const sgVec3 p3);

#endif

