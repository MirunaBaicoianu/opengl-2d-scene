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
#include "ObstacolUpDown.h"
#include "ObstacolSpin.h"

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

std::vector<Obstacol*> obstacole;

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

unsigned int nr_collisions = 0;


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

void drawCounter (void) {
    // Fundal
    if (nr_collisions <= 5)
        glColor3f (0.0f, 1.0f, 0.0f);
    else if (nr_collisions <= 20)
        glColor3f (1.0f, 1.0f, 0.0f);
    else
        glColor3f (1.0f, 0.0f, 0.0f);

    glRectd (WIDTH - 175, HEIGHT - 30, WIDTH - 5, HEIGHT - 5);

    // Border
    glColor3f (0.0f, 0.0f, 0.0f);
    glBegin (GL_LINE_LOOP);
        glVertex2f (WIDTH - 175, HEIGHT -  5);
        glVertex2f (WIDTH -   5, HEIGHT -  5);
        glVertex2f (WIDTH -   5, HEIGHT - 30);
        glVertex2f (WIDTH - 175, HEIGHT - 30);
    glEnd ();


    // Text
    std::string s = "Collisions: ";
    s += std::to_string(nr_collisions);

    glColor3f (0.0f, 0.0f, 0.0f);
    glRasterPos2d (WIDTH - 165, HEIGHT - 20);
    void* font = GLUT_BITMAP_9_BY_15;

    for (std::string::iterator i = s.begin(); i != s.end(); i++)
        glutBitmapCharacter(font, *i);
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
    /*glLoadIdentity();
    glTranslated(x, y, 0.0f);
    glRotated(theta - 90, 0.0f, 0.0f, 1.0f);
    glTranslated(-x, -y, 0.0f);*/
    glPushMatrix();
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
	
    glPopMatrix();


    // ------------------ OBSTACOLE ----------------------
    glColor3f(0.0f, 0.0f, 1.0f);
    glLineWidth(5);

    double x1, y1, x2, y2;
    double x_mij, y_mij;
    for (int i = 0; i < obstacole.size(); i++) {
        x1 = obstacole[i]->getA().getC1();
        y1 = obstacole[i]->getA().getC2();
        x2 = obstacole[i]->getB().getC1();
        y2 = obstacole[i]->getB().getC2();

        x_mij = obstacole[i]->getCenter().getC1();
        y_mij = obstacole[i]->getCenter().getC2();

        theta = obstacole[i]->getTheta();
        
        glPushMatrix();
        
        glTranslated(x_mij, y_mij, 0.0f);
        glRotated(theta, 0.0f, 0.0f, 1.0f);
        glTranslated(-x_mij, -y_mij, 0.0f);

        glBegin(GL_LINES);
        {
            glVertex2d(x1, y1);
            glVertex2d(x2, y2);
        }
        glEnd();

        glPopMatrix();
    }
    // ---------------- END OBSTACOLE --------------------

    drawCounter();

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
    // --------------- COLIZIUNI CU CIRCUITUL -------------------
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
    // ------------- END COLIZIUNI CU CIRCUITUL -----------------


    // --------------- COLIZIUNI CU OBSTACOLELE -------------------
    Vec3 a, b;
    for (int i = 0; i < obstacole.size(); i++) {
        a = obstacole[i]->getA();
        b = obstacole[i]->getB();
        
        if (Util::intersecteazaSegmente(masina_sus, masina_st, a, b))
            return true;
        if (Util::intersecteazaSegmente(masina_sus, masina_dr, a, b))
            return true;
    }
    // ------------- END COLIZIUNI CU OBSTACOLELE -----------------


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
        nr_collisions = 0;
    }
}

void update (int t0) {
    checkInput();

    if (hasCollided()) {
        nr_collisions++;
        std::cout << "Nr. collisions: " << nr_collisions << " - "
                  << masina.getX() << " " << masina.getY() << std::endl;
        masina.bump();
    }

    int t1 = glutGet(GLUT_ELAPSED_TIME);
    int elapsedTime = t1 - t0;

    masina.update(elapsedTime);

    for (int i = 0; i < obstacole.size(); i++)
        obstacole[i]->update(elapsedTime);

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


    // Load obstacole
    f >> n;
    obstacole.resize(n);
    
    int tip_obstacol;
    Vec3 a, b;
    double rotation_speed;
    double up_limit, down_limit;
    for (int i = 0; i < n; i++) {
        f >> tip_obstacol;
        if (tip_obstacol == 1) { // Obstacol UpDown
            f >> a >> b >> up_limit >> down_limit;
            obstacole[i] = new ObstacolUpDown(a, b, up_limit, down_limit);
        } else if (tip_obstacol == 2) { // Obstacol Spin
            f >> a >> b >> rotation_speed;
            obstacole[i] = new ObstacolSpin(a, b, rotation_speed);
        }
    }
}

void destroyObstacole (void) {
    for (int i = 0; i < obstacole.size(); i++)
        delete obstacole[i];
}

int main (int argc, char** argv) {
    loadCircuit("input/circuit2.txt");

    initGL (argc, argv);
	
    glutDisplayFunc (draw);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);

    glutTimerFunc(1000 / FPS, update, glutGet(GLUT_ELAPSED_TIME));

	glutMainLoop ();

    destroyObstacole();

	return 0;
}