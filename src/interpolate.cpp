
#include "interpolate.h"

/*


>   for quadratic (conic) beziers, were P1, P2 and P3 are the control points:
>
>     P(t) = P1 + 2t.(P2-P1) + t^2.(P3-2P2+P1)
>
>   for cubics:
>
>     P(t) = P1 + 3t.(P2-P1) + 3t^2.(P3-2P2+1) + t^3.(P4-3P3+3P2-P1)
>
> A quick rule of thumb to reconstruct the polygon, or even to
> easily draw an arbitrary point of a conic or cubic by hand:
>
>   for t in (0..1)
>
>   for conics:
>
>      let P1, P2, P3 be the control points,
>
>      define  Q1(t) = P1 + t.(P2-P1)
>              Q2(t) = P2 + t.(P3-P2)
>
>      then   P(t) = Q1 + t.(Q2-Q1)
>
>   for cubics:
>
>      let P1, P2, P3 and P4 be the control points,
>
>      define  Q1(t) = P1 + t.(P2-P1)
>              Q2(t) = P2 + t.(P3-P2)
>              Q3(t) = P3 + t.(P4-P3)
>
>      define  R1(t) = Q1 + t.(Q2-Q1)
>              R2(t) = Q2 + t.(Q3-Q2)
>
>      then    P(t) = R1 + t.(R2-R1)
>
>   you can apply this "rule" recursively to build
>   higher-order beziers too :-)
>
>   Also note that all Q1, Q2, Q3, R1, R2 are control points
>   for the sub-arcs P1..P(t) and P(t)..P3 (or P(t)..P4) !!
>
>   Beziers have _tons_ of weird and useful properties,
>   I love them :-)

*/

/*
void cubic_interpolate(sgVec3 dst, const sgVec3 v0, const sgVec3 v1, const sgVec3 v2, const sgVec3 v3, const float t);

   sgVec3 P, Q, R, S;

   sgSubVec3(P, v3, v2);
   sgSubVec3(P, v0);
   sgAddVec3(P, v1);

   sgSubVec3(Q, v0, v1);
   sgSubVec3(Q, P);

   sgSubVec3(R, v2, v0);

   sgCopyVec3(S, v1);

   dst[0] = ((P[0]*t + Q[0])*t + R[0])*t + S[0];
   dst[1] = ((P[1]*t + Q[1])*t + R[1])*t + S[1];
   dst[2] = ((P[2]*t + Q[2])*t + R[2])*t + S[2];
}
*/

// p is an array of sgVec3 2^depth+1 in size

/*
void bezier_curve_work(sgVec3 *p, int depth, const sgVec3 p0, const sgVec3 p1, const sgVec3 p2, const sgVec3 p3) {

   static int k = 0;

   if(depth > 0) {

      sgVec3 a, b, c, d, e, f;

      sgAddVec3(a, p1, p2);
      sgScaleVec3(a, 0.5);
      
      sgAddVec3(b, p0, p1);
      sgScaleVec3(b, 0.5);
      
      sgAddVec3(c, p2, p3);
      sgScaleVec3(c, 0.5);
     
      sgAddVec3(d, b, a);
      sgScaleVec3(d, 0.5);
     
      sgAddVec3(e, a, c);
      sgScaleVec3(e, 0.5);
     
      sgAddVec3(f, d, e);
      sgScaleVec3(f, 0.5);
     
      depth--;

      bezier_curve(p, depth, p0, b, d, f);
      bezier_curve(p, depth, f, e, c, p3); 
   }
   else {
//      printf("%d: %f %f %f -> %f %f %f\n", k, p0[0], p0[1], p0[2], p3[0], p3[1], p3[2]);
      sgCopyVec3(p[k++], p0);
   }
}

*/
