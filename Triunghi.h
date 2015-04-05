#pragma once

#include "Vec3.h"
#include <string>

class Triunghi {
 private:
     Vec3 m_v1;
     Vec3 m_v2;
     Vec3 m_v3;

 public:
     Triunghi (Vec3 v1 = Vec3(), Vec3 v2 = Vec3(), Vec3 v3 = Vec3());
     Triunghi (const Triunghi& t);
     
     Vec3 getV1 () const;
     Vec3 getV2 () const;
     Vec3 getV3 () const;
     
     void setV1 (Vec3 v);
     void setV2 (Vec3 v);
     void setV3 (Vec3 v);
     
     friend std::ostream& operator<< (std::ostream& os, const Triunghi& t);
     friend std::istream& operator>> (std::istream& is, Triunghi& t);
     
     double calculeazaArie () const;
     static double calculeazaArie (const Vec3& v1, const Vec3& v2, const Vec3& v3);
     
     bool continePunct (const Vec3& v) const;
     bool continePunct (double x, double y, double z) const;
};