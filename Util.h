#pragma once

#include <vector>

#include "Vec3.h"
#include "Triunghi.h"

class Util {
public:
    // Face conversia de la grade la radiani
    static double degreesToRadians (double theta);
    
    // Trianguleaza poligonul determinat de punctele specificate
    static std::vector<Triunghi> triangulare (std::vector<Vec3> puncte);

    // Testeaza daca cele doua segmente, S1(a, b) si S2(c, d), se intersecteaza
    static bool intersecteazaSegmente (const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d);
};