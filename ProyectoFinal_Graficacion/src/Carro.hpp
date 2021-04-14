#ifndef CARRO_HPP_INCLUDED
#define CARRO_HPP_INCLUDED

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../util/Utilities.hpp"
#include "BoundingSphere.hpp"

class Carro
{
    protected:
        float posX,posY,posZ;   // pos = position
        float dirX,dirY,dirZ;   // dir = direction
        float tX,tY,tZ;         // temporal position
        float direction;        // angle of direction
        float s_magnitude;      // step magnitude
        float r_magnitude;      // rotation magnitude

        BoundingSphere *boundingSphere;//The objects bounding sphere---UPDATE TO INCLUDE IN CONSTRUCTOR
        // Maybe is missing a collision variable or something... even textures!
        // ...
        void updateDirectionAngle();
        void updateDirection();
    public:
        Carro(float,float,float,float,float,float,float,float);
        Carro();
        ~Carro();

        void setPositionPoint(float,float,float);
        void setPosX(float);
        void setPosY(float);
        void setPosZ(float);
        float getPosX();
        float getPosY();
        float getPosZ();
        void setDirectionVector(float,float,float);
        void setDirX(float);
        void setDirY(float);
        void setDirZ(float);
        float getDirX();
        float getDirY();
        float getDirZ();
        void setStepMagnitude(float);
        float getStepMagnitude();
        void setRotMagnitude(float);
        float getRotMagnitude();
        float getDirection();

        // This function handles what will happend in case there is
        // a collition detected
        void handleCollisions(BoundingSphere*,int);

        virtual void draw() = 0;        // Función específica para dibujarlo
        virtual void update() = 0;      // Esto es específico para las animaciones que tenga.
        virtual void moveForward();     // Función especial para mover al objeto
        virtual void moveBackward();    // Función especial para mover al objeto
        virtual void moveRight();       // Función especial para mover al objeto
        virtual void moveLeft();        // Función especial para mover al objeto
        virtual void moveRewind();      // Función especial para rebobinar movimiento

        // Maybe some "actions", for instante, "explode" or something XD
};

#endif // CARRO_HPP_INCLUDED
