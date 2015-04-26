#pragma once

#include "Obstacol.h"

class ObstacolSpin : public Obstacol {
 private:
     // Raza cercului descris de miscarea obstacolului
     double m_radius;

     double m_rotation_speed;

 public:
     ObstacolSpin (Vec3 a, Vec3 b, double rotation_speed);

     Vec3 getA () const;
     Vec3 getB () const;

     void update (double elapsedTime);
};