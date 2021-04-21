#ifndef PISO_HPP_INCLUDED
#define PISO_HPP_INCLUDED

#include "GL/glut.h"
#include "Texture.hpp"

#define FLOOR_RAD 75.0f

class Piso
{
    private:
        float x,y,z;
        float points[4][2];

        char* texFilename;
        Texture tex;
    public:
        Piso();
        ~Piso();

        float getX();
        float getY();
        float getZ();
        float getRadious();

        void draw();
};

#endif // PISO_HPP_INCLUDED
