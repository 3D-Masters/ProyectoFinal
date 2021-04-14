#include "BoundingSphere.hpp"

BoundingSphere::BoundingSphere(float* x, float* y, float* z, float radius, int type)
{
    centerX = x; centerY = y; centerZ = z;
    this->radius = radius;
    this->type= type;
}

BoundingSphere::~BoundingSphere(){}

int BoundingSphere::isColliding(BoundingSphere otherSphere)
{
    //Sum of both of the boundingSphere's radius
    float radiusDistance = this->radius + otherSphere.getRadius();

    //Distance between the two center points of the BoundingSphere's
    float distance = Util::pointDistance(*centerX,*centerY,*centerZ,
                                         otherSphere.getCenterX(), otherSphere.getCenterY(), otherSphere.getCenterZ());

    //If the distance between the the center points of the BoundingSpheres minus the sum
    //of both of these BoundingSpheres's radius is less than 0 (or a predefined error margin)
    //then the BoundingSpheres are touching.
    if((distance - radiusDistance) <= ERROR_MARGIN)
        return otherSphere.getType();
    return BOUNDS_NONE;
}

bool BoundingSphere::isNone(int type)
{
    return type == BOUNDS_NONE;
}

bool BoundingSphere::isWall(int type)
{
    return type == BOUNDS_WALL;
}

bool BoundingSphere::isKart(int type)
{
    return type == BOUNDS_KART;
}

void BoundingSphere::setRadius(float sf)
{
    radius = sf;
}

void BoundingSphere::setType(int ty)
{
    type = ty;
}

float BoundingSphere::getCenterX(){return *centerX;}
float BoundingSphere::getCenterY(){return *centerY;}
float BoundingSphere::getCenterZ(){return *centerZ;}
float BoundingSphere::getRadius(){return radius;}
int BoundingSphere::getType(){return type;}
/*
void BoundingSphere::setCenterX(float x){centerX = x;}
void BoundingSphere::setCenterY(float y){centerY = y;}
void BoundingSphere::setCenterZ(float z){centerZ = z;}
*/
void BoundingSphere::printValues()
{
    std::cout << "CENTER: " << centerX << " " << centerY << " " << centerZ <<
    " " << "RADIUS: " << radius << std::endl;
}
