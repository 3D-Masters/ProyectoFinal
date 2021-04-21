#include "Piso.hpp"

Piso::Piso(): tex(1)
{
    x = y = z = 0.0f;

    texFilename = "res/floor.bmp";

    points[0][0] =  FLOOR_RAD; points[0][1] =  FLOOR_RAD;
    points[1][0] =  FLOOR_RAD; points[1][1] = -FLOOR_RAD;
    points[2][0] = -FLOOR_RAD; points[2][1] = -FLOOR_RAD;
    points[3][0] = -FLOOR_RAD; points[3][1] =  FLOOR_RAD;
}

Piso::~Piso(){}

float Piso::getX(){return x;}
float Piso::getY(){return y;}
float Piso::getZ(){return z;}
float Piso::getRadious(){ return FLOOR_RAD; }

void Piso::draw()
{
    tex.loadTexture(texFilename);

    glEnable(GL_TEXTURE_2D);
    //tex.Bind(1);
    glPushMatrix();

    glTranslatef(x,y,z);

    glBegin(GL_QUADS);
        glTexCoord2f(30,0);
        glVertex3f(points[0][0],y,points[0][1]);
        glTexCoord2f(30,30);
        glVertex3f(points[1][0],y,points[1][1]);
        glTexCoord2f(0,30);
        glVertex3f(points[2][0],y,points[2][1]);
        glTexCoord2f(0,0);
        glVertex3f(points[3][0],y,points[3][1]);
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
