#include "Carro.hpp"
#include <iostream>

int Carro::ID = 0;

Carro::Carro(float x, float y, float z, float dx, float dy, float dz, float step, float rot):
    tex(TEXTURE_LIMIT)
{
    MyID = ID++;

    radious = 1.0f;
    mass = 10.0f;

    posX = x;   posY = y;   posZ = z;
    dirX = dx;  dirY = dy;  dirZ = dz;
    velX = 0.0f; velZ = 0.0f;
    accX = 0.0f; accZ = 0.0f;
    s_magnitude = step;
    r_magnitude = rot;

    updateDirectionAngle();
}

Carro::Carro():
    tex(TEXTURE_LIMIT)
{
    MyID = ID++;

    radious = 1.0f;
    mass = 10.0f;

    posX = posY = posZ = 0;
    dirX = dirY = 0; dirZ = 1;
    velX = 0.0f; velZ = 0.0f;
    accX = 0.0f; accZ = 0.0f;
    s_magnitude = 1.0f;
    r_magnitude = 2.5f;

    updateDirectionAngle();
}

Carro::~Carro(){}

void Carro::initTextures()
{
    texFilename[0] = "res/default.bmp";
}

int Carro::getID(){return MyID;}

float Carro::getRadious(){return radious;}
void Carro::setRadious(float r){radious = r;}
float Carro::getMass(){return mass;}
void Carro::setMass(float m){mass = m;}

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
void Carro::setVelocity(float vx, float vz)
{
    velX = vx;  velZ = vz;
}
void Carro::setVelX(float vx){velX = vx;}
void Carro::setVelZ(float vz){velZ = vz;}
float Carro::getVelX(){return velX;}
float Carro::getVelZ(){return velZ;}
void Carro::setAcceleration(float ax, float az)
{
    accX = ax;  accZ = az;
}
void Carro::setAccX(float ax){accX = ax;}
void Carro::setAccZ(float az){accZ = az;}
float Carro::getAccX(){return accX;}
float Carro::getAccZ(){return accZ;}
void Carro::setStepMagnitude(float m){s_magnitude = m;}
float Carro::getStepMagnitude(){return s_magnitude;}
void Carro::setRotMagnitude(float m){r_magnitude = m;}
float Carro::getRotMagnitude(){return r_magnitude;}
float Carro::getDirection(){return direction;}

void Carro::accelerateForward()
{
    accX = 0.1 * s_magnitude * dirX;
    accZ = 0.1 * s_magnitude * dirZ;
}

void Carro::accelerateBackward()
{
    accX = - 0.1 * s_magnitude * dirX;
    accZ = - 0.1 * s_magnitude * dirZ;
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
