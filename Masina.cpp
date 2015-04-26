#include "Masina.h"
#include "Util.h"

Masina::Masina (double x, double y) : m_x(x), m_y(y), m_speed(0), m_theta(90) {}

double Masina::getX () const { return m_x; }
double Masina::getY () const { return m_y; }
double Masina::getSpeed () const { return m_speed; }
double Masina::getTheta () const { return m_theta; };

void Masina::setPosition (int x, int y) {
    m_x = x;
    m_y = y;
}

void Masina::reset () {
    m_speed = 0.0f;
    m_theta = 90;
}

void Masina::increaseSpeed () {
    if (m_speed < TOP_SPEED)
        m_speed += 0.01f;
}
void Masina::decreaseSpeed () {
    if (m_speed > TOP_REVERSE_SPEED)
        m_speed -= 0.01f;
}

void Masina::turnLeft () { m_theta += 3.0f; }
void Masina::turnRight () { m_theta -= 3.0f; }

void Masina::update (double timeElapsed) {
    // "Intervine si frecarea"
    if (m_speed > 0) {
        m_speed -= SLOW_DOWN * timeElapsed;
        if (m_speed <= 0)
            m_speed = 0;
    } else if (m_speed < 0) {
        m_speed += SLOW_DOWN * timeElapsed;
        if (m_speed >= 0)
            m_speed = 0;
    }

    double vx = m_speed * cos(Util::degreesToRadians(m_theta));
    double vy = m_speed * sin(Util::degreesToRadians(m_theta));

    m_x += vx * timeElapsed;
    m_y += vy * timeElapsed;
}

void Masina::bump () {
    m_speed = - (m_speed);
}