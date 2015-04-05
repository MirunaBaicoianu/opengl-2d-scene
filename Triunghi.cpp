#include "Triunghi.h"

Triunghi::Triunghi (Vec3 v1, Vec3 v2, Vec3 v3) : m_v1(v1), m_v2(v2), m_v3(v3) {}
Triunghi::Triunghi (const Triunghi& t) : m_v1(t.m_v1), m_v2(t.m_v2), m_v3(t.m_v3) {}

Vec3 Triunghi::getV1 () const { return m_v1; }
Vec3 Triunghi::getV2 () const { return m_v2; }
Vec3 Triunghi::getV3 () const { return m_v3; }

void Triunghi::setV1 (Vec3 v) { m_v1 = v; }
void Triunghi::setV2 (Vec3 v) { m_v2 = v; }
void Triunghi::setV3 (Vec3 v) { m_v3 = v; }

std::ostream& operator<< (std::ostream& os, const Triunghi& t) {
	os << t.m_v1 << " " << t.m_v2 << " " << t.m_v3;

	return os;
}
std::istream& operator>> (std::istream& is, Triunghi& t) {
	is >> t.m_v1;
	is >> t.m_v2;
	is >> t.m_v3;

	return is;
}

double Triunghi::calculeazaArie () const {
    double arie;

    arie = (m_v2.getC1() - m_v1.getC1()) * (m_v3.getC2() - m_v1.getC2())
         - (m_v3.getC1() - m_v1.getC1()) * (m_v2.getC2() - m_v1.getC2());

    return abs(arie) / 2;
}

double Triunghi::calculeazaArie (const Vec3& v1, const Vec3& v2, const Vec3& v3) {
    double arie;

    arie = (v2.getC1() - v1.getC1()) * (v3.getC2() - v1.getC2())
         - (v3.getC1() - v1.getC1()) * (v2.getC2() - v1.getC2());

    return abs(arie) / 2;
}

bool Triunghi::continePunct (const Vec3& v) const {
    // Punctul P se gaseste in interiorul triunghiului
    // sau pe laturile sale daca suma ariilor subtriungiurilor
    // (ABP, ACP, BCP) este egala cu suma triunhiului ABC.
    double arie_ABP = Triunghi::calculeazaArie(m_v1, m_v2, v);
    double arie_ACP = Triunghi::calculeazaArie(m_v1, m_v3, v);
    double arie_BCP = Triunghi::calculeazaArie(m_v2, m_v3, v);
    double arie_subtriunghiuri = arie_ABP + arie_ACP + arie_BCP;

    if (abs(calculeazaArie() - arie_subtriunghiuri) < 0.0001)
        return true;

    return false;
}

bool Triunghi::continePunct (double x, double y, double z) const {
    Vec3 v(x, y, z);

    // Punctul P se gaseste in interiorul triunghiului
    // sau pe laturile sale daca suma ariilor subtriungiurilor
    // (ABP, ACP, BCP) este egala cu suma triunhiului ABC.
    double arie_ABP = Triunghi::calculeazaArie(m_v1, m_v2, v);
    double arie_ACP = Triunghi::calculeazaArie(m_v1, m_v3, v);
    double arie_BCP = Triunghi::calculeazaArie(m_v2, m_v3, v);
    double arie_subtriunghiuri = arie_ABP + arie_ACP + arie_BCP;

    if (abs(calculeazaArie() - arie_subtriunghiuri) < 0.0001)
        return true;

    return false;
}