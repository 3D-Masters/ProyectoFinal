#include "Carro.hpp"
#include <iostream>

Carro::Carro(float x, float y, float z, float dx, float dy, float dz, float step, float rot)
{
    posX = x;   posY = y;   posZ = z;
    dirX = dx;  dirY = dy;  dirZ = dz;
    s_magnitude = step;
    r_magnitude = rot;

    updateDirectionAngle();

    // ...
}

Carro::Carro()
{
    posX = posY = posZ = 0;
    dirX = dirY = 0; dirZ = 1;
    s_magnitude = 1.0f;
    r_magnitude = 2.5f;

    updateDirectionAngle();
}

Carro::~Carro(){}

void Carro::setPositionPoint(float x, float y, float z)
{
    posX = x;   posY = y;   posZ = z;
}
void Carro::setPosX(float x){posX = x;}
void Carro::setPosY(float y){posY = y;}
void Carro::setPosZ(float z){posZ = z;}
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

void Carro::moveForward()
{
    posX += (s_magnitude * dirX);
    posY += (s_magnitude * dirY);
    posZ += (s_magnitude * dirZ);
}

void Carro::moveBackward()
{
    posX -= (s_magnitude * dirX);
    posY -= (s_magnitude * dirY);
    posZ -= (s_magnitude * dirZ);
}

void Carro::moveLeft()
{
    direction -= r_magnitude;
    direction = (direction < 0.0f) ? direction+360.0f : direction;
    updateDirection();
}

void Carro::moveRight()
{
    direction += r_magnitude;
    direction = (direction >= 360.0f) ? direction-360.0f : direction;
    updateDirection();
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
