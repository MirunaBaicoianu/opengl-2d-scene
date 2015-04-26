#pragma once

#include "Vec3.h"

// Obstacolele sunt segmente [AB]
class Obstacol {
 protected:
     Vec3 m_a;
     Vec3 m_b;
     Vec3 m_center;

     double m_theta;

 public:
     Obstacol (Vec3 a = Vec3(), Vec3 b = Vec3(), double theta = 90.0);
     
     virtual Vec3 getA () const;
     virtual Vec3 getB () const;
     Vec3 getCenter () const;
     double getTheta () const;

     virtual void update (double elapsedTime) = 0;
};
