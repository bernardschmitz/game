
// $Id: matrix.cpp,v 1.1 2003-08-02 18:01:34 bernard Exp $

#include "matrix.h"

#if 0
/*

Matrix::Matrix(const Matrix& m) {

   m11 = m.m11;  m12 = m.m12;  m13 = m.m13;  m14 = m.m14;
   m21 = m.m21;  m22 = m.m22;  m23 = m.m23;  m24 = m.m24;
   m31 = m.m31;  m32 = m.m32;  m33 = m.m33;  m34 = m.m34;
}

Matrix::Matrix(int how, const Vector& v1, const Vector& v2, const Vector& v3, const Vector& v4) {

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

Matrix::Matrix(int rx, int ry, int rz, const Vector& t) {

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

*/

void Matrix::Identity(void) {

   m11 = m22 = m33 = 1.0;
   m12 = m13 = m14 =
   m21 = m23 = m24 =
   m31 = m32 = m34 = 0.0;
}

void Matrix::Scale(const Vector& v) {

   m11 = v.x;
   m22 = v.y;
   m33 = v.z;
   m12 = m13 = m14 =
   m21 = m23 = m24 =
   m31 = m32 = m34 = 0.0;
}

void Matrix::Translate(const Vector& v) {

   m14 = v.x;
   m24 = v.y;
   m34 = v.z;
   m12 = m13 = m21 =
   m23 = m31 = m32 = 0.0;
   m11 = m22 = m33 = 1.0;
}

void Matrix::RotateX(int d) {

   float c = Cos[d], s = Sin[d];

   m11 = 1.0;
   m22 = c;
   m23 = -s;
   m32 = s;
   m33 = c;
   m12 = m13 = m14 =
   m21 = m24 =
   m31 = m34 = 0.0;
}

void Matrix::RotateY(int d) {

   float c = Cos[d], s = Sin[d];

   m11 = c;
   m13 = s;
   m22 = 1.0;
   m31 = -s;
   m33 = c;
   m12 = m14 =
   m21 = m23 = m24 =
   m32 = m34 = 0.0;
}

void Matrix::RotateZ(int d) {

   float c = Cos[d], s = Sin[d];

   m11 = c;
   m12 = -s;
   m21 = s;
   m22 = c;
   m33 = 1.0;
   m13 = m14 =
   m23 = m24 =
   m31 = m32 = m34 = 0.0;
}

void Matrix::PostScale(const Vector& v) {

   m11 = m11 * v.x;
   m12 = m12 * v.y;
   m13 = m13 * v.z;
   m21 = m21 * v.x;
   m22 = m22 * v.y;
   m23 = m23 * v.z;
   m31 = m31 * v.x;
   m32 = m32 * v.y;
   m33 = m33 * v.z;
}

void Matrix::PostTranslate(const Vector& v) {

   m14 += m11 * v.x + m12 * v.y + m13 * v.z;
   m24 += m21 * v.x + m22 * v.y + m23 * v.z;
   m34 += m31 * v.x + m32 * v.y + m33 * v.z;
}

void Matrix::PostRotateX(int d) {

   float c, s, a, b;

   c = Cos[d];
   s = Sin[d];
   a = m12;   
   b = m13;   
   m12 = a * c - b * s;   
   m13 = a * s + b * c;   
   a = m22;   
   b = m23;   
   m22 = a * c - b * s;   
   m23 = a * s + b * c;   
   a = m32;   
   b = m33;   
   m32 = a * c - b * s;   
   m33 = a * s + b * c;
}

void Matrix::PostRotateY(int d) {

   float c, s, a, b;

   c = Cos[d];
   s = Sin[d];   
   a = m11;   
   b = m13;   
   m11 = a * c + b * s;   
   m13 = b * c - a * s;   
   a = m21;   
   b = m23;   
   m21 = a * c + b * s;   
   m23 = b * c - a * s;   
   a = m31;   
   b = m33;   
   m31 = a * c + b * s;   
   m33 = b * c - a * s;
}

void Matrix::PostRotateZ(int d) {

   float c, s, a, b;

   c = Cos[d];
   s = Sin[d];  
   a = m11;   
   b = m12;   
   m11 = a * c - b * s;   
   m12 = a * s + b * c;   
   a = m21;   
   b = m22;   
   m21 = a * c - b * s;   
   m22 = a * s + b * c;   
   a = m31;   
   b = m32;   
   m31 = a * c - b * s;   
   m32 = a * s + b * c;
}

/*
Matrix& Matrix::operator*=(const Matrix& b) {

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

Matrix operator*(const Matrix& a, const Matrix& b) {

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

*/


/*

R = rotation_about_axis_by_angle(axis, theta) =

    | txx + c    txy + sz    txz - sy  |
  = | txy - sz   tyy + c     tyz + sx  |
    | txz + sy   tyz - sx    tzz + c   |

where:
   x, y, and z are the components of a unit vector along rotation axis;
   theta is the angular amount of rotation;
   s = sin theta;
   c = cos theta;
   t = 1 - c.

*/

void Matrix::RotateAboutVector(const Vector& v, int a) {

   float s, c, t, x, y, z;

   s = Sin[a];
   c = Cos[a];
   t = 1.0 - c;

   x = v.x;
   y = v.y;
   z = v.z;

   m11 = t * x * x + c;
   m12 = t * x * y + s * z;
   m13 = t * x * z - s * y;
   m14 = 0.0;
   m21 = t * x * y - s * z;
   m22 = t * y * y + c;
   m23 = t * y * z + s * x;
   m24 = 0.0;
   m31 = t * x * z + s * y;
   m32 = t * y * z - s * x;
   m33 = t * z * z + c;
   m34 = 0.0;
}

void Matrix::Transpose(void) {

   Matrix m = *this;

   m11 = m.m11;
   m12 = m.m21;
   m13 = m.m31;
   m14 = 0;

   m21 = m.m12;
   m22 = m.m22;
   m23 = m.m32;
   m24 = 0;

   m31 = m.m13;
   m32 = m.m23;
   m33 = m.m33;
   m34 = 0;

   Vector v(m.m14, m.m24, m.m34);

   Vector tt = *this * v;

   m14 = -tt.x;
   m24 = -tt.y;
   m34 = -tt.z;
}


void Matrix::AlignToVector(const Vector &dir) {

   Vector s(0, -1, 0);

   if(dir.x == s.x && dir.y == s.y && dir.z == s.z)
      s = Vector(0, 0, -1);

   Vector d = ~dir;
   Vector r = ~(s % d);
   Vector u = ~(d % r);

   *this = Matrix(MAT_COLS, r, u, d, Vector(0, 0, 0));
}

#endif
