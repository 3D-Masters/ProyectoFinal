#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <chrono>

#include <cstdlib>

#include "src/Scene.hpp"

using namespace std;

float WIDTH = 1280;
float HEIGHT = 720;

float FOVY=60.0;
float ZNEAR=0.01;
float ZFAR=150.0;

Scene escena;

void drawPlane()
{
    glBegin(GL_QUADS);
     glColor3f(0.2f,0.2f,0.2f);
     glVertex3f( 1.0f, 0.0f,  1.0f);
     glVertex3f(-1.0f, 0.0f,  1.0f);
     glVertex3f(-1.0f, 0.0f, -1.0f);
     glVertex3f( 1.0f, 0.0f, -1.0f);
    glEnd();
}

/*
void drawAxis()
{
     //X axis in red
     glBegin(GL_LINES);
       glColor3f(1.0f,0.0f,0.0f);
       glVertex3f(X_MIN,0.0,0.0);
       glColor3f(1.0f,0.0f,0.0f);
       glVertex3f(X_MAX,0.0,0.0);
     glEnd();
     //Y axis in green
     glBegin(GL_LINES);
       glColor3f(0.0f,1.0f,0.0f);
       glVertex3f(0.0,Y_MIN,0.0);
       glColor3f(0.0f,1.0f,0.0f);
       glVertex3f(0.0,Y_MAX,0.0);
     glEnd();
     //Z axis in blue
     glBegin(GL_LINES);
       glColor3f(0.0f,0.0f,1.0f);
       glVertex3f(0.0,0.0,Z_MIN);
       glColor3f(0.0f,0.0f,1.0f);
       glVertex3f(0.0,0.0,Z_MAX);
     glEnd();
 }
*/
void init()
{

    glPolygonMode(GL_FRONT,GL_FILL);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);

    escena.init();

    glutIgnoreKeyRepeat(true);
}

void resize(int width, int height)
{
    WIDTH = width; HEIGHT = height;
    glViewport(0, 0, WIDTH, HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOVY,(float)WIDTH/HEIGHT,ZNEAR,ZFAR);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //drawAxis();
    //drawPlane();

    glPushMatrix();

    escena.display();

    glPopMatrix();

    glutSwapBuffers();

    //Sleep(10);
}

void SpecialInput(int key, int x, int y)
{
    escena.inputPressed(key,x,y);
}

void SpecialUpInput(int key, int x, int y)
{
    escena.inputReleased(key,x,y);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Proyecto final: Carro chocones");

    init();

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutSpecialFunc(SpecialInput);
    glutSpecialUpFunc(SpecialUpInput);

    glutMainLoop();

    return 0;
}
