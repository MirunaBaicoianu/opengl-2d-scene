#pragma once

#define TOP_SPEED           0.15000f
#define TOP_REVERSE_SPEED  -0.07500f
#define SLOW_DOWN           0.00015f

class Masina {
 private:
     double m_x;
     double m_y;

     double m_speed;

     // Indica directia masinii
     // i.e numarul de grade in sens trigonometric
     double m_theta;

 public:
     Masina (double x = 0.0, double y = 0.0);
     double getX () const;
     double getY () const;
     double getSpeed () const;
     double getTheta () const;
     
     void setPosition (int x, int y);
     void reset ();
     
     void increaseSpeed ();
     void decreaseSpeed ();

     void turnLeft ();
     void turnRight ();

     void update (double timeElapsed);
     void bump ();
};