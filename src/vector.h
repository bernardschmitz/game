
// $Id: vector.h,v 1.2 2003-07-29 22:44:11 bernard Exp $

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <math.h>

// TODO
//
//  angle between to vectors
//  lerps


inline float degToRad(float deg) { return deg*M_PI/180.0; }
inline float radToDeg(float rad) { return rad*180.0/M_PI; }

static const float tiny = 0.00001f;
static const float zero = 0.0f;
static const float one  = 1.0f;

class vector2 {
public:
   float x, y;

   vector2() { x = y = zero; }
   vector2(const float fx, const float fy) { x = fx; y = fy; }
   vector2(const vector2& v) { x = v.x; y = v.y; }
   vector2(const float* const p) { x = p[0]; y = p[1]; }
   ~vector2() { }

   void set(const float fx, const float fy) { x = fx; y = fy; }

   float lengthSquared() const { return x*x+y*y; }
   float length() const { return sqrt(length()); }

   void negate() { x = -x; y = -y; }

   void scale(const float f) { x *= f; y *= f; }

   void add(const vector2& v) { x += v.x; y += v.y; }
   void sub(const vector2& v) { x -= v.x; y -= v.y; }

   void normalize() {

      float f = length();

      if(f > zero)
         scale(one/f);
   }

   // operators
 
   // negate
   vector2 operator-(const vector2& v) { return vector2(-x, -y); }

   // addition
   vector2& operator+=(const vector2& v) { add(v); return *this; }
   vector2& operator-=(const vector2& v) { sub(v); return *this; }

   // scale
   vector2& operator*=(const float f) { scale(f); return *this; }
   vector2& operator/=(const float f) { scale(one/f); return *this; }

   // equality
   bool isEqual(const vector2& v, const float tol) const {
      
      if(fabs(v.x - x) > tol)
         return false;
      else if(fabs(v.y - y) > tol)
         return false;
      else
         return true;
   }
};
   

// dot (scalar) product
inline float operator*(const vector2& vA, const vector2& vB) { 

   return vA.x*vB.x + vA.y*vB.y; 
}

// vector addition
inline vector2 operator+(const vector2& vA, const vector2& vB) { 

   return vector2(vA.x+vB.x, vA.y+vB.y);
}

// vector subtraction
inline vector2 operator-(const vector2& vA, const vector2& vB) { 

   return vector2(vA.x-vB.x, vA.y-vB.y); 
}

// scale
inline vector2 operator*(const vector2& v, const float f) { 

   vector2 tmp(v);
   tmp.scale(f);
   return tmp;
}

inline vector2 operator*(const float f, const vector2& v) { 

   return v*f;
}

inline vector2 operator/(const vector2& v, const float f) { 

   return v * (one/f);
}


// norm

inline vector2 operator!(const vector2& v) {

   vector2 tmp(v);
   tmp.normalize();
   return tmp;
}




class vector3 {
public:
   float x, y, z;

   vector3() { x = y = z = zero; }
   vector3(const float fx, const float fy, const float fz) { x = fx; y = fy; z = fz; }
   vector3(const vector2& v) { x = v.x; y = v.y; z = zero; }
   vector3(const vector3& v) { x = v.x; y = v.y; z = v.z; }
   vector3(const float* const p) { x = p[0]; y = p[1]; z = p[2]; }
   ~vector3() { }

   void set(const float fx, const float fy, const float fz) { x = fx; y = fy; z = fz; }

   float lengthSquared() const { return x*x+y*y+z*z; }
   float length() const { return sqrt(lengthSquared()); }

   void negate() { x = -x; y = -y; z = -z; }

   void scale(const float f) { x *= f; y *= f; z *= f; }

   void add(const vector3& v) { x += v.x; y += v.y; z += v.z; }
   void sub(const vector3& v) { x -= v.x; y -= v.y; z -= v.z; }

   void normalize() {

      float f = length();

      if(f > zero)
         scale(one/f);
   }

   // operators
 
   // negate
   vector3 operator-() { return vector3(-x, -y, -z); }

   // addition
   vector3& operator+=(const vector3& v) { add(v); return *this; }
   vector3& operator-=(const vector3& v) { sub(v); return *this; }

   // scale
   vector3& operator*=(const float f) { scale(f); return *this; }
   vector3& operator/=(const float f) { scale(one/f); return *this; }

