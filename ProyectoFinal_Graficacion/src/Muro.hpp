#ifndef MURO_HPP_INCLUDED
#define MURO_HPP_INCLUDED

#include "GL/glut.h"
#include "Texture.hpp"
#include "../util/Utilities.hpp"
#include <cmath>

#define WALL_RES 32
#define WALL_HEIGHT 6.5f
#define WALL_RAD 50.0f
#define WALL_TIMES 3

class Muro
{
    private:
        float x,y,z;
        float points[WALL_RES][2];

        char* texFilename;
        Texture tex;
    public:
        Muro();
        ~Muro();

        float getX();
        float getY();
        float getZ();
        float getRadious();

        void draw();
};

#endif // MURO_HPP_INCLUDED
