
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
   quaternion(const vector3& vv, const float aa=zero) : v(vv), a(aa) { }
   quaternion(const vector4& v) : v(v.x, v.y, v.z), a(v.w) { }
   ~quaternion() { }

   void set(const float qx, const float qy, const float qz, const float qw) { v.x = qx; v.y = qy; v.z = qz; a = qw; }

   float magnitudeSquared() const { return v*v+a*a; }
   float magnitude() const { return sqrt(magnitudeSquared()); }

   // negate
   void negate() { v.negate(); a = -a; }

   void scale(const float f) { v.scale(f); a *= f; }

   void add(const quaternion& q) { v.add(q.v); a += q.a; }
   void sub(const quaternion& q) { v.sub(q.v); a -= q.a; }

   void conjugate() { v.negate(); }


   void normalize() {

      float f = magnitude();

      if(f > zero) {
         a /= f;
         v.scale(one/f);
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
   float getAngle() { return (2.0f*acos(a))*180.0f/M_PI; }

   // get axis
   vector3 getAxis() { vector3 tmp(v); tmp.normalize(); return tmp; }

   void setAxisAngle(const vector3& axis, const float angle) {

      float r = angle*M_PI/180.0f*0.5f;

      v = axis;
      v.scale(sin(r));
      a = cos(r);

      normalize();
   }   

//friend inline quaternion operator*(const quaternion& a, const quaternion& b);
//friend inline quaternion operator*(const quaternion& q, const vector3& v);

   // TODO
/*
   vector3 rotateVector(const vector3& v) {
   
      quaternion c(*this);
      c.conjugate();

      quaternion t = *this * quaternion(v) * c;

      t.normalize();
      t *= v.magnitude();

      return t.getVector();
   }
*/
};



inline quaternion operator*(const quaternion& q, const float f) { 

   return quaternion(q.v.x*f, q.v.y*f, q.v.z*f, q.a*f); 
}

inline quaternion operator*(const float f, const quaternion& q) { 

   return q * f;
}

inline quaternion operator/(const quaternion& v, const float f) {

   return v * (one/f);
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

   return quaternion(  (a.v%b.v)+(a.v*b.a)+(b.v*a.a) , a.a*b.a-a.v*b.v );
/*
   return quaternion( a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z, 
                      a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y,
                      a.w*b.y + a.y*b.w + a.z*b.x - a.x*b.z,
                      a.w*b.z + a.z*b.w + a.x*b.y - a.y*b.x );
*/
}
      

// quaternion addition
inline quaternion operator+(const quaternion& vA, const quaternion& vB) { 

   return quaternion(vA.v+vB.v, vA.a+vB.a);
}

inline quaternion operator-(const quaternion& vA, const quaternion& vB) { 

   return quaternion(vA.v-vB.v, vA.a-vB.a);
}


inline quaternion operator~(const quaternion& v) {

   quaternion tmp(v);
   tmp.normalize();
   return tmp;
}


#endif

