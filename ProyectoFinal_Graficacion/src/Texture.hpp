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
        //GLuint texture[NTextures];
        GLuint *texture;

    public:
        Texture(unsigned int ); //solo almacena la cantidad de texturas que tendra
       // Texture(const char*, int);
        ~Texture();
        void setNumTextures(unsigned int);
        void loadTexture(char*,int);    //carga las texturas
        void Bind(int );    //bindTextures


};


#endif // TEXTURE_HPP_INCLUDED
