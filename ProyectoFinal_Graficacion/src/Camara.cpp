#include "Camara.hpp"

Camara::Camara( float eyeX, float eyeY, float eyeZ,
                float centerX, float centerY, float centerZ,
                float dirX, float dirY, float dirZ,
                float m)
{
    this->eyeX = eyeX; this->eyeY = eyeY; this->eyeZ = eyeZ;
    this->centerX = centerX; this->centerY = centerY; this->centerZ = centerZ;
    this->dirX = dirX; this->dirY = dirY; this->dirZ = dirZ;
    upX = 0.0f; upY = 1.0f; upZ = 0.0f;
    magnitude = m;
    theta = 0.0f;
}

Camara::Camara()
{
    eyeX = eyeY = eyeZ = 0.0f;
    centerX = centerY = centerZ = 0.0f;
    dirX = dirY = dirZ = 0.0f;
    upX = 0.0f; upY = 1.0f; upZ = 0.0f;
    /*
    dirX = 1.0f;
    dirY = dirZ = 0.0f
    */
    magnitude = 1.0f;
    theta = 0.0f;
}

Camara::~Camara(){}

//intuitive formula as seen in class
void Camara::updateCenter()
{
    centerX = eyeX + dirX;
    centerY = eyeY + dirY;
    centerZ = eyeZ + dirZ;
}

void Camara::specialUpdateCenter()
{
    theta = degToRad(theta);


    //Directions must be included just in case one of them is (-1)

    dirX = (std::cos(theta) * dirX) + (std::sin(theta) * dirZ);
    dirZ = (std::sin(theta) * dirX) + (std::cos(theta) * dirZ);
    centerX = eyeX + dirX;
    centerZ = eyeZ + dirZ;


    /*
    dirX = cos(theta);
    dirZ = sin(theta);
    centerX = eyeX + dirX;
    centerZ = eyeZ + dirZ;
    */
}

float Camara::degToRad(float degrees)
{
      return ((degrees*PI_)/180.0f);
}

/*
I think that the center has to update every time we
update the eye, but just for the specified axis.
*/

void Camara::setEyeX(float eyeX)
{
    this->eyeX = eyeX;
    centerX = eyeX + dirX;
}

void Camara::setEyeY(float eyeY)
{
    this->eyeY = eyeY;
    centerY = eyeY + dirY;
}

void Camara::setEyeZ(float eyeZ)
{
    this->eyeZ = eyeZ;
    centerY = eyeZ + dirZ;
}

void Camara::setEye(float eyeX, float eyeY, float eyeZ)
{
    this->eyeX = eyeX; this->eyeY = eyeY; this->eyeZ = eyeZ;
    updateCenter();
}


/*
If the center (observation point) is changed, then the
direction must also change so the camera can move towards
its direction.
*************Scratch this, I don't think this has to be
implemented xd

void Camara::setCenterX(float centerX)
{
    this->centerX = centerX;
    //update dir
}

void Camara::setCenterY(float centerY)
{
    this->centerY = centerY;
}

void Camara::setCenterZ(float centerY)
{
    this->centerZ = centerZ;
}

void Camara::setCenter(float CenterX, float centerY, float centerZ){}
*/

/*
If the direction is updated, then the center must also be updated to make
it look like we're heading towards that specific direction. I think that
the center must only be updated to the specified axis.
*/
void Camara::setDirX(float dirX)
{
    this->dirX = dirX;
    centerX = eyeX + dirX;
}

void Camara::setDirY(float dirY)
{
    this->dirY = dirY;
    centerY = eyeY + dirY;
}

void Camara::setDirZ(float dirZ)
{
    this->dirZ = dirZ;
    centerZ = eyeZ + dirZ;
}

void Camara::setDir(float dirX, float dirY, float dirZ)
{
    this->dirX = dirX; this->dirY = dirY; this->dirZ = dirZ;
    updateCenter();
}

void Camara::setMagnitude(float m)
{
    magnitude = m;
}

float Camara::getEyeX(){return eyeX;}
float Camara::getEyeY(){return eyeY;}
float Camara::getEyeZ(){return eyeZ;}

float Camara::getCenterX(){return centerX;}
float Camara::getCenterY(){return centerY;}
float Camara::getCenterZ(){return centerZ;}

float Camara::getDirX(){return dirX;}
float Camara::getDirY(){return dirY;}
float Camara::getDirZ(){return dirZ;}

float Camara::getMagnitude(){return magnitude;}

void Camara::moveForward()
{
    eyeX += (magnitude * dirX);
    eyeY += (magnitude * dirY);
    eyeZ += (magnitude * dirZ);
    updateCenter();
}

void Camara::moveBackward()
{
    eyeX -= (magnitude * dirX);
    eyeY -= (magnitude * dirY);
    eyeZ -= (magnitude * dirZ);
    updateCenter();
}

void Camara::moveLeft()
{
    theta -= 1.0f;
    theta = (theta < 0.0) ? 359.0 : theta;
    specialUpdateCenter();
}


void Camara::moveRight()
{
    theta += 1.0f;
    theta = (theta > 359.0) ? 0.0 : theta;
    specialUpdateCenter();
}


void Camara::colocar()
{
    glLoadIdentity();//should this be here?
    gluLookAt(eyeX,eyeY,eyeZ,centerX,centerY,centerZ,upX,upY,upZ);
    glutPostRedisplay();//should this be here?
}
