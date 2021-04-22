#include "Piso.hpp"

Piso::Piso()
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
    glPushMatrix();

    glTranslatef(x,y,z);

    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);
        tex.bind();
        glTexCoord2f(FLOOR_REPEAT,0);
        glVertex3f(points[0][0],y,points[0][1]);
        glTexCoord2f(FLOOR_REPEAT,FLOOR_REPEAT);
        glVertex3f(points[1][0],y,points[1][1]);
        glTexCoord2f(0,FLOOR_REPEAT);
        glVertex3f(points[2][0],y,points[2][1]);
        glTexCoord2f(0,0);
        glVertex3f(points[3][0],y,points[3][1]);
        tex.unbind();
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
