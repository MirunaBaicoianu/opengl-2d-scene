#include "ObstacolUpDown.h"

const double ObstacolUpDown::SPEED = 0.05f;

ObstacolUpDown::ObstacolUpDown (Vec3 a, Vec3 b, double up_limit, double down_limit) 
    : Obstacol(a, b, 0.0f), m_up_limit(up_limit), m_down_limit(down_limit), m_direction(1) {}

void ObstacolUpDown::update (double elapsedTime) {
    // Se misca in sus/jos daca poate
    // i.e nu a depasit limita de sus/jos
    if (m_a.getC2() > m_up_limit)
        m_direction = -1;
    else if (m_b.getC2() < m_down_limit)
        m_direction = +1;

    m_a.setC2(m_a.getC2() + m_direction * SPEED * elapsedTime);
    m_b.setC2(m_b.getC2() + m_direction * SPEED * elapsedTime);
}