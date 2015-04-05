#pragma once

#include <iostream>
#include <string>

class Vec3 {
 private:
     double m_c1;
     double m_c2;
     double m_c3;
 
 public:
     Vec3 (double c1 = 0, double c2 = 0, double c3 = 0);
     Vec3 (const Vec3& v);
     
     double getC1 () const;
     double getC2 () const;
     double getC3 () const;
     
     void setC1 (double c);
     void setC2 (double c);
     void setC3 (double c);
     void setAll (double c1, double c2, double c3);
     
     Vec3 operator+ (const Vec3& v) const;
     Vec3 operator- (const Vec3& v) const;
     
     friend std::ostream& operator<< (std::ostream& os, const Vec3& v);
     friend std::istream& operator>> (std::istream& is, Vec3& v);
     
     Vec3 produs_vectorial (const Vec3& v);
};