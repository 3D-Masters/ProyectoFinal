#ifndef BOUNDINGSPHERE_HPP
#define BOUNDINGSPHERE_HPP

#include "../util/Utilities.hpp"
#include <iostream>
#define ERROR_MARGIN 0.1

class BoundingSphere
{
    private:
        float centerX, centerY, centerZ;
        float radius;
    public:
        BoundingSphere(float, float, float, float);
        ~BoundingSphere();

        bool isColliding(BoundingSphere);
        void translateCenter(float, float, float);
        void scaleRadius(float);

        float getCenterX();
        float getCenterY();
        float getCenterZ();
        float getRadius();

        void setCenterX(float);
        void setCenterY(float);
        void setCenterZ(float);
        void printValues();
};

#endif // BOUNDINGSPHERE_HPP
