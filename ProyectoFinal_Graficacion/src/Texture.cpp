#include "Texture.hpp"


Texture::Texture(){}

Texture::~Texture()
{
    glDeleteTextures(1,&texture);
}

void Texture::loadTexture(char* filename)
{

    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_FLAT);

    RgbImage theTexMap( filename );

    glGenTextures(1,&texture);

    //controla texture wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//textura no exacta al tmn del objeto
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3,theTexMap.GetNumCols(), theTexMap.GetNumRows(),
					 GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );

    theTexMap.Reset();
}
void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D,texture);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D,0);
}
