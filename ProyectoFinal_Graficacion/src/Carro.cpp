#include "Carro.hpp"

Carro::Carro(float x, float y, float z, float dx, float dy, float dz, float m)
{
    posX = x;       posY = y;       posZ = z;
    dirX = dx;      dirY = dy;      dirZ = dz;
    forX = x+dx;    forY = y+dy;    forZ = z+dz;
    magnitude = m;
    // ...
}

Carro::Carro()
{
    posX = posY = posZ = 0;
    dirX = dirY = dirZ = 0;
    forX = forY = forZ = 0;
    magnitude = 1;
}

Carro::~Carro(){}

void Carro::updateForward(){
    forX = posX+dirX;
    forY = posY+dirY;
    forZ = posZ+dirZ;
}

void Carro::setPosition(float x, float y, float z)
{
    posX = x;   posY = y;   posZ = z;
    updateForward();
}
void Carro::setPosX(float x){posX = x; updateForward();}
void Carro::setPosY(float y){posY = y; updateForward();}
void Carro::setPosZ(float z){posZ = z; updateForward();}
float Carro::getPosX(){return posX;}
float Carro::getPosY(){return posY;}
float Carro::getPosZ(){return posZ;}
void Carro::setDirection(float dx, float dy, float dz)
{
    dirX = dx;  dirY = dy;  dirZ = dz;
    updateForward();
}
void Carro::setDirX(float dx){dirX = dx; updateForward();}
void Carro::setDirY(float dy){dirY = dy; updateForward();}
void Carro::setDirZ(float dz){dirZ = dz; updateForward();}
float Carro::getDirX(){return dirX;}
float Carro::getDirY(){return dirY;}
float Carro::getDirZ(){return dirZ;}
void Carro::setDirMagnitude(float m){magnitude = m;}
float Carro::getDirMagnitude(){return magnitude;}
