#include "Vec3.h"

Vec3::Vec3 (double c1, double c2, double c3) : m_c1(c1), m_c2(c2), m_c3(c3) {}
Vec3::Vec3 (const Vec3& v) : m_c1(v.m_c1), m_c2(v.m_c2), m_c3(v.m_c3) {}

double Vec3::getC1 () const { return m_c1; }
double Vec3::getC2 () const { return m_c2; }
double Vec3::getC3 () const { return m_c3; }

void Vec3::setC1 (double c) { m_c1 = c; }
void Vec3::setC2 (double c) { m_c2 = c; }
void Vec3::setC3 (double c) { m_c3 = c; }
void Vec3::setAll (double c1, double c2, double c3) {
     m_c1 = c1;
     m_c2 = c2;
     m_c3 = c3;
}

Vec3 Vec3::operator+ (const Vec3& v) const {
    return Vec3(m_c1 + v.m_c1, m_c2 + v.m_c2, m_c3 + v.m_c3);
}

Vec3 Vec3::operator- (const Vec3& v) const {
    return Vec3(m_c1 - v.m_c1, m_c2 - v.m_c2, m_c3 - v.m_c3);
}

std::ostream& operator<< (std::ostream& os, const Vec3& v) {
    os << " (" << v.m_c1 << ", " << v.m_c2 << ", " << v.m_c3 << ") ";
    return os;
}

std::istream& operator>> (std::istream& is, Vec3& v) {
    is >> v.m_c1 >> v.m_c2 >> v.m_c3;
    return is;
}

Vec3 Vec3::produs_vectorial (const Vec3& v) {
    Vec3 r;

    r.setC1(m_c2 * v.m_c3 - m_c3 * v.m_c2);
    r.setC2(- (m_c1 * v.m_c3 - m_c3 * v.m_c1));
    r.setC3(m_c1 * v.m_c2 - m_c2 * v.m_c1);

    return r;
}