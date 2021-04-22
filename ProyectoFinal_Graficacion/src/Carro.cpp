#include "Carro.hpp"
#include <iostream>

int Carro::ID = 0;
std::chrono::steady_clock::time_point Carro::start = std::chrono::steady_clock::now();

Carro::Carro(float x, float y, float z, float dx, float dy, float dz, float step, float rot)
{
    MyID = ID++;

    radious = 1.0f;
    mass = 10.0f;

    posX = x;   posY = y;   posZ = z;
    dirX = dx;  dirY = dy;  dirZ = dz;
    velX = 0.0f; velZ = 0.0f;
    accX = 0.0f; accZ = 0.0f;
    s_magnitude = step;
    r_magnitude = rot;

    updateDirectionAngle();
}

Carro::Carro()
{
    MyID = ID++;

    radious = 1.0f;
    mass = 10.0f;

    posX = posZ = 0;
    posY = 0.5;
    dirX = dirY = 0; dirZ = 1;
    velX = 0.0f; velZ = 0.0f;
    accX = 0.0f; accZ = 0.0f;
    s_magnitude = 1.0f;
    r_magnitude = 2.5f;

    updateDirectionAngle();
}

Carro::~Carro(){}

void Carro::initTextures()
{
    texFilename[0] = "res/default.bmp";
}

void Carro::drawUp()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);

    //front
        tex.bind();
        glNormal3f(0.0f,0.0f,1.0f);

        glTexCoord2f(0.0f,0.0f);
        glVertex3f(-0.5,0.15,1.0);

        glTexCoord2f(1.0f,0.0f);
        glVertex3f(0.5,0.15,1.0);

        glTexCoord2f(1.0f,1.0f);
        glVertex3f(0.3,0.45,0.7);

        glTexCoord2f(0.0f,1.0f);
        glVertex3f(-0.3,0.45,0.7);

    //Left
        glNormal3f(1.0f,0.0f,0.0f);

        glTexCoord2f(0.0f,0.0f);
        glVertex3f(0.5,0.15,1.0);

        glTexCoord2f(1.0f,0.0f);
        glVertex3f(0.5,0.15,-1.0);

        glTexCoord2f(1.0f,1.0f);
        glVertex3f(0.3,0.45,-0.7);

        glTexCoord2f(0.0f,1.0f);
        glVertex3f(0.3,0.45,0.7);
    //Right
        glNormal3f(-1.0f,0.0f,0.0f);

        glTexCoord2f(0.0,0.0);
        glVertex3f(-0.5f,0.15f,-1.0f);

        glTexCoord2f(1.0f,0.0f);
        glVertex3f(-0.5f,0.15f,1.0f);

        glTexCoord2f(1.0f,1.0f);
        glVertex3f(-0.3f,0.45f,0.7);

        glTexCoord2f(0.0f,1.0f);
        glVertex3f(-0.3f,0.45f,-0.7f);

    //back
        glNormal3f(0.0f,0.0f,-1.0f);

        glTexCoord2f(0.0f,0.0f);
        glVertex3f(0.5f,0.15f,-1.0);

        glTexCoord2f(1.0f,0.0f);
        glVertex3f(-0.5f,0.15f,-1.0f);

        glTexCoord2f(1.0f,1.0f);
        glVertex3f(-0.3,0.45f,-0.7);

        glTexCoord2f(0.0f,1.0f);
        glVertex3f(0.3f,0.45f,-0.7);

    //top
        glNormal3f(0.0f,1.0f,0.0f);

        glTexCoord2f(0.0f,0.0f);
        glVertex3f(-0.3f,0.45f,0.7f);

        glTexCoord2f(1.0f,0.0f);
        glVertex3f(0.3f,0.45f,0.7f);

        glTexCoord2f(1.0f,1.0f);
        glVertex3f(0.3f,0.45f,-0.7f);

        glTexCoord2f(0.0f,1.0f);
        glVertex3f(-0.3f,0.45f,-0.7f);
        tex.unbind();
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void Carro::drawBase()
{
    //Activando las texturas
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);

    //front
        tex.bind();
        glNormal3f(0.0f, 0.0f, 1.0f);

        glTexCoord2f(0.5f,1.0f);
        glVertex3f(-0.5f, -0.15f, 1.0f);

        glTexCoord2f(0.75f,1.0f);
        glVertex3f(0.5f, -0.15f, 1.0f);

        glTexCoord2f(0.75f,0.0f);
        glVertex3f(0.5f, 0.15f, 1.0f);

        glTexCoord2f(0.5f,0.0f);
        glVertex3f(-0.5f, 0.15f, 1.0f);

	//Left
        glNormal3f(1.0f, 0.0f, 0.0f);

        glTexCoord2f(0.75f,0.0f);
        glVertex3f(0.5f, -0.15f, 1.0f);

        glTexCoord2f(1.0f,0.0f);
        glVertex3f(0.5f, -0.15f, -1.0f);

        glTexCoord2f(1.0f,1.0f);
        glVertex3f(0.5f, 0.15f, -1.0f);

        glTexCoord2f(0.75f,1.0f);
        glVertex3f(0.5f, 0.15f, 1.0f);

	//Back
        glNormal3f(-1.0f, 0.0f, 0.0f);

        glTexCoord2f(0.0f,0.0f);
        glVertex3f(0.5f, -0.15f, -1.0f);

        glTexCoord2f(0.25f,0.0f);
        glVertex3f(-0.5f, -0.15f, -1.0f);

        glTexCoord2f(0.25f,1.0f);
        glVertex3f(-0.5f, 0.15f, -1.0f);

        glTexCoord2f(0.0f,1.0f);
        glVertex3f(0.5f, 0.15f, -1.0f);

	//Right
        glNormal3f(0.0f, 0.0f, -1.0f);

        glTexCoord2f(0.5f,1.0f);
        glVertex3f(-0.5f, 0.15f, 1.0f);

        glTexCoord2f(0.25f,1.0f);
        glVertex3f(-0.5f, 0.15f, -1.0f);

        glTexCoord2f(0.25f,0.0f);
        glVertex3f(-0.5f, -0.15f, -1.0f);

        glTexCoord2f(0.5f,0.0f);
        glVertex3f(-0.5f, -0.15f, 1.0f);
        tex.unbind();
	glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

}

