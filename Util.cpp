#include <stdlib.h>
#include <math.h>
#include "Util.h"

#define M_PI    3.14159
#define MAXINT  1 << 30

double Util::degreesToRadians (double theta) {
    return theta * M_PI / 180;
}

void determinaSemne(const std::vector<Vec3>& puncte, std::vector<int>& semne) {
    unsigned int nr_puncte = puncte.size();

    // Determina semnul primului varf
    if ((puncte[0] - puncte[nr_puncte - 1]).produs_vectorial(puncte[1] - puncte[0]).getC3() < 0)
        semne[0] = -1;
    else
        semne[0] = 1;

    // Determina semnul ultimului varf
    if ((puncte[nr_puncte - 1] - puncte[nr_puncte - 2]).produs_vectorial(puncte[0] - puncte[nr_puncte - 1]).getC3() < 0)
        semne[nr_puncte - 1] = -1;
    else
        semne[nr_puncte - 1] = 1;
    
    // Determina semnele celorlalte varfuri
    for (int i = 1; i < nr_puncte - 1; i++) {
        if ((puncte[i] - puncte[i - 1]).produs_vectorial(puncte[i + 1] - puncte[i]).getC3() < 0)
            semne[i] = -1;
        else
            semne[i] = 1;
    }
}

void determinaSemnVarfMinim(const std::vector<Vec3>& puncte, const std::vector<int>& semne, int& semn_varf_conex) {
    // Gaseste cel mai din stanga varf deoarece acesta este mereu conex!
    // Semnul lui reprezinta semnul varfurilor conexe.

    double minim = MAXINT;
    for (int i = 0; i < puncte.size(); i++)
        if (puncte[i].getC1() < minim) {
            minim = puncte[i].getC1();
            semn_varf_conex = semne[i];
        }
}

std::vector<Triunghi> Util::triangulare (std::vector<Vec3> puncte) {
    // Un varf poate fi convex/concav
    std::vector<int> semne;
    semne.resize(puncte.size());
    int semn_varf_convex;

    // N puncte determina (N - 2) triunghiuri
    int nr_triunghiuri = puncte.size() - 2;
    std::vector<Triunghi> triunghiuri;
    triunghiuri.reserve(nr_triunghiuri);

    Triunghi t;
    unsigned int predecesor, succesor;
    bool varf_principal;

    for (int i = 0; i < nr_triunghiuri; i++) {
        determinaSemne(puncte, semne);
        determinaSemnVarfMinim(puncte, semne, semn_varf_convex);

        for (int varf = 0; varf < puncte.size(); varf++) {
            varf_principal = true;

            // Verifica daca este convex
            if (semne[varf] == semn_varf_convex) {
                // Verifica daca este principal
                // i.e triunghiul (varf - 1)(varf)(varf + 1) nu contine alte varfuri
                if (varf == 0) {
                    predecesor = puncte.size() - 1;
                    succesor   = 1;
                } else if (varf == puncte.size() - 1) {
                    predecesor = puncte.size() - 2;
                    succesor   = 0;
                } else {
                    predecesor = varf - 1;
                    succesor   = varf + 1;
                }

                // "Construieste" triunghiul predecesor-succesor
                t.setV1(puncte[predecesor]);
                t.setV2(puncte[varf]);
                t.setV3(puncte[succesor]);

                // Verifica daca varful este principal
                // i.e celelalte varfuri nu sunt cuprinse in acest triunghi
                for (int alt_varf = 0; alt_varf < predecesor && varf_principal; alt_varf++)
                    if (t.continePunct(puncte[alt_varf]))
                        varf_principal = false;

                for (int alt_varf = succesor + 1; alt_varf < puncte.size() && varf_principal; alt_varf++)
                    if (t.continePunct(puncte[alt_varf]))
                        varf_principal = false;

                if (varf_principal) {
                    // Retine triunghiul
                    triunghiuri.push_back(t);

                    // Elimina varful
                    puncte.erase(puncte.begin() + varf);
                    semne.erase(semne.begin() + varf);
                }
            }
        }
    }

    return triunghiuri;
}

bool Util::intersecteazaSegmente (const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d) {
    // Segment 1: capete A(x1, y1) si B(x2, y2)
    double xA = a.getC1(), yA = a.getC2();
    double xB = b.getC1(), yB = b.getC2();

	// Segment 2: capete C(x1, y1) si D(x2, y2)
    double xC = c.getC1(), yC = c.getC2();
    double xD = d.getC1(), yD = d.getC2();

	// Punctele de pe un segment AB sunt de forma:
	// (1 - lambda) * A + lambda * B, cu lambda in [0, 1].
	// Punctele de pe un segment CD sunt de forma:
	// (1 - mu) * A + mu * B, cu mu in [0, 1].
	double lambda, mu;

	// Calculeaza determinantul sistemului
	double delta, delta_lambda, delta_mu;
	delta = (xB - xA) * (yC - yD) - (xC - xD) * (yB - yA);
	
	// Daca dreptele sunt paralele
	if (delta == 0) {
		return false;
	} else {
		delta_lambda = (xC - xA) * (yC - yD) - (xC - xD) * (yC - yA);
		delta_mu     = (xB - xA) * (yC - yA) - (xC - xA) * (yB - yA);

		lambda = delta_lambda / delta;
		mu = delta_mu / delta;

		// Verifica daca solutiile sunt in [0, 1]
		if (lambda >= 0 && lambda <= 1 && mu >= 0 && mu <= 1) {
			return true;
		} else {
			return false;
        }
	}
}