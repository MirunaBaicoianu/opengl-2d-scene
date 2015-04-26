#include "ObstacolSpin.h"
#include <math.h>

ObstacolSpin::ObstacolSpin (Vec3 a, Vec3 b, double rotation_speed)
    : Obstacol(a, b), m_rotation_speed(rotation_speed)
{
    m_radius = abs(a.getC2() - b.getC2()) / 2;
}

Vec3 ObstacolSpin::getA () const {
    double x = m_center.getC1() + m_radius * cos(m_theta);
    double y = m_center.getC2() + m_radius * sin(m_theta);

    return Vec3(x, y, 0);
}

Vec3 ObstacolSpin::getB () const {
    double x = m_center.getC1() - m_radius * cos(m_theta);
    double y = m_center.getC2() - m_radius * sin(m_theta);

    return Vec3(x, y, 0);
}

void ObstacolSpin::update (double elapsedTime) {
    m_theta = m_theta + m_rotation_speed * elapsedTime;
}