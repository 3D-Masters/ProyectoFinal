#include "Model.hpp"

ModelX::ModelX():Carro()
{
    initTextures();
    ang=0;
}
ModelX::~ModelX(){}

void ModelX::initTextures()
{
    texFilename[0] = "res/default.bmp";
}

void ModelX::drawBase()
{
    //Activando las texturas
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glColor3f(1.0f,1.0f,1.0f);
    //glRotatef(ang,0.0f,1.0,1.0);        //PRUEBA
    glBegin(GL_QUADS);
    /*=======BASE AUTO=======*/
    //front
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-0.5f, -0.15f, 1.0f);
        glVertex3f(0.5f, -0.15f, 1.0f);
        glVertex3f(0.5f, 0.15f, 1.0f);
        glVertex3f(-0.5f, 0.15f, 1.0f);
	//Right
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.5f, -0.15f, 1.0f);
        glVertex3f(0.5f, -0.15f, -1.0f);
        glVertex3f(0.5f, 0.15f, -1.0f);
        glVertex3f(0.5f, 0.15f, 1.0f);
	//Left
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(0.5f, -0.15f, -1.0f);
        glVertex3f(-0.5f, -0.15f, -1.0f);
        glVertex3f(-0.5f, 0.15f, -1.0f);
        glVertex3f(0.5f, 0.15f, -1.0f);
	//Back
        tex.Bind(0);  //Bind Texture 0

        glTexCoord2f(1.0f,1.0f);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glTexCoord2f(0.0f,0.0f);
        glVertex3f(-0.5f, -0.15f, 1.0f);
        glTexCoord2f(1.0f,0.0f);
        glVertex3f(-0.5f, -0.15f, -1.0f);
        glTexCoord2f(1.0f,1.0f);
        glVertex3f(-0.5f, 0.15f, -1.0f);
        glTexCoord2f(0.0f,1.0f);
        glVertex3f(-0.5f, 0.15f, 1.0f);
    //Bottom
        glNormal3f(0.0f,-1.0f,0.0f);
        glVertex3f(-0.5f,-0.15f,1.0f);
        glVertex3f(0.5f,-0.15f,1.0f);
        glVertex3f(0.5f,-0.15f,-1.0f);
        glVertex3f(-0.5f,-0.15f,-1.0f);

	glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    //dibujandoLlantas
    //glPushMatrix();

}
void ModelX::drawUp()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glColor3f(1.0f,1.0f,1.0f);
    //glRotatef(ang,0.0f,1.0f,1.0f);
    glBegin(GL_QUADS);
    /*=====PARTE SUPERIOR=====*/
    //front
        glNormal3f(0.0f,0.0f,1.0f);
        glVertex3f(-0.5,0.15,1.0);
        glVertex3f(0.5,0.15,1.0);
        glVertex3f(0.4,0.45,0.7);
        glVertex3f(-0.3,0.45,0.7);
    //right
        glNormal3f(1.0f,0.0f,0.0f);
        glVertex3f(0.5,0.15,1.0);
        glVertex3f(0.5,0.15,-1.0);
        glVertex3f(0.4,0.45,-0.7);
        glVertex3f(0.4,0.45,0.7);
    //left
        tex.Bind(0);

        glTexCoord2f(0.0f,0.0f);
        glNormal3f(-1.0f,0.0f,0.0f);
        glVertex3f(-0.5f,0.15f,1.0f);
        glTexCoord2f(1.0,0.0);
        glVertex3f(-0.5f,0.15f,-1.0f);
        glTexCoord2f(1.0f,1.0f);
        glVertex3f(-0.3f,0.45f,-0.7f);
        glTexCoord2f(0.0f,1.0f);
        glVertex3f(-0.3f,0.45f,0.7);
    //back
        glNormal3f(0.0f,0.0f,-1.0f);
        glVertex3f(-0.5f,0.15f,-1.0f);
        glVertex3f(0.5f,0.15f,-1.0);
        glVertex3f(0.4f,0.45f,-0.7);
        glVertex3f(-0.3,0.45f,-0.7);
    //top
        tex.Bind(0);
        glTexCoord2f(0.0f,0.0f);
        glNormal3f(0.0f,1.0f,0.0f);
        glVertex3f(-0.3f,0.45f,0.7f);
        glTexCoord2f(1.0f,0.0f);
        glVertex3f(0.4f,0.45f,0.7f);
        glTexCoord2f(1.0f,1.0f);
        glVertex3f(0.4f,0.45f,-0.7f);
        glTexCoord2f(0.0f,1.0f);
        glVertex3f(-0.3f,0.45f,-0.7f);
    //bottom
        //glNormal3f(0.0f,-1.0,0.0f);

    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void ModelX::draw()
{
    //Cargando Textura
    tex.loadTexture(texFilename[0],0);
    //Dibujando el auto de forma solida
    glPushMatrix();

    // Estas funciones permiten posicionar al carro en su lugar
    glTranslatef(posX,posY,posZ);
    glRotatef(direction,0,-1,0);

    glPushMatrix();
        drawBase();
        drawUp();
        //dibujando las llantas
        /*glPushMatrix();
        glRotatef(90,1.0,0.0,0.0);
        glTranslatef(-0.35,-0.1,1.0);
        //gluCylinder()
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.35,-0.1,-1.0);

        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.35,-0.1,1.0);

        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.35,-0.1,-1.0);

        glPopMatrix();*/

    glPopMatrix();

    glPopMatrix();
}
void ModelX::update()
{
    ang+=0.2f;                          //PRUEBA
}

//Model Y
ModelY::ModelY():Carro()
{

}
ModelY::~ModelY(){}

void ModelY::draw()
{

}
void ModelY::update()
{

}
