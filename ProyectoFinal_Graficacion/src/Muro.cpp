#include "Muro.hpp"
#include <iostream>

Muro::Muro(): tex(1)
{
    float step = (float) 360.0f / (float) WALL_RES;
    x = y = z = 0.0f;

    texFilename = "res/wall.bmp";

    for(int i = 0; i < WALL_RES; i++)
    {
        points[i][0] = (float)WALL_RAD*cos(Util::degToRad(step*i));
        points[i][1] = (float)WALL_RAD*sin(Util::degToRad(step*i));
        //std::cout << points[i][0] << " " << points[i][1] << std::endl;
    }
}

Muro::~Muro(){}

float Muro::getX(){return x;}
float Muro::getY(){return y;}
float Muro::getZ(){return z;}
float Muro::getRadious(){ return WALL_RAD; }

void Muro::draw()
{
    float delta = (float) WALL_TIMES / (float) WALL_RES;
    tex.loadTexture(texFilename,0);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(x,0.0f,z);
    glBegin(GL_QUAD_STRIP);
        for(int i = 0; i <= WALL_RES; i++)
        {
            glTexCoord2f(delta*i,1.0f);
            glVertex3f(points[i%WALL_RES][0],WALL_HEIGHT,points[i%WALL_RES][1]);
            glTexCoord2f(delta*i,0.0f);
            glVertex3f(points[i%WALL_RES][0], 0.0f      ,points[i%WALL_RES][1]);
        }
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
