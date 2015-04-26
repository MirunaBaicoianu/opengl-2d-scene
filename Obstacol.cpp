#include "Obstacol.h"

Obstacol::Obstacol (Vec3 a, Vec3 b , double theta) : m_a(a), m_b(b), m_theta(theta) {
    m_center = (m_a + m_b) / 2;
}

Vec3 Obstacol::getA () const { return m_a; }
Vec3 Obstacol::getB () const { return m_b; }
Vec3 Obstacol::getCenter () const { return m_center; }
double Obstacol::getTheta () const { return m_theta; }