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
BoundingSphere arr[] = {sunBoundingSphere,muro.getBounds()};

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

void updateMovement()
{
    if(arrows[0])   // UP
        mx.moveForward();
    if(arrows[1])   // DOWN
        mx.moveBackward();
    if(arrows[2])   // RIGTH
        mx.moveRight();
    if(arrows[3])   // LEFT
        mx.moveLeft();

    // chequeo de colisiones XD
    mx.handleCollisions(arr,2);

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

float anguloSun = 0.0f;
float anguloEarth = 0.0f;
float anguloMoon = 0.0f;
float scaleStep = 0.001f;
float scaleVar = 1.0f;

void TheSun()
{
    glColor3f(1.0f,0.6f,0.0f);
    for(int i = 0; i < 8; i++)
    {
        glPushMatrix();

        glRotatef(anguloSun,0.0f,1.0f,0.0f);
        glRotatef((float)(i*45),1.0f,0.0f,0.0f);
        glutWireCone(1.0f,2.0f,10,10);

        glPopMatrix();
    }
}

void Moon()
{
    glColor3f(1.0f,1.0f,1.0f);
    glPushMatrix();

    glRotatef(anguloMoon,0.0,1.0,0.0);
    glTranslatef(2.0f,0.0f,0.0f);
    glutWireSphere(0.5,10,10);


    glPopMatrix();
}

void Earth()
{
    glColor3f(0.5f,0.7f,1.0f);
    glPushMatrix();

    glRotatef(anguloEarth,0.0,1.0,0.0);
    glTranslatef(5.0f,0.0f,0.0f);
    glutWireSphere(1.0,12,12);
    Moon();

    glPushMatrix();
    glRotatef(90.0f,0.0f,0.0f,1.0f);
    Moon();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90.0f,0.0f,1.0f,0.0f);
    Moon();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90.0f,1.0f,0.0f,0.0f);
    Moon();
    glPopMatrix();


    glPopMatrix();
}

void updateScaleStep()
{
    if(scaleVar >= 3.0f || scaleVar < 1.0f)
        scaleStep *= -1;
    scaleVar += scaleStep;

}

void update()
{
    anguloSun += 0.01f;
    anguloEarth += 0.05f;
    anguloMoon += 0.2f;
    updateScaleStep();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    updateMovement();   // Se realiza aquí para que reaccione al instante en la escena.

    drawAxis();

    glPushMatrix();

    glPushMatrix();

    glPushMatrix();

    glRotatef(90,1,0,0);
    glutWireSphere(35,10,10);
    glutWireSphere(2,10,10);

    glPopMatrix();

    mx.draw();
    muro.draw();
    //glScalef(scaleVar,scaleVar,scaleVar);
    //glRotatef(120,0.0f,1.0f,0.0f);
    //TheSun();
    glPopMatrix();
    //Earth();

    glPopMatrix();

    glutSwapBuffers();

    update();
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
