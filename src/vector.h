
// $Id: vector.h,v 1.5 2003-08-08 22:41:15 bernard Exp $

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
   
   // scalar product
   float dot(const vector2& vB) { return x*vB.x + y*vB.y; }

   // equality
   bool isEqual(const vector2& v, const float tol) const {
      
      if(fabs(v.x - x) > tol)
         return false;
      else if(fabs(v.y - y) > tol)
         return false;
      else
         return true;
   }

   // operators
 
   // negate
   friend vector2 operator-(const vector2& v) { vector2 t(v); t.negate(); return t; }

   // addition
   vector2& operator+=(const vector2& v) { add(v); return *this; }
   vector2& operator-=(const vector2& v) { sub(v); return *this; }

   // scale
   vector2& operator*=(const float f) { scale(f); return *this; }
   vector2& operator/=(const float f) { scale(one/f); return *this; }
 
   // dot (scalar) product
   friend float operator*(const vector2& A, const vector2& B) { vector2 t(A); return t.dot(B); }
   
   // vector addition
   friend vector2 operator+(const vector2& A, const vector2& B) { vector2 t(A); t.add(B); return t; }
   
   // vector subtraction
   friend vector2 operator-(const vector2& A, const vector2& B) { vector2 t(A); t.sub(B); return t; }
   
   // scale
   friend vector2 operator*(const vector2& v, const float f) { vector2 t(v); t.scale(f); return t; }
   
   friend vector2 operator*(const float f, const vector2& v) { return v*f; }
   
   friend vector2 operator/(const vector2& v, const float f) { return v * (one/f); }
   
   // norm
   friend vector2 operator!(const vector2& v) { vector2 t(v); t.normalize(); return t; }


   friend class vector3;
   friend class vector4;
};
   


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

   void linear_interpolate(const vector3& a, const vector3& b, const float t) {
      vector3 d(b - a);
      x = a.x + d.x*t;
      y = a.y + d.y*t;
      z = a.z + d.z*t;
   }

   void cosine_interpolate(const vector3& a, const vector3& b, const float t) {
      linear_interpolate(a, b, (1.0-cos(t*M_PI))*0.5);
   }

   void quadratic_interpolate(const vector3& p0, const vector3& p1, const vector3& p2, const float t) {

      x = p0.x + t*(2.0*(p1.x-p0.x) + t*(p2.x-2.0*p1.x+p0.x));
      y = p0.y + t*(2.0*(p1.y-p0.y) + t*(p2.y-2.0*p1.y+p0.y));
      z = p0.z + t*(2.0*(p1.z-p0.z) + t*(p2.z-2.0*p1.z+p0.z));
   }

   void cubic_interpolate(const vector3& p0, const vector3& p1, const vector3& p2, const vector3& p3, const float t) {

      float t2 = t*t*3.0;
      float t3 = t*t*t;

      x = p0.x + (3.0*t)*(p1.x-p0.x) + (t2)*(p2.x-2.0*p1.x+p0.x) + (t3)*(p3.x-3.0*p2.x+3.0*p1.x-p0.x);
      y = p0.y + (3.0*t)*(p1.y-p0.y) + (t2)*(p2.y-2.0*p1.y+p0.y) + (t3)*(p3.y-3.0*p2.y+3.0*p1.y-p0.y);
      z = p0.z + (3.0*t)*(p1.z-p0.z) + (t2)*(p2.z-2.0*p1.z+p0.z) + (t3)*(p3.z-3.0*p2.z+3.0*p1.z-p0.z);
   }    

 
   // scalar product
   float dot(const vector3& v) const { return x*v.x + y*v.y + z*v.z; }


   // vector product
   friend vector3 cross(const vector3& A, const vector3& B) {

      return vector3( A.y*B.z - A.z*B.y,
                      A.z*B.x - A.x*B.z,
                      A.x*B.y - A.y*B.x );
   }


   // operators

   // vector (cross) product
   friend vector3 operator%(const vector3& A, const vector3& B) { return cross(A, B); }
 
   // negate
   friend vector3 operator-(const vector3& v) { vector3 t(v); t.negate(); return t; }

   // addition
   vector3& operator+=(const vector3& v) { add(v); return *this; }
   vector3& operator-=(const vector3& v) { sub(v); return *this; }

   // scale
   vector3& operator*=(const float f) { scale(f); return *this; }
   vector3& operator/=(const float f) { scale(one/f); return *this; }
 
   // scalar (dot) product
   friend float operator*(const vector3& A, const vector3& B) { vector3 t(A); return t.dot(B); }
   
   // vector addition
   friend vector3 operator+(const vector3& A, const vector3& B) { vector3 t(A); t.add(B); return t; }
   
   // vector subtraction
   friend vector3 operator-(const vector3& A, const vector3& B) { vector3 t(A); t.sub(B); return t; }
   
   // scale
   friend vector3 operator*(const vector3& v, const float f) { vector3 t(v); t.scale(f); return t; }
   
   friend vector3 operator*(const float f, const vector3& v) { return v*f; }
   
   friend vector3 operator/(const vector3& v, const float f) { return v * (one/f); }
   
   // norm
   friend vector3 operator!(const vector3& v) { vector3 t(v); t.normalize(); return t; }

   friend class vector4;
   friend class quaternion;
};
   


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

   void linear_interpolate(const vector4& a, const vector4& b, const float t) {
      vector4 d(b - a);
      x = a.x + d.x*t;
      y = a.y + d.y*t;
      z = a.z + d.z*t;
      w = a.w + d.w*t;
   }
 
   // scalar product
   float dot(const vector4& v) const { return x*v.x + y*v.y + z*v.z + w*v.w; }

   // operators

   // negate
   friend vector4 operator-(const vector4& v) { vector4 t(v); t.negate(); return t; }

   // addition
   vector4& operator+=(const vector4& v) { add(v); return *this; }
   vector4& operator-=(const vector4& v) { sub(v); return *this; }

   // scale
   vector4& operator*=(const float f) { scale(f); return *this; }
   vector4& operator/=(const float f) { scale(one/f); return *this; }
 
   // scalar (dot) product
   friend float operator*(const vector4& A, const vector4& B) { vector4 t(A); return t.dot(B); }
   
   // vector addition
   friend vector4 operator+(const vector4& A, const vector4& B) { vector4 t(A); t.add(B); return t; }
   
   // vector subtraction
   friend vector4 operator-(const vector4& A, const vector4& B) { vector4 t(A); t.sub(B); return t; }
   
   // scale
   friend vector4 operator*(const vector4& v, const float f) { vector4 t(v); t.scale(f); return t; }
   
   friend vector4 operator*(const float f, const vector4& v) { return v*f; }
   
   friend vector4 operator/(const vector4& v, const float f) { return v * (one/f); }
   
   // norm
   friend vector4 operator!(const vector4& v) { vector4 t(v); t.normalize(); return t; }

};
   


#endif