void Carro::drawBottom()
{
    glPushMatrix();
    glColor3f(1.0f,1.0f,1.0f);
    glShadeModel(GL_SMOOTH);
    glBegin(GL_QUADS);
    //front
        glNormal3f(0.0f,0.0f,1.0f);
        //up
        glColor3f(0.4f,0.4f,0.4f);
        glVertex3f(-0.5f,-0.15f,1.0);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex3f(-0.5f,-0.20f,1.5);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex3f(0.5f,-0.20f,1.5);
        glColor3f(0.4f,0.4f,0.4f);
        glVertex3f(0.5f,-0.15f,1.0);
        //middle
        glColor3f(0.8f,0.8f,0.8f);
        glVertex3f(-0.5f,-0.20f,1.5);
        glVertex3f(-0.5f,-0.25f,1.5);
        glVertex3f(0.5f,-0.25f,1.5);
        glVertex3f(0.5f,-0.20f,1.5);
        //down
        glVertex3f(-0.5f,-0.25f,1.5);
        glVertex3f(-0.5f,-0.30f,1.0f);
        glVertex3f(0.5f,-0.30f,1.0);
        glVertex3f(0.5f,-0.25f,1.5);
    //back
        glNormal3f(0.0f,0.0f,-1.0f);
        //up
        glColor3f(0.4f,0.4f,0.4f);
        glVertex3f(0.5f,-0.15f,-1.0);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex3f(0.5f,-0.20f,-1.5);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex3f(-0.5f,-0.20f,-1.5);
        glColor3f(0.4f,0.4f,0.4f);
        glVertex3f(-0.5f,-0.15f,-1.0);
        //middle
        glColor3f(0.8f,0.8f,0.8f);
        glVertex3f(0.5f,-0.20f,-1.5);
        glVertex3f(0.5f,-0.25f,-1.5);
        glVertex3f(-0.5f,-0.25f,-1.5);
        glVertex3f(-0.5f,-0.20f,-1.5);
        //down
        glVertex3f(0.5f,-0.25f,-1.5);
        glVertex3f(0.5f,-0.30f,-1.0);
        glVertex3f(-0.5f,-0.30f,-1.0f);
        glVertex3f(-0.5f,-0.25f,-1.5);
    //Left

        glNormal3f(1.0f,0.0f,0.0f);
        //up
        glColor3f(0.4f,0.4f,0.4f);
        glVertex3f(0.5f,-0.15f,1.0);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex3f(0.5f,-0.20f,1.5);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex3f(0.5f,-0.20f,-1.5);
        glColor3f(0.4f,0.4f,0.4f);
        glVertex3f(0.5f,-0.15f,-1.0);
        //middle
        glColor3f(0.8f,0.8f,0.8f);
        glVertex3f(0.5f,-0.20f,1.5f);
        glVertex3f(0.5f,-0.25f,1.5f);
        glVertex3f(0.5f,-0.25f,-1.5f);
        glVertex3f(0.5f,-0.20f,-1.5f);
        //down
        glVertex3f(0.5f,-0.25f,1.5f);
        glVertex3f(0.5f,-0.30f,1.0f);
        glVertex3f(0.5f,-0.30f,-1.0f);
        glVertex3f(0.5f,-0.25f,-1.5f);

    //Right
        glNormal3f(-1.0f,0.0f,0.0f);
        //up
        glColor3f(0.4f,0.4f,0.4f);
        glVertex3f(-0.5f,-0.15f,-1.0f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex3f(-0.5f,-0.20f,-1.5f);
        glColor3f(0.8f,0.8f,0.8f);        glVertex3f(-0.5f,-0.20f,1.5f);
        glColor3f(0.4f,0.4f,0.4f);
        glVertex3f(-0.5f,-0.15f,1.0f);
        //middle
        glColor3f(0.8f,0.8f,0.8f);
        glVertex3f(-0.5f,-0.20f,-1.5f);
        glVertex3f(-0.5f,-0.25f,-1.5f);
        glVertex3f(-0.5f,-0.25f,1.5f);
        glVertex3f(-0.5f,-0.20f,1.5f);
        //down
        glVertex3f(-0.5f,-0.25f,-1.5f);
        glVertex3f(-0.5f,-0.30f,-1.0f);
        glVertex3f(-0.5f,-0.30f,1.0f);
        glVertex3f(-0.5f,-0.25f,1.5f);
    glEnd();
    glShadeModel(GL_FLAT);
    glPopMatrix();
}

void Carro::setTimer(std::chrono::steady_clock::time_point str)
{
    Carro::start = str;
}

int Carro::getID(){return MyID;}

float Carro::getRadious(){return radious;}
void Carro::setRadious(float r){radious = r;}
float Carro::getMass(){return mass;}
void Carro::setMass(float m){mass = m;}

void Carro::setPositionPoint(float x, float y, float z)
{
    posX = x;   posY = y;   posZ = z;
}
void Carro::setPosX(float x){posX = x;}
void Carro::setPosY(float y){posY = y;}
void Carro::setPosZ(float z){posZ = z;}
float Carro::getPosX(){return posX;}
float Carro::getPosY(){return posY;}
float Carro::getPosZ(){return posZ;}
void Carro::setDirectionVector(float dx, float dy, float dz)
{
    dirX = dx;  dirY = dy;  dirZ = dz;
    updateDirectionAngle();
    updateDirection();
}
void Carro::setDirX(float dx){dirX = dx; updateDirectionAngle(); updateDirection();}
void Carro::setDirY(float dy){dirY = dy; updateDirectionAngle(); updateDirection();}
void Carro::setDirZ(float dz){dirZ = dz; updateDirectionAngle(); updateDirection();}
float Carro::getDirX(){return dirX;}
float Carro::getDirY(){return dirY;}
float Carro::getDirZ(){return dirZ;}
void Carro::setVelocity(float vx, float vz)
{
    velX = vx;  velZ = vz;
}
void Carro::setVelX(float vx){velX = vx;}
void Carro::setVelZ(float vz){velZ = vz;}
float Carro::getVelX(){return velX;}
float Carro::getVelZ(){return velZ;}
void Carro::setAcceleration(float ax, float az)
{
    accX = ax;  accZ = az;
}
void Carro::setAccX(float ax){accX = ax;}
void Carro::setAccZ(float az){accZ = az;}
float Carro::getAccX(){return accX;}
float Carro::getAccZ(){return accZ;}
void Carro::setStepMagnitude(float m){s_magnitude = m;}
float Carro::getStepMagnitude(){return s_magnitude;}
void Carro::setRotMagnitude(float m){r_magnitude = m;}
float Carro::getRotMagnitude(){return r_magnitude;}
float Carro::getDirection(){return direction;}

void Carro::accelerateForward()
{
    accX = 0.1 * s_magnitude * dirX;
    accZ = 0.1 * s_magnitude * dirZ;
}

void Carro::accelerateBackward()
{
    accX = - 0.1 * s_magnitude * dirX;
    accZ = - 0.1 * s_magnitude * dirZ;
}

void Carro::moveRight()
{
    direction += r_magnitude;
    direction = (direction >= 360.0f) ? direction-360.0f : direction;
    updateDirection();
}

void Carro::moveLeft()
{
    direction -= r_magnitude;
    direction = (direction < 0.0f) ? direction+360.0f : direction;
    updateDirection();
}

void Carro::attack(Carro *target, int seconds)
{
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    int elapsed_time = int(std::chrono::duration_cast <std::chrono::seconds>(end - Carro::start).count());

    //nuevo vector de direccionamiento para enemigo
    float vecX = target->getPosX() - posX;
    float vecZ = target->getPosZ() - posZ;

    //normalizacion del vector
    float hyp = std::sqrt((vecX * vecX) + (vecZ * vecZ));
    vecX /= hyp;
    vecZ /= hyp;

    //actualizando posicion del enemigo
    setDirectionVector(vecX,dirY,vecZ);

    //acelarcion cada 3 segundos por 1 segundo
    if(elapsed_time % seconds == 0)
        accelerateForward();
}

void Carro::updateDirection()
{
    float rads = Util::degToRad(direction);

    //std::cout << direction << std::endl;

    dirX = cos(rads);
    dirZ = sin(rads);
}

void Carro::updateDirectionAngle()
{
    direction = Util::getAngle(dirX,dirZ);
}

void Carro::draw()
{
    glPushMatrix();

    // Estas funciones permiten posicionar al carro en su lugar
    glTranslatef(posX,posY,posZ);
    glRotatef(direction-90,0,-1,0);

    tex.loadTexture(texFilename[1]);    // Textura de la base
    drawBase();

    tex.loadTexture(texFilename[0]);    // Textura de la parte superior
    drawUp();

    drawBottom();

    glPopMatrix();
}
