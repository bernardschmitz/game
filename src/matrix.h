
// $Id: matrix.h,v 1.2 2003-08-13 02:26:32 bernard Exp $

#ifndef __MATRIX33_H__
#define __MATRIX33_H__

#include <math.h>
#include <iostream>

#include "vector.h"



class matrix33 {
public:
   float m11, m12, m13;
   float m21, m22, m23;
   float m31, m32, m33;

   matrix33() { m11 = m12 = m13 = 
                m21 = m22 = m23 = 
                m31 = m32 = m33 = one; }
   matrix33(const float r1c1, const float r1c2, const float r1c3, 
            const float r2c1, const float r2c2, const float r2c3, 
            const float r3c1, const float r3c2, const float r3c3) {

      m11 = r1c1;   m12 = r1c2;   m13 = r1c3;
      m21 = r2c1;   m22 = r2c2;   m23 = r2c3;
      m31 = r3c1;   m32 = r3c2;   m33 = r3c3;
   }

   ~matrix33() { }

   float det() const;
   matrix33 transpose() const;
   matrix33 inverse() const;

   matrix33 matrix33::operator*=(const float s);
   matrix33 matrix33::operator/=(const float s);
   matrix33 matrix33::operator-=(const float s);
   matrix33 matrix33::operator+=(const float s);
};

inline float matrix33::det() const {

   return    m11*m22*m33 -
             m11*m32*m23 +
             m21*m32*m13 -
             m21*m12*m33 +
             m31*m12*m23 -
             m31*m22*m13;
}

inline matrix33 matrix33::transpose() const {

   return matrix33( m11, m21, m31,
                    m12, m22, m32, 
                    m13, m23, m33  );
}



inline matrix33 matrix33::inverse() const{

   float d = det();

   if(d == zero)
      d = one;

   return matrix33(  (m22*m33 - m23*m32) / d, 
                    -(m12*m33 - m13*m32) / d,
                     (m12*m23 - m13*m22) / d,
                    -(m21*m33 - m23*m31) / d,
                     (m11*m33 - m13*m31) / d,
                    -(m11*m23 - m13*m21) / d,
                     (m21*m32 - m22*m31) / d,
                    -(m11*m32 - m12*m31) / d,
                     (m11*m22 - m12*m21) / d  );
}


inline matrix33 matrix33::operator*=(const float s) {

   m11 *= s;   m12 *= s;   m13 *= s;
   m21 *= s;   m22 *= s;   m23 *= s;
   m31 *= s;   m32 *= s;   m33 *= s;

   return *this;
}

inline matrix33 matrix33::operator/=(const float s) {

   m11 /= s;   m12 /= s;   m13 /= s;
   m21 /= s;   m22 /= s;   m23 /= s;
   m31 /= s;   m32 /= s;   m33 /= s;

   return *this;
}

inline matrix33 matrix33::operator+=(const float s) {

   m11 += s;   m12 += s;   m13 += s;
   m21 += s;   m22 += s;   m23 += s;
   m31 += s;   m32 += s;   m33 += s;

   return *this;
}


inline matrix33 matrix33::operator-=(const float s) {

   m11 -= s;   m12 -= s;   m13 -= s;
   m21 -= s;   m22 -= s;   m23 -= s;
   m31 -= s;   m32 -= s;   m33 -= s;

   return *this;
}



inline matrix33 operator*(const matrix33& a, const matrix33& b) {

   return matrix33( a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31, 
                    a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32,
                    a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33,
                    a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31,
                    a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32,
                    a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33,
                    a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31,
                    a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32,
                    a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33  );

}

inline matrix33 operator/(const matrix33& m, float s) {

   return matrix33( m.m11/s, m.m12/s, m.m13/s, 
                    m.m21/s, m.m22/s, m.m23/s, 
                    m.m31/s, m.m32/s, m.m33/s  );
}


inline matrix33 operator*(const matrix33& m, float s) {

   return matrix33( m.m11*s, m.m12*s, m.m13*s, 
                    m.m21*s, m.m22*s, m.m23*s, 
                    m.m31*s, m.m32*s, m.m33*s  );
}

inline matrix33 operator*(float s, const matrix33& m) {

   return m * s;
}



inline vector3 operator*(const matrix33& m, const vector3& v) {

   return vector3( m.m11*v.x + m.m12*v.y + m.m13*v.z,
                   m.m21*v.x + m.m22*v.y + m.m23*v.z,   
                   m.m31*v.x + m.m32*v.y + m.m33*v.z  );
}

inline vector3 operator*(const vector3& v, const matrix33& m) {

   return vector3( v.x*m.m11 + v.y*m.m21 + v.z*m.m31, 
                   v.x*m.m12 + v.y*m.m22 + v.z*m.m32, 
                   v.x*m.m13 + v.y*m.m23 + v.z*m.m33  );
}



inline std::ostream& operator<<(std::ostream& s, const matrix33& m) {

   s << "({" << m.m11 << "," << m.m12 << "," << m.m13 << "},{"
             << m.m21 << "," << m.m22 << "," << m.m23 << "},{"
             << m.m31 << "," << m.m32 << "," << m.m33 << "})";

   return s;
}



  
#endif

