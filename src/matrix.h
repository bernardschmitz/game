
// $Id: matrix.h,v 1.1 2003-08-02 18:01:34 bernard Exp $

#ifndef __MATRIX33_H__
#define __MATRIX33_H__

#include <math.h>

#include "vector.h"

/*

TODO

class matrix33 {
public:
   float m[9];
   float m11, m12, m13, m14;
   float m21, m22, m23, m24;
   float m31, m32, m33, m34;

   Matrix() { }
   Matrix(const Matrix&);
   Matrix(int, const Vector&, const Vector&, const Vector&, const Vector&);
   Matrix(int, int, int, const Vector&);
   ~Matrix() { }

   void Identity(void);
   void Scale(const Vector&);
   void Translate(const Vector&);
   void RotateX(int);
   void RotateY(int);
   void RotateZ(int);

   void PostScale(const Vector&);
   void PostTranslate(const Vector&);
   void PostRotateX(int);
   void PostRotateY(int);
   void PostRotateZ(int);

   void Transpose(void);
   void Inverse(void);

   void RotateAboutVector(const Vector&, int);
   void AlignToVector(const Vector &);

   friend Vector operator*(const Matrix&, const Vector&);
   friend Matrix operator*(const Matrix&, const Matrix&);

   Matrix& operator*=(const Matrix&);
};


inline Matrix::Matrix(const Matrix& m) {

   m11 = m.m11;  m12 = m.m12;  m13 = m.m13;  m14 = m.m14;
   m21 = m.m21;  m22 = m.m22;  m23 = m.m23;  m24 = m.m24;
   m31 = m.m31;  m32 = m.m32;  m33 = m.m33;  m34 = m.m34;
}

inline Matrix::Matrix(int how, const Vector& v1, const Vector& v2, const Vector& v3, const Vector& v4) {

   if(how == MAT_ROWS) {
      m11 = v1.x;
      m12 = v1.y;
      m13 = v1.z;
      m21 = v2.x;
      m22 = v2.y;
      m23 = v2.z;
      m31 = v3.x;
      m32 = v3.y;
      m33 = v3.z;
      m14 = v4.x;
      m24 = v4.y;
      m34 = v4.z;
   }
   else {
      m11 = v1.x;
      m12 = v2.x;
      m13 = v3.x;
      m21 = v1.y;
      m22 = v2.y;
      m23 = v3.y;
      m31 = v1.z;
      m32 = v2.z;
      m33 = v3.z;
      m14 = v4.x;
      m24 = v4.y;
      m34 = v4.z;
   }
}

inline Matrix::Matrix(int rx, int ry, int rz, const Vector& t) {

   float sx, sy, sz, cx, cy, cz;

   sx = Sin[rx];
   sy = Sin[ry];
   sz = Sin[rz];
   cx = Cos[rx];
   cy = Cos[ry];
   cz = Cos[rz];

   m11 = cy * cz;
   m12 = cx * -sz + sx * sy * cz;
   m13 = -sx * -sz + cx * sy * cz;
   m14 = t.x;
   m21 = cy * sz;
   m22 = cx * cz + sx * sy * sz;
   m23 = -sx * cz + cx * sy * sz;
   m24 = t.y;
   m31 = -sy;
   m32 = sx * cy;
   m33 = cx * cy;
   m34 = t.z;
}

inline Matrix& Matrix::operator*=(const Matrix& b) {

   Matrix a = *this;

   m11 = a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31; 
   m12 = a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32; 
   m13 = a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33; 
   m14 = a.m11 * b.m14 + a.m12 * b.m24 + a.m13 * b.m34 + a.m14;  
   m21 = a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31; 
   m22 = a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32; 
   m23 = a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33; 
   m24 = a.m21 * b.m14 + a.m22 * b.m24 + a.m23 * b.m34 + a.m24;  
   m31 = a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31; 
   m32 = a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32; 
   m33 = a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33; 
   m34 = a.m31 * b.m14 + a.m32 * b.m24 + a.m33 * b.m34 + a.m34;

   return(*this);
}

inline Matrix operator*(const Matrix& a, const Matrix& b) {

   Matrix c;

   c.m11 = a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31; 
   c.m12 = a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32; 
   c.m13 = a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33; 
   c.m14 = a.m11 * b.m14 + a.m12 * b.m24 + a.m13 * b.m34 + a.m14;  
   c.m21 = a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31; 
   c.m22 = a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32; 
   c.m23 = a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33; 
   c.m24 = a.m21 * b.m14 + a.m22 * b.m24 + a.m23 * b.m34 + a.m24;  
   c.m31 = a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31; 
   c.m32 = a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32; 
   c.m33 = a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33; 
   c.m34 = a.m31 * b.m14 + a.m32 * b.m24 + a.m33 * b.m34 + a.m34;

   return(c);
}

inline Vector operator*(const Matrix& m, const Vector& v) {

   return(Vector(m.m11*v.x + m.m12*v.y + m.m13*v.z + m.m14,
                 m.m21*v.x + m.m22*v.y + m.m23*v.z + m.m24,   
                 m.m31*v.x + m.m32*v.y + m.m33*v.z + m.m34));
}

*/

#endif

