#include "BoundingSphere.hpp"

BoundingSphere::BoundingSphere(float x, float y, float z, float radius)
{
    centerX = x; centerY = y; centerZ = z;
    this->radius = radius;
}

BoundingSphere::~BoundingSphere(){}

bool BoundingSphere::isColliding(BoundingSphere otherSphere)
{
    //Sum of both of the boundingSphere's radius
    float radiusDistance = this->radius + otherSphere.getRadius();

    //Distance between the two center points of the BoundingSphere's
    float distance = Util::pointDistance(centerX,centerY,centerZ,
                                         otherSphere.getCenterX(), otherSphere.getCenterY(), otherSphere.getCenterZ());

    //If the distance between the the center points of the BoundingSpheres minus the sum
    //of both of these BoundingSpheres's radius is less than 0 (or a predefined error margin)
    //then the BoundingSpheres are touching.
    if((distance - radiusDistance) <= ERROR_MARGIN)
        return true;
    return false;
}

void BoundingSphere::translateCenter(float tx, float ty, float tz)
{
    centerX += tx; centerY += ty; centerZ += tz;
}

void BoundingSphere::scaleRadius(float sf)
{
    radius *= sf;
}

float BoundingSphere::getCenterX(){return centerX;}
float BoundingSphere::getCenterY(){return centerY;}
float BoundingSphere::getCenterZ(){return centerZ;}
float BoundingSphere::getRadius(){return radius;}

void BoundingSphere::setCenterX(float x){centerX = x;}
void BoundingSphere::setCenterY(float y){centerY = y;}
void BoundingSphere::setCenterZ(float z){centerZ = z;}

void BoundingSphere::printValues()
{
    std::cout << "CENTER: " << centerX << " " << centerY << " " << centerZ <<
    " " << "RADIUS: " << radius << std::endl;
}
