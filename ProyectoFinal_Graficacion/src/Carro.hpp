#ifndef CARRO_HPP_INCLUDED
#define CARRO_HPP_INCLUDED

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Carro
{
    private:
        float posX,posY,posZ;   // pos = position
        float dirX,dirY,dirZ;   // dir = direction
        float forX,forY,forZ;   // for = forward. But (forward != next step), generally
        float magnitude;        // direction magnitude
        // Maybe is missing a collision variable or something... even textures!
        // ...

        void updateForward();

    public:
        Carro(float,float,float,float,float,float,float);
        Carro();
        ~Carro();
        
        void setPosition(float,float,float);
        void setPosX(float);
        void setPosY(float);
        void setPosZ(float);
        float getPosX();
        float getPosY();
        float getPosZ();
        void setDirection(float,float,float);
        void setDirX(float);
        void setDirY(float);
        void setDirZ(float);
        float getDirX();
        float getDirY();
        float getDirZ();
        void setDirMagnitude(float);
        float getDirMagnitude();
        
        virtual void draw() = 0;            // Función específica para dibujarlo
        virtual void update() = 0;          // Esto es específico para las animaciones que tenga.
        virtual void move(int,int,int) = 0; // Función especial para mover al objeto

        // Maybe some "actions", for instante, "explode" or something XD
};

#endif // CARRO_HPP_INCLUDED