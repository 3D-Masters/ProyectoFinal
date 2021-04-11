#ifndef CAMARA_HPP
#define CAMARA_HPP
#define PI_ 3.14159f

#include <math.h>
#include <GL/glut.h>


class Camara
{
    private:
        float eyeX, eyeY, eyeZ;
        float centerX, centerY, centerZ;
        float dirX, dirY, dirZ;
        float upX, upY, upZ;
        float magnitude;
        float theta;

        void updateCenter();
        void specialUpdateCenter();
    public:
        Camara(float, float, float, float, float, float, float, float, float, float);
        Camara();
        ~Camara();

        float degToRad(float);
        void setEyeX(float);
        void setEyeY(float);
        void setEyeZ(float);//I don't really think we'll use methods for the Y axis
        void setEye(float, float, float);
        void setCenterX(float);
        void setCenterY(float);
        void setCenterZ(float);
        void setCenter(float, float, float);
        void setDirX(float);
        void setDirY(float);
        void setDirZ(float);
        void setDir(float, float, float);
        void setMagnitude(float);

        float getEyeX();
        float getEyeY();
        float getEyeZ();
        float getCenterX();
        float getCenterY();
        float getCenterZ();
        float getDirX();
        float getDirY();
        float getDirZ();
        float getMagnitude();

        void moveForward();
        void moveBackward();
        void moveRight();
        void moveLeft();
        void colocar();
};

#endif // CAMARA_HPP