   // equality
   bool isEqual(const vector3& v, const float tol) const {
      
      if(fabs(v.x - x) > tol)
         return false;
      else if(fabs(v.y - y) > tol)
         return false;
      else if(fabs(v.z - z) > tol)
         return false;
      else
         return true;
   }

};
   

// dot (scalar) product
inline float operator*(const vector3& vA, const vector3& vB) { 

   return vA.x*vB.x + vA.y*vB.y + vA.z*vB.z; 
}

// vector addition
inline vector3 operator+(const vector3& vA, const vector3& vB) { 

   return vector3(vA.x+vB.x, vA.y+vB.y, vA.z+vB.z);
}

// vector subtraction
inline vector3 operator-(const vector3& vA, const vector3& vB) { 

   return vector3(vA.x-vB.x, vA.y-vB.y, vA.z-vB.z); 
}

// cross (vector) product
inline vector3 operator%(const vector3& vA, const vector3& vB) {

   return vector3(vA.y*vB.z - vA.z*vB.y,
                  vA.z*vB.x - vA.x*vB.z,
                  vA.x*vB.y - vA.y*vB.x);
}

// scale
inline vector3 operator*(const vector3& v, const float f) { 

   vector3 tmp(v);
   tmp.scale(f);
   return tmp;
}

inline vector3 operator*(const float f, const vector3& v) { 

   return v*f;
}

inline vector3 operator/(const vector3& v, const float f) { 

   return v * (one/f);
}

// norm
inline vector3 operator!(const vector3& v) {

   vector3 tmp(v);
 
   tmp.normalize();
   return tmp;
}




class vector4 {
public:
   float x, y, z, w;

   vector4() { x = y = z = w = zero; }
   vector4(const float fx, const float fy, const float fz, const float fw) { x = fx; y = fy; z = fz; w = fw; }
   vector4(const vector2& v) { x = v.x; y = v.y; z = w = zero; }
   vector4(const vector4& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
   vector4(const float* const p) { x = p[0]; y = p[1]; z = p[2]; w = p[3]; }
   ~vector4() { }

   void set(const float fx, const float fy, const float fz, const float fw) { x = fx; y = fy; z = fz; w = fw; }

   float lengthSquared() const { return x*x+y*y+z*z; }
   float length() const { return sqrt(lengthSquared()); }

   void negate() { x = -x; y = -y; z = -z; w = -w; }

   void scale(const float f) { x *= f; y *= f; z *= f; w *= f; }

   void add(const vector4& v) { x += v.x; y += v.y; z += v.z; w += v.w; }
   void sub(const vector4& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; }

   void normalize() {

      float f = length();

      if(f > zero)
         scale(one/f);
   }

   // operators
 
   // negate
   vector4 operator-(const vector4& v) { return vector4(-x, -y, -z, -w); }

   // addition
   vector4& operator+=(const vector4& v) { add(v); return *this; }
   vector4& operator-=(const vector4& v) { sub(v); return *this; }

   // scale
   vector4& operator*=(const float f) { scale(f); return *this; }
   vector4& operator/=(const float f) { scale(one/f); return *this; }

   // equality
   bool isEqual(const vector4& v, const float tol) const {
      
      if(fabs(v.x - x) > tol)
         return false;
      else if(fabs(v.y - y) > tol)
         return false;
      else if(fabs(v.z - z) > tol)
         return false;
      else if(fabs(v.w - w) > tol)
         return false;
      else
         return true;
   }

};
   

// dot (scalar) product
inline float operator*(const vector4& vA, const vector4& vB) { 

   return vA.x*vB.x + vA.y*vB.y + vA.z*vB.z + vA.w*vB.w; 
}

// vector addition
inline vector4 operator+(const vector4& vA, const vector4& vB) { 

   return vector4(vA.x+vB.x, vA.y+vB.y, vA.z+vB.z, vA.w+vB.w);
}

// vector subtraction
inline vector4 operator-(const vector4& vA, const vector4& vB) { 

   return vector4(vA.x-vB.x, vA.y-vB.y, vA.z-vB.z, vA.w-vB.w); 
}


// scale
inline vector4 operator*(const vector4& v, const float f) { 

   vector4 tmp(v);
   tmp.scale(f);
   return tmp;
}

inline vector4 operator*(const float f, const vector4& v) { 

   return v*f;
}

inline vector4 operator/(const vector4& v, const float f) { 

   float ff = one/f; 
   return v * ff;
}

// norm
inline vector4 operator!(const vector4& v) {

   vector4 tmp(v);
 
   tmp.normalize();
   return tmp;
}


#endif

