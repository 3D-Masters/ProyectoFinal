#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "RgbImage.hpp"
/*SE CREA UN OBJETO TEXTURA PARA CADA FIGURA */
class Texture{
    private:
        GLuint texture;
    public:
        Texture();
        ~Texture();
        void loadTexture(char*);    //carga las texturas
        void bind();    //bindTextures
        void unbind();  //unbindTextures
};

#endif // TEXTURE_HPP_INCLUDED
