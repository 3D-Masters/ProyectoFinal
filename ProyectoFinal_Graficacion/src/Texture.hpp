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
        int NTextures;
        GLuint texture;

    public:
        Texture(unsigned int ); //solo almacena la cantidad de texturas que tendra
        ~Texture();
        void setNumTextures(unsigned int);
        void loadTexture(char*);    //carga las texturas
        void Bind();    //bindTextures
};


#endif // TEXTURE_HPP_INCLUDED
