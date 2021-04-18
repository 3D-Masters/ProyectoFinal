#include "Texture.hpp"



Texture::Texture(unsigned int cant)
{
    NTextures = cant;
    //filename[0] = "RedLeavesTexture.bmp";
    texture = new GLuint[NTextures];
}
Texture::~Texture()
{
    delete [] texture;
}
void Texture::setNumTextures(unsigned int cant)
{
    NTextures = cant;
}
void Texture::loadTexture(char* filename, int index)
{
//pasar nomArchivo, index y cantidad de texturas

    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_FLAT);

    RgbImage theTexMap( filename );

    glGenTextures(1,&texture[index]);

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
void Texture::Bind(int index)
{
    glBindTexture(GL_TEXTURE_2D,texture[index]);
}


