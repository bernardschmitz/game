
#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include <math.h>

#include "vector.h"

// asm ("fsincos" : "=t" (cos), "=u" (sin) : "0" (inp)); 

// TODO
// rotate, set from dir vectors, eulers, slerp
// optimize operators...
// to_matrix, from_matrix
// to/from frame (dir, up, right vectors)
// equals
// normalize after every operation??


class quaternion {
public:
   vector3 v;
   float a;

   quaternion() : v(zero, zero, zero), a(one) { }
   quaternion(const float x, const float y, const float z, const float w) : v(x, y, z), a(w) { }
   quaternion(const quaternion& q) : v(q.v), a(q.a) { }
   quaternion(const vector3& vv, const float aa=zero) : v(vv.x, vv.y, vv.z), a(aa) { }
   quaternion(const vector4& vv) : v(vv.x, vv.y, vv.z), a(vv.w) { }
   ~quaternion() { }
   
   // construct from axis and angle
   //quaternion(const vector3& axis, const float angle) {
   void setAxisAngle(const vector3& axis, const float angle) {

      float r = degToRad(angle)*0.5f;

      v = axis * sin(r);
      a = cos(r);

      normalize();
   }   

   // construct from two dir vectors.
   void setAxisToAxis(const vector3& from, const vector3& to) {

      float cosa = from * to;

      if(cosa < -one+tiny) {
         v.set(zero, from.x, -from.y);
         if((from.z*from.z) > (from.y*from.y))
            v.set(-from.z, zero, from.x);
         v.normalize();
         a = zero;
      }
      else {
         vector3 bisect = !(from+to);
         v = from % bisect;
         a = from * bisect;
      } 
   }


   void set(const float qx, const float qy, const float qz, const float qw) { v.x = qx; v.y = qy; v.z = qz; a = qw; }

   float lengthSquared() const { return v*v+a*a; }
   float length() const { return sqrt(lengthSquared()); }

   // negate
   void negate() { v.negate(); a = -a; }

   void scale(const float f) { v.scale(f); a *= f; }

   void add(const quaternion& q) { v.add(q.v); a += q.a; }
   void sub(const quaternion& q) { v.sub(q.v); a -= q.a; }

   void conjugate() { v.negate(); }

   void normalize() {

      float f = length();

      if(f > zero) {
         f = one/f;
         a *= f;
         v *= f;
      }
      else {
         a = one;
         v.set(zero, zero, zero);
      }
   }

   // operators

   // negate
   quaternion operator-(const quaternion& v) { quaternion tmp(v); tmp.negate(); return tmp; }

   // addition
   quaternion& operator+=(const quaternion& v) { add(v); return *this; }
   quaternion& operator-=(const quaternion& v) { sub(v); return *this; }

   // scale
   quaternion& operator*=(const float f) { scale(f); return *this; }
   quaternion& operator/=(const float f) { scale(one/f); return *this; }


   // get vector component
   vector3 getVector() { return v; }

   // get scalar component
   float getScalar() { return a; }

   // get angle
   float getAngle() { return radToDeg(acos(a)*2.0f); }

   // get axis
   vector3 getAxis() { vector3 tmp(v); tmp.normalize(); return tmp; }

//friend inline quaternion operator*(const quaternion& a, const quaternion& b);
//friend inline quaternion operator*(const quaternion& q, const vector3& v);

   // TODO
/*
   vector3 rotateVector(const vector3& v) {
   
      quaternion c(*this);
      c.conjugate();

      quaternion t = *this * quaternion(v) * c;

      t.normalize();
      t *= v.length();

      return t.getVector();
   }
*/
};



inline quaternion operator*(const quaternion& q, const float f) { 

   return quaternion(q.v*f, q.a*f);
}

inline quaternion operator*(const float f, const quaternion& q) { 

   return q * f;
}

inline quaternion operator/(const quaternion& q, const float f) {

   return quaternion(q.v/f, q.a/f);
}

// vector product
/*
inline quaternion operator*(const quaternion& q, const vector3& v) {

   return quaternion( -(q.x*v.x + q.y*v.y + q.z*v.z),
                        q.w*v.x + q.y*v.z - q.z*v.y,
                        q.w*v.y + q.z*v.x - q.x*v.z,
                        q.w*v.z + q.x*v.y - q.y*v.x );
}

inline quaternion operator*(const vector3& v, const quaternion& q) {
   return quaternion( -(q.x*v.x + q.y*v.y + q.z*v.z),
                        q.w*v.x + q.z*v.y - q.y*v.z,
                        q.w*v.y + q.x*v.z - q.z*v.x,
                        q.w*v.z + q.y*v.x - q.x*v.y );
}
*/

// quaternion product
inline quaternion operator*(const quaternion& a, const quaternion& b) { 

//   return quaternion(  (a.v%b.v)+(a.v*b.a)+(b.v*a.a) , (a.a*b.a)-(a.v*b.v) );

   return quaternion( a.a*b.v.x + a.v.x*b.a + a.v.y*b.v.z - a.v.z*b.v.y,
                      a.a*b.v.y + a.v.y*b.a + a.v.z*b.v.x - a.v.x*b.v.z,
                      a.a*b.v.z + a.v.z*b.a + a.v.x*b.v.y - a.v.y*b.v.x, 
                      a.a*b.a - a.v.x*b.v.x - a.v.y*b.v.y - a.v.z*b.v.z );

}


// quaternion addition
inline quaternion operator+(const quaternion& vA, const quaternion& vB) { 

   return quaternion(vA.v+vB.v, vA.a+vB.a);
}

inline quaternion operator-(const quaternion& vA, const quaternion& vB) { 

   return quaternion(vA.v-vB.v, vA.a-vB.a);
}


inline quaternion operator!(const quaternion& q) {

   quaternion tmp(q);
   tmp.normalize();
   return tmp;
}

inline quaternion operator~(const quaternion& q) {

   quaternion tmp(q);
   tmp.conjugate();
   return tmp;
}

#endif

