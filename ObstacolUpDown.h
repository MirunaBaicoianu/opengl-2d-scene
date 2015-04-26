#pragma once

#include "Obstacol.h"

class ObstacolUpDown : public Obstacol {
 private:
     static const double SPEED;

     // Segmentul [AB] va fi orientat vertical,
     // cu varful A sus, iar B jos.

     // Coordonatele Y ale limitelor
     double m_up_limit;
     double m_down_limit;

     // Directia curenta de miscare: sus(+1) sau jos(-1);
     int m_direction;

 public:
     ObstacolUpDown (Vec3 a, Vec3 b, double up_limit, double down_limit);

     void update (double elapsedTime);
};