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

#define WIDTH 1280
#define HEIGHT 720
#include "src/Camara.hpp"

/*PRUEBA*/ #include "src/Model.hpp"
#include "src/Muro.hpp"
#include "src/BoundingSphere.hpp"

using namespace std;

//Variables para establecer los valores de gluPerspective
float FOVY=60.0;
float ZNEAR=0.01;
float ZFAR=150.0;

float EYE_X=0.0;
float EYE_Y=0.0;
float EYE_Z=-10.0;
float CENTER_X=0;
float CENTER_Y=0;
float CENTER_Z=0;
float UP_X=0;
float UP_Y=1;
float UP_Z=0;
//Direction vector
float DIR_X = 0.0f;
float DIR_Y = 0.0f;
float DIR_Z = 1.0f;
//Variables para dibujar los ejes del sistema
float X_MIN=-500;
float X_MAX=500;
float Y_MIN=-500;
float Y_MAX=500;
float Z_MIN=-500;
float Z_MAX=500;

ModelX mx; //modeloX
ModelX mx2;
ModelX mx3;
ModelX mx4;
ModelX mx5;
Muro muro;

bool arrows[] = {
    false,  // UP
    false,  // DOWN
    false,  // RIGHT
    false   // LEFT
};

Camara camara(EYE_X,EYE_Y,EYE_Z,
              DIR_X,DIR_Y,DIR_Z,
              UP_X,UP_Y,UP_Z,0.75f,1.5f);

//how do we update its variables like we did in Parcial2 in "aplicar"?
float x = 0, y = 0, z = 0;
BoundingSphere sunBoundingSphere(&x,&y,&z,2,BOUNDS_WALL,true);
BoundingSphere extBoundingSphere(&x,&y,&z,35,BOUNDS_WALL,false);
//BoundingSphere arr[] = {sunBoundingSphere,extBoundingSphere};
BoundingSphere arr[] = {sunBoundingSphere, muro.getBounds(), mx.getBounds(), mx2.getBounds(), mx3.getBounds(), mx4.getBounds(), mx5.getBounds()};
auto start = std::chrono::steady_clock::now();

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

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOVY,(float)WIDTH/HEIGHT,ZNEAR,ZFAR);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //texturas
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glShadeModel(GL_FLAT);

    glEnable(GL_DEPTH_TEST);
    mx.setDirectionVector(DIR_X,DIR_Y,DIR_Z);
    mx.setPositionPoint(EYE_X,EYE_Y,EYE_Z);

    mx2.setDirectionVector(DIR_X,DIR_Y,DIR_Z);
    mx2.setPositionPoint(30,0,0);

    mx3.setDirectionVector(DIR_X,DIR_Y,DIR_Z);
    mx3.setPositionPoint(-30,0,0);

    mx4.setDirectionVector(DIR_X,DIR_Y,DIR_Z);
    mx4.setPositionPoint(0,0,30);

    mx5.setDirectionVector(DIR_X,DIR_Y,DIR_Z);
    mx5.setPositionPoint(0,0,-30);

    camara.display();

    glutIgnoreKeyRepeat(true);
}

void SpecialInput(int key, int x, int y)
{
    switch(key){
        case GLUT_KEY_UP:
             arrows[0] = true;
             break;
        case GLUT_KEY_DOWN:
             arrows[1] = true;
             break;
        case GLUT_KEY_RIGHT:
             arrows[2] = true;
             break;
        case GLUT_KEY_LEFT:
             arrows[3] = true;
             break;
    }
    //std::cout << "yes" << std::endl;
}

void SpecialUpInput(int key, int x, int y)
{
    switch(key){
        case GLUT_KEY_UP:
             arrows[0] = false;
             break;
        case GLUT_KEY_DOWN:
             arrows[1] = false;
             break;
        case GLUT_KEY_RIGHT:
             arrows[2] = false;
             break;
        case GLUT_KEY_LEFT:
             arrows[3] = false;
             break;
    }
    //std::cout << "no" << std::endl;
}

void updateOthers()
{
    auto end = std::chrono::steady_clock::now();

    int elapsed_time = int(std::chrono::duration_cast <std::chrono::seconds>(end - start).count());
    float divisor =  1.0f; //std::rand() % 11;
    float a, b, c, d , e;

    //std::cout << elapsed_time << std::endl;

    if((elapsed_time % 2) == 0)
    {
        a = std::rand() % 2;
        b = std::rand() % 2;
        c = std::rand() % 2;
        d = std::rand() % 2;
        e = std::rand() % 2;

        a /= divisor;
        b /= divisor;
        c /= divisor;
        d /= divisor;
        e /= divisor;

        mx2.setDirectionVector(a,0,c);
        mx3.setDirectionVector(b,0,d);
        mx4.setDirectionVector(c,0,e);
        mx5.setDirectionVector(d,0,a);

        mx2.moveBackward();
        mx3.moveBackward();
        mx4.moveBackward();
        mx5.moveBackward();
    }
    else
    {
        mx2.moveForward();
        mx3.moveForward();
        mx4.moveForward();
        mx5.moveForward();
    }
}

void updateMovement()
{
    if(arrows[0])   // UP
    {
       mx.moveForward();
    }

    if(arrows[1])   // DOWN
    {
        mx.moveBackward();
    }
    if(arrows[2])   // RIGTH
        mx.moveRight();
    if(arrows[3])   // LEFT
        mx.moveLeft();

    // chequeo de colisiones XD
    mx.handleCollisions(arr,7);
    mx2.handleCollisions(arr,7);
    mx3.handleCollisions(arr,7);
    mx4.handleCollisions(arr,7);
    mx5.handleCollisions(arr,7);


    glLoadIdentity();
    camara.set(
        mx.getPosX(),
        mx.getPosY()+0.75f,
        mx.getPosZ(),
        mx.getDirX(),
        mx.getDirY()-0.10,
        mx.getDirZ(),
        0.0f,1.0f,0.0f
    );
    camara.moveBackward();
    camara.moveBackward();
    camara.moveBackward();
    camara.display();
}



void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    updateMovement();   // Se realiza aquí para que reaccione al instante en la escena.
    updateOthers(); // "AI" for cars xd

    drawAxis();

    glPushMatrix();
    glScalef(70.0f,70.f,70.0f);
    drawPlane();
    glPopMatrix();

    glPushMatrix();

    glPushMatrix();

    glPushMatrix();

    glRotatef(90,1,0,0);
    glutWireSphere(35,10,10);
    glutWireSphere(2,10,10);

    glPopMatrix();

    mx.draw();
    mx2.draw();
    mx3.draw();
    mx4.draw();
    mx5.draw();
    muro.draw();

    glPopMatrix();


    glPopMatrix();

    glutSwapBuffers();


    //mx.update();
    Sleep(10);
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("Solar System");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutSpecialFunc(SpecialInput);
    glutSpecialUpFunc(SpecialUpInput);
    glutMainLoop();

    return 0;
}
