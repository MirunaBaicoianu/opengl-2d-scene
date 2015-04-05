/**
 * Authors: Miruna BAICOIANU, Ovidiu PODARIU
 * Date:    1/Apr/2015
 * Title:   Scena 2D
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <gl/freeglut.h>

#include "Vec3.h"
#include "Triunghi.h"
#include "Util.h"
#include "Masina.h"

// Pozitia ferestrei
#define X 100
#define Y 100

// Dimensiunile ferestrei
#define WIDTH  800
#define HEIGHT 600

// Titlul ferestrei
#define TITLE "Scena 2D"

#define FPS 60


Masina masina;

// Coordonatele de start ale circuitului
double start_x, start_y;

// Punctele ce definesc exteriorul circuitului
std::vector<Vec3> circuit_exterior;

// Triunghiurile ce definesc exteriorul circuitului
std::vector<Triunghi> circuit_exterior_triunghiuri;

// Punctele ce definesc interiorul circuitului
std::vector<Vec3> circuit_interior;

// Triunghiurile ce definesc interiorul circuitului
std::vector<Triunghi> circuit_interior_triunghiuri;

// Punctele ce definesc linia separatoare
std::vector<Vec3> linie_separatoare;

// Indica daca o tasta este apasata sau nu
bool keys[256];


// Initializeaza mediul GL si fereastra de vizualizare.
void initGL (int argc, char** argv) {
	glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition (X, Y);
    glutInitWindowSize (WIDTH, HEIGHT);
    glutCreateWindow (TITLE);
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, WIDTH, 0.0, HEIGHT);
}

void draw (void) {
    glClear (GL_COLOR_BUFFER_BIT);
    glClearColor (0.0117, 0.1294, 0.0117, 0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // --------------------------- CIRCUIT ----------------------------
    // Circuitul exterior
    glColor3f (0.4901, 0.5490, 0.6392);
    glBegin (GL_TRIANGLES);
        for (int i = 0; i < circuit_exterior_triunghiuri.size(); i++) {
            glVertex2d (circuit_exterior_triunghiuri[i].getV1().getC1(),
                        circuit_exterior_triunghiuri[i].getV1().getC2());

            glVertex2d (circuit_exterior_triunghiuri[i].getV2().getC1(),
                        circuit_exterior_triunghiuri[i].getV2().getC2());

            glVertex2d (circuit_exterior_triunghiuri[i].getV3().getC1(),
                        circuit_exterior_triunghiuri[i].getV3().getC2());
        }
	glEnd ();

    glColor3f (0.0, 0.0, 0.0);
    glLineWidth(7);
    glBegin (GL_LINE_LOOP);
        for (int i = 0; i < circuit_exterior.size(); i++)
            glVertex2d (circuit_exterior[i].getC1(), circuit_exterior[i].getC2());
	glEnd ();

    // Circuitul interior
    glColor3f (0.0117, 0.1294, 0.0117);
    glBegin (GL_TRIANGLES);
        for (int i = 0; i < circuit_interior_triunghiuri.size(); i++) {
            glVertex2d (circuit_interior_triunghiuri[i].getV1().getC1(),
                        circuit_interior_triunghiuri[i].getV1().getC2());

            glVertex2d (circuit_interior_triunghiuri[i].getV2().getC1(),
                        circuit_interior_triunghiuri[i].getV2().getC2());

            glVertex2d (circuit_interior_triunghiuri[i].getV3().getC1(),
                        circuit_interior_triunghiuri[i].getV3().getC2());
        }
	glEnd ();

    glColor3f (0.0, 0.0, 0.0);
    glLineWidth(7);
    glBegin (GL_LINE_LOOP);
        for (int i = 0; i < circuit_interior.size(); i++)
            glVertex2d (circuit_interior[i].getC1(), circuit_interior[i].getC2());
	glEnd ();

    // Linie separatoare
    glColor3f (1.0, 1.0, 1.0);
    glLineWidth(3);
    glEnable (GL_LINE_STIPPLE);
    glLineStipple(1, 0xF00F);
    glBegin (GL_LINE_LOOP);
        for (int i = 0; i < linie_separatoare.size(); i++)
            glVertex2d (linie_separatoare[i].getC1(), linie_separatoare[i].getC2());
	glEnd ();
    glDisable (GL_LINE_STIPPLE);
    // ------------------------- END CIRCUIT ---------------------------


    // Coordonatele curente ale masinii
    double x = masina.getX();
    double y = masina.getY();
    double theta = masina.getTheta();

    // Transformari
    glLoadIdentity();
    glTranslated(x, y, 0.0f);
    glRotated(theta - 90, 0.0f, 0.0f, 1.0f);
    glTranslated(-x, -y, 0.0f);

	glColor3f (0.5568, 0.2313, 0.2745);
    glLineWidth (3.0);

	glBegin (GL_POLYGON);
		glVertex2d (     x, y + 10);
        glVertex2d (x + 10, y - 10);
        glVertex2d (     x, y -  4);
        glVertex2d (x - 10, y - 10);
	glEnd ();
	
    glutSwapBuffers();
    glFlush ();
}

void keyboard (unsigned char key, int x, int y) {
    keys[key] = true;
}

void keyboardUp (unsigned char key, int x, int y) {
    keys[key] = false;
}

bool hasCollided () {
    // Coliziunea va fi testata doar intre cele doua
    // laturi (stanga si dreapta) ale masinii si circuit
    Vec3 masina_sus(masina.getX(),     masina.getY() + 5);
    Vec3 masina_st (masina.getX() - 5, masina.getY() - 5);
    Vec3 masina_dr (masina.getX() + 5, masina.getY() - 5);

    // Verifica coliziunea cu circuitul exterior
    for (int i = 0; i < circuit_exterior.size() - 1; i++) {
        // Latura stanga
        if (Util::intersecteazaSegmente(masina_sus, masina_st, circuit_exterior[i], circuit_exterior[i + 1]))
            return true;
        // Latura dreapta
        if (Util::intersecteazaSegmente(masina_sus, masina_dr, circuit_exterior[i], circuit_exterior[i + 1]))
            return true;
    }
    // Verifica coliziunea cu ultima latura a circuitului exterior
    if (Util::intersecteazaSegmente(masina_sus, masina_st,
                                    circuit_exterior[circuit_exterior.size() - 1], circuit_exterior[0]))
        return true;
    if (Util::intersecteazaSegmente(masina_sus, masina_dr,
                                    circuit_exterior[circuit_exterior.size() - 1], circuit_exterior[0]))
        return true;


    // Verifica coliziunea cu circuitul interior
    for (int i = 0; i < circuit_interior.size() - 1; i++) {
        // Latura stanga
        if (Util::intersecteazaSegmente(masina_sus, masina_st, circuit_interior[i], circuit_interior[i + 1]))
            return true;
        // Latura dreapta
        if (Util::intersecteazaSegmente(masina_sus, masina_dr, circuit_interior[i], circuit_interior[i + 1]))
            return true;
    }
    // Verifica coliziunea cu ultima latura a circuitului interior
    if (Util::intersecteazaSegmente(masina_sus, masina_st,
                                    circuit_interior[circuit_interior.size() - 1], circuit_interior[0]))
        return true;
    if (Util::intersecteazaSegmente(masina_sus, masina_dr,
                                    circuit_interior[circuit_interior.size() - 1], circuit_interior[0]))
        return true;

    return false;
}

void checkInput () {
    if (keys['w']) masina.increaseSpeed();
    if (keys['s']) masina.decreaseSpeed();

    if (keys['a']) masina.turnLeft();
    if (keys['d']) masina.turnRight();

    if (keys['r']) {
        masina.setPosition(start_x, start_y);
        masina.reset();
    }
}

void update (int t0) {
    checkInput();

    if (hasCollided())
        masina.bump();

    int t1 = glutGet(GLUT_ELAPSED_TIME);
    int elapsedTime = t1 - t0;

    masina.update(elapsedTime);

    glutPostRedisplay();

    glutTimerFunc(1000 / FPS, update, t1);
}

void loadCircuit (std::string filename) {
    std::ifstream f(filename);

    f >> start_x >> start_y;
    masina.setPosition(start_x, start_y);

    int n;
    Vec3 v;

    f >> n;

    circuit_exterior.reserve(n);
    for (int i = 0; i < n; i++) {
        f >> v;
        circuit_exterior.push_back(v);
    }

    f >> n;

    circuit_interior.reserve(n);
    for (int i = 0; i < n; i++) {
        f >> v;
        circuit_interior.push_back(v);
    }
    
    // Este necesara triangularea circuitului deoarece
    // se poate intampla sa fie concav
    circuit_exterior_triunghiuri = Util::triangulare(circuit_exterior);
    circuit_interior_triunghiuri = Util::triangulare(circuit_interior);

    f >> n;

    linie_separatoare.reserve(n);
    for (int i = 0; i < n; i++) {
        f >> v;
        linie_separatoare.push_back(v);
    }
}

int main (int argc, char** argv) {
    loadCircuit("input/circuit2.txt");

    initGL (argc, argv);
	
    glutDisplayFunc (draw);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);

    glutTimerFunc(1000 / FPS, update, glutGet(GLUT_ELAPSED_TIME));

	glutMainLoop ();

	return 0;
}