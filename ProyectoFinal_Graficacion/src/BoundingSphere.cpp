#include "BoundingSphere.hpp"
int BoundingSphere::ID = 0;
BoundingSphere::BoundingSphere(float* x, float* y, float* z, float radius, int type, bool inner)
{
    centerX = x; centerY = y; centerZ = z;
    this->radius = radius;
    this->type = type;
    this->inner = inner;
    myID = ID;
    ID++;
}

int BoundingSphere::getMyID(){return myID;}
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
    if(otherSphere.getInnerValue())
    {
        if((distance - radiusDistance) <= ERROR_MARGIN)
            return otherSphere.getType();
        return BOUNDS_NONE;
    }
    else
    {
        if((distance + radius - otherSphere.getRadius()) <= -ERROR_MARGIN)
            return BOUNDS_NONE;
        return otherSphere.getType();
    }
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

void BoundingSphere::setInnerValue(bool inn)
{
    inner = inn;
}

float BoundingSphere::getCenterX(){return *centerX;}
float BoundingSphere::getCenterY(){return *centerY;}
float BoundingSphere::getCenterZ(){return *centerZ;}
float BoundingSphere::getRadius(){return radius;}
int BoundingSphere::getType(){return type;}
bool BoundingSphere::getInnerValue(){return inner;}
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
