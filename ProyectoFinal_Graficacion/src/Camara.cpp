#include "Camara.hpp"

Camara::Camara( float eyeX, float eyeY, float eyeZ,
                float dirX, float dirY, float dirZ,
                float upX, float upY, float upZ,
                float step, float rots)
{
    set(eyeX,eyeY,eyeZ,dirX,dirY,dirZ,upX,upY,upZ);
    s_magnitude = step;
    r_magnitude = rots;
}

Camara::Camara()
{
    set(0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,1.0f,0.0f);
    s_magnitude = r_magnitude = 1.0f;
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
    float rads = Util::degToRad(theta);
    //std::cout << theta << std::endl;

    //Directions must be included just in case one of them is (-1)
    dirX = cos(rads);
    dirZ = sin(rads);
    centerX = eyeX + dirX;
    centerZ = eyeZ + dirZ;
}

void Camara::set(float eyeX, float eyeY, float eyeZ,
                 float dirX, float dirY, float dirZ,
                 float upX, float upY, float upZ)
{
    this->eyeX = eyeX; this->eyeY = eyeY; this->eyeZ = eyeZ;
    this->dirX = dirX; this->dirY = dirY; this->dirZ = dirZ;
    centerX = eyeX + dirX; centerY = eyeY + dirY; centerZ = eyeZ + dirZ;
    this->upX = upX; this->upY = upY; this->upZ = upZ;

    theta = Util::getAngle(dirX,dirZ);
    //std::cout << theta << std::endl;
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

void Camara::setStepMagnitude(float m)
{
    s_magnitude = m;
}

void Camara::setRotMagnitude(float m)
{
    r_magnitude = m;
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

float Camara::getStepMagnitude(){return s_magnitude;}
float Camara::getRotMagnitude(){return r_magnitude;}

void Camara::moveForward()
{
    eyeX += (s_magnitude * dirX);
    eyeY += (s_magnitude * dirY);
    eyeZ += (s_magnitude * dirZ);
    updateCenter();
}

void Camara::moveBackward()
{
    eyeX -= (s_magnitude * dirX);
    eyeY -= (s_magnitude * dirY);
    eyeZ -= (s_magnitude * dirZ);
    updateCenter();
}

void Camara::moveLeft()
{
    theta -= r_magnitude;
    //std::cout << theta << std::endl;
    theta = (theta < 0.0f) ? theta+360.0f : theta;
    specialUpdateCenter();
}

void Camara::moveRight()
{
    theta += r_magnitude;
    //std::cout << theta << std::endl;
    theta = (theta >= 360.0f) ? theta-360.0f : theta;
    specialUpdateCenter();
}

void Camara::display()
{
    gluLookAt(eyeX,eyeY,eyeZ,centerX,centerY,centerZ,upX,upY,upZ);
}
