#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <GL/glut.h>
#include <stdlib.h>

#define WIDTH 960
#define HEIGHT 480

float EYE_X=15.0;
float EYE_Y=15.0;
float EYE_Z=15.0;
float CENTER_X=0;
float CENTER_Y=0;
float CENTER_Z=0;
float UP_X=0;
float UP_Y=1;
float UP_Z=0;

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f,(float)WIDTH/HEIGHT,0.1f,50.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    gluLookAt(EYE_X,EYE_Y,EYE_Z,CENTER_X,CENTER_Y,CENTER_Z,UP_X,UP_Y,UP_Z);
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
    glPushMatrix();

    glPushMatrix();
    glScalef(scaleVar,scaleVar,scaleVar);
    glRotatef(120,0.0f,1.0f,0.0f);
    TheSun();
    glPopMatrix();
    Earth();

    glPopMatrix();

    glutSwapBuffers();
    update();
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
    glutMainLoop();

    return 0;
}
