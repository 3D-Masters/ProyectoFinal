#include "Carro.hpp"
#include <iostream>

Carro::Carro(float x, float y, float z, float dx, float dy, float dz, float step, float rot)
{
    posX = x;   posY = y;   posZ = z;
    dirX = dx;  dirY = dy;  dirZ = dz;
    tX = x;   tY = y;   tZ = z;
    s_magnitude = step;
    r_magnitude = rot;

    updateDirectionAngle();

    boundingSphere = new BoundingSphere(&posX,&posY,&posZ,0.5,BOUNDS_KART,true);

    // ...
}

Carro::Carro()
{
    posX = posY = posZ = 0;
    dirX = dirY = 0; dirZ = 1;
    s_magnitude = 1.0f;
    r_magnitude = 2.5f;

    updateDirectionAngle();

    boundingSphere = new BoundingSphere(&posX,&posY,&posZ,1.1,BOUNDS_KART,true);
}

Carro::~Carro()
{
    delete boundingSphere;
}

void Carro::setPositionPoint(float x, float y, float z)
{
    posX = x;   posY = y;   posZ = z;
    tX = x;   tY = y;   tZ = z;
}
void Carro::setPosX(float x){posX = x; tX = x;}
void Carro::setPosY(float y){posY = y; tY = y;}
void Carro::setPosZ(float z){posZ = z; tZ = z;}
float Carro::getPosX(){return posX;}
float Carro::getPosY(){return posY;}
float Carro::getPosZ(){return posZ;}
void Carro::setDirectionVector(float dx, float dy, float dz)
{
    dirX = dx;  dirY = dy;  dirZ = dz;
    updateDirectionAngle();
    updateDirection();
}
void Carro::setDirX(float dx){dirX = dx; updateDirectionAngle(); updateDirection();}
void Carro::setDirY(float dy){dirY = dy; updateDirectionAngle(); updateDirection();}
void Carro::setDirZ(float dz){dirZ = dz; updateDirectionAngle(); updateDirection();}
float Carro::getDirX(){return dirX;}
float Carro::getDirY(){return dirY;}
float Carro::getDirZ(){return dirZ;}
void Carro::setStepMagnitude(float m){s_magnitude = m;}
float Carro::getStepMagnitude(){return s_magnitude;}
void Carro::setRotMagnitude(float m){r_magnitude = m;}
float Carro::getRotMagnitude(){return r_magnitude;}
float Carro::getDirection(){return direction;}

void Carro::handleCollisions(BoundingSphere* spheres, int sizeN)
{
    int value;

    for(int i = 0; i < sizeN; i++)
    {
        value = boundingSphere->isColliding(spheres[i]);
        if(BoundingSphere::isWall(value))
        {
            moveRewind();
            std::cout << "Collision with Wall" << std::endl;
        }
        else if(BoundingSphere::isKart(value))
        {
            // rotar, mover, explotar
            std::cout << "Collision with Kart" << std::endl;
        }
    }
}

//The following should only be executed if isColliding is false
//if(!isColliding)
void Carro::moveForward()
{
    tX = posX; tY = posY; tZ = posZ;

    posX += (s_magnitude * dirX);
    posY += (s_magnitude * dirY);
    posZ += (s_magnitude * dirZ);
}

void Carro::moveBackward()
{
    tX = posX; tY = posY; tZ = posZ;

    posX -= (s_magnitude * dirX);
    posY -= (s_magnitude * dirY);
    posZ -= (s_magnitude * dirZ);
}

void Carro::moveRight()
{
    direction += r_magnitude;
    direction = (direction >= 360.0f) ? direction-360.0f : direction;
    updateDirection();
}

void Carro::moveLeft()
{
    direction -= r_magnitude;
    direction = (direction < 0.0f) ? direction+360.0f : direction;
    updateDirection();
}

void Carro::moveRewind()
{
    posX = tX; posY = tY; posZ = tZ;
}

void Carro::updateDirection()
{
    float rads = Util::degToRad(direction);

    //std::cout << direction << std::endl;

    dirX = cos(rads);
    dirZ = sin(rads);
}

void Carro::updateDirectionAngle()
{
    direction = Util::getAngle(dirX,dirZ);
}
