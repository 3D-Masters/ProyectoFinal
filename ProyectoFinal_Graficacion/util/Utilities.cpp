#include "Utilities.hpp"

float Util::degToRad(float degrees)
{
      return ((degrees*M_PI)/180.0f);
}

float Util::radToDeg(float radians)
{
      return (radians*180.0f/M_PI);
}

float Util::getAngle(float dirX, float dirZ)
{
    float theta;

    if(dirX != 0.0f)
    {
        if(dirX > 0.0f && dirZ >= 0.0f)                 // Cuadrante 1
            theta = radToDeg(atan(dirZ/dirX));
        else if(dirX < 0.0f)                            // Cuadrante 2 & 3
            theta = 180.0f+radToDeg(atan(dirZ/dirX));
        else if(dirX > 0.0f && dirZ < 0.0f)             // Cuadrante 4
            theta = 360.0f+radToDeg(atan(dirZ/dirX));
    }
    else
    {
        theta = (dirZ >= 0.0f ? 90 : 270);
    }

    return theta;
}

float Util::pointDistance(float x1, float y1, float z1, float x2, float y2, float z2)
{
    float x = (x2 - x1), y = (y2 - y1), z = (z2 - z1);
    return std::sqrt((x * x) + (y * y) + (z * z));
}
