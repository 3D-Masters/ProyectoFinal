#ifndef BOUNDINGSPHERE_HPP
#define BOUNDINGSPHERE_HPP

#include "../util/Utilities.hpp"
#include <iostream>
#define ERROR_MARGIN 0.0

#define BOUNDS_NONE 0
#define BOUNDS_WALL 1
#define BOUNDS_KART 2

class BoundingSphere
{
    private:
        float *centerX, *centerY, *centerZ;
        int type;
        float radius;
        bool inner;
    public:
        BoundingSphere(float*, float*, float*, float, int, bool);
        ~BoundingSphere();

        int isColliding(BoundingSphere);
        static bool isNone(int);
        static bool isWall(int);
        static bool isKart(int);

        float getCenterX();
        float getCenterY();
        float getCenterZ();
        float getRadius();
        int getType();
        bool getInnerValue();

        /*
        void setCenterX(float);
        void setCenterY(float);
        void setCenterZ(float);
        */
        void setRadius(float);
        void setType(int);
        void setInnerValue(bool);

        void printValues();
};

#endif // BOUNDINGSPHERE_HPP
