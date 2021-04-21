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
    texFilename[1] = "res/backTexture.bmp";
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
        //tex.Bind(); //bind Texture 0

        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.0f,0.0f);        glVertex3f(0.5f, -0.15f, -1.0f);
        glTexCoord2f(1.0f,0.0f);        glVertex3f(-0.5f, -0.15f, -1.0f);
        glTexCoord2f(1.0f,1.0f);        glVertex3f(-0.5f, 0.15f, -1.0f);
        glTexCoord2f(0.0f,1.0f);        glVertex3f(0.5f, 0.15f, -1.0f);
	//Back
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-0.5f, -0.15f, 1.0f);
        glVertex3f(-0.5f, -0.15f, -1.0f);
        glVertex3f(-0.5f, 0.15f, -1.0f);
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

}
void ModelX::drawRueda()
{
    glPushMatrix();
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);
    //front
        //up
        glNormal3f(0.0f,0.0f,1.0f);
            glVertex3f(-0.5f,-0.15f,1.0);
            glVertex3f(-0.5f,-0.20f,1.5);
            glVertex3f(0.5f,-0.20f,1.5);
            glVertex3f(0.5f,-0.15f,1.0);
        //middle
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
        //up
        glNormal3f(0.0f,0.0f,-1.0f);
            glVertex3f(-0.5f,-0.15f,-1.0);
            glVertex3f(-0.5f,-0.20f,-1.5);
            glVertex3f(0.5f,-0.20f,-1.5);
            glVertex3f(0.5f,-0.15f,-1.0);
        //middle
            glVertex3f(-0.5f,-0.20f,-1.5);
            glVertex3f(-0.5f,-0.25f,-1.5);
            glVertex3f(0.5f,-0.25f,-1.5);
            glVertex3f(0.5f,-0.20f,-1.5);
        //down
            glVertex3f(-0.5f,-0.25f,-1.5);
            glVertex3f(-0.5f,-0.30f,-1.0f);
            glVertex3f(0.5f,-0.30f,-1.0);
            glVertex3f(0.5f,-0.25f,-1.5);
    //right
        //up
        glNormal3f(1.0f,0.0f,0.0f);
            glVertex3f(0.5f,-0.15f,1.0);
            glVertex3f(0.5f,-0.20f,1.0);
            glVertex3f(0.5f,-0.20f,-1.0);
            glVertex3f(0.5f,-0.15f,-1.0);
        //middle
            glVertex3f(0.5f,-0.20f,1.0f);
            glVertex3f(0.5f,-0.25f,1.0f);
            glVertex3f(0.5f,-0.25f,-1.0f);
            glVertex3f(0.5f,-0.20f,-1.0f);
        //down
            glVertex3f(0.5f,-0.25f,1.0f);
            glVertex3f(0.5f,-0.30f,1.0f);
            glVertex3f(0.5f,-0.30f,-1.0f);
            glVertex3f(0.5f,-0.25f,-1.0f);
    //left
        glNormal3f(-1.0f,0.0f,0.0f);
        //up
            glVertex3f(-0.5f,-0.15f,1.0f);
            glVertex3f(-0.5f,-0.20f,1.5f);
            glVertex3f(-0.5f,-0.20f,-1.5f);
            glVertex3f(-0.5f,-0.15f,-1.0f);
        //middle
            glVertex3f(-0.5f,-0.20f,1.5f);
            glVertex3f(-0.5f,-0.25f,1.5f);
            glVertex3f(-0.5f,-0.25f,-1.5f);
            glVertex3f(-0.5f,-0.20f,-1.5f);
        //down
            glVertex3f(-0.5f,-0.25f,1.5f);
            glVertex3f(-0.5f,-0.30f,1.0f);
            glVertex3f(-0.5f,-0.30f,-1.0f);
            glVertex3f(-0.5f,-0.25f,-1.5f);
    //bottom
        glNormal3f(0.0f,-1.0f,0.0f);
        glVertex3f(-0.5f,-0.30f,1.0f);
        glVertex3f(-0.5f,-0.30f,-1.0f);
        glVertex3f(0.5,-0.30f,-1.0f);
        glVertex3f(0.5f,-0.30f,1.0f);

    glEnd();
}
void ModelX::drawUp()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glColor3f(1.0f,1.0f,1.0f);
    //glRotatef(ang,0.0f,1.0f,1.0f);    //PRUEBA
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
        tex.Bind();

        glTexCoord2f(0.0f,0.0f);
        glNormal3f(-1.0f,0.0f,0.0f);
        glVertex3f(-0.5f,0.15f,1.0f);
        /*glTexCoord2f(1.0,0.0);*/      glVertex3f(-0.5f,0.15f,-1.0f);
        /*glTexCoord2f(1.0f,1.0f);*/    glVertex3f(-0.3f,0.45f,-0.7f);
        /*glTexCoord2f(0.0f,1.0f);*/    glVertex3f(-0.3f,0.45f,0.7);
    //back
        glNormal3f(0.0f,0.0f,-1.0f);
        glVertex3f(-0.5f,0.15f,-1.0f);
        glVertex3f(0.5f,0.15f,-1.0);
        glVertex3f(0.4f,0.45f,-0.7);
        glVertex3f(-0.3,0.45f,-0.7);
    //top
        tex.Bind();
        glTexCoord2f(0.0f,0.0f);
        glNormal3f(0.0f,1.0f,0.0f);
        glVertex3f(-0.3f,0.45f,0.7f);
        glTexCoord2f(1.0f,0.0f);        glVertex3f(0.4f,0.45f,0.7f);
        glTexCoord2f(1.0f,1.0f);        glVertex3f(0.4f,0.45f,-0.7f);
        glTexCoord2f(0.0f,1.0f);        glVertex3f(-0.3f,0.45f,-0.7f);
    //bottom
        //glNormal3f(0.0f,-1.0,0.0f);

    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void ModelX::draw()
{
    tex.loadTexture(texFilename[1]);        //Cargando Textura
    //Dibujando el auto de forma solida
    glPushMatrix();

    // Estas funciones permiten posicionar al carro en su lugar
    glTranslatef(posX,posY,posZ);
    glRotatef(direction,0,-1,0);
    glPushMatrix();
        glRotatef(-90,0,-1,0);
        drawBase();

        tex.loadTexture(texFilename[0]);
        drawUp();
        glPushMatrix();
            drawRueda();
        glPopMatrix();

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
    initTextures();
}
ModelY::~ModelY(){}

void ModelY::initTextures()
{
    texFilename[0] = "res/mY.bmp";
    texFilename[1] = "res/modely.bmp";
}

void ModelY::drawBase()
{
    //Activando las texturas
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glColor3f(1.0f,1.0f,1.0f);
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
        //tex.Bind(); //bind Texture 0

        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.0f,0.0f);        glVertex3f(0.5f, -0.15f, -1.0f);
        glTexCoord2f(1.0f,0.0f);        glVertex3f(-0.5f, -0.15f, -1.0f);
        glTexCoord2f(1.0f,1.0f);        glVertex3f(-0.5f, 0.15f, -1.0f);
        glTexCoord2f(0.0f,1.0f);        glVertex3f(0.5f, 0.15f, -1.0f);
	//Back
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-0.5f, -0.15f, 1.0f);
        glVertex3f(-0.5f, -0.15f, -1.0f);
        glVertex3f(-0.5f, 0.15f, -1.0f);
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
}
void ModelY::drawRueda()
{
    glPushMatrix();
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);
    //front
        //up
        glNormal3f(0.0f,0.0f,1.0f);
            glVertex3f(-0.5f,-0.15f,1.0);
            glVertex3f(-0.5f,-0.20f,1.5);
            glVertex3f(0.5f,-0.20f,1.5);
            glVertex3f(0.5f,-0.15f,1.0);
        //middle
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
        //up
        glNormal3f(0.0f,0.0f,-1.0f);
            glVertex3f(-0.5f,-0.15f,-1.0);
            glVertex3f(-0.5f,-0.20f,-1.5);
            glVertex3f(0.5f,-0.20f,-1.5);
            glVertex3f(0.5f,-0.15f,-1.0);
        //middle
            glVertex3f(-0.5f,-0.20f,-1.5);
            glVertex3f(-0.5f,-0.25f,-1.5);
            glVertex3f(0.5f,-0.25f,-1.5);
            glVertex3f(0.5f,-0.20f,-1.5);
        //down
            glVertex3f(-0.5f,-0.25f,-1.5);
            glVertex3f(-0.5f,-0.30f,-1.0f);
            glVertex3f(0.5f,-0.30f,-1.0);
            glVertex3f(0.5f,-0.25f,-1.5);
    //right
        //up
        glNormal3f(1.0f,0.0f,0.0f);
            glVertex3f(0.5f,-0.15f,1.0);
            glVertex3f(0.5f,-0.20f,1.0);
            glVertex3f(0.5f,-0.20f,-1.0);
            glVertex3f(0.5f,-0.15f,-1.0);
        //middle
            glVertex3f(0.5f,-0.20f,1.0f);
            glVertex3f(0.5f,-0.25f,1.0f);
            glVertex3f(0.5f,-0.25f,-1.0f);
            glVertex3f(0.5f,-0.20f,-1.0f);
        //down
            glVertex3f(0.5f,-0.25f,1.0f);
            glVertex3f(0.5f,-0.30f,1.0f);
            glVertex3f(0.5f,-0.30f,-1.0f);
            glVertex3f(0.5f,-0.25f,-1.0f);
    //left
        glNormal3f(-1.0f,0.0f,0.0f);
        //up
            glVertex3f(-0.5f,-0.15f,1.0f);
            glVertex3f(-0.5f,-0.20f,1.5f);
            glVertex3f(-0.5f,-0.20f,-1.5f);
            glVertex3f(-0.5f,-0.15f,-1.0f);
        //middle
            glVertex3f(-0.5f,-0.20f,1.5f);
            glVertex3f(-0.5f,-0.25f,1.5f);
            glVertex3f(-0.5f,-0.25f,-1.5f);
            glVertex3f(-0.5f,-0.20f,-1.5f);
        //down
            glVertex3f(-0.5f,-0.25f,1.5f);
            glVertex3f(-0.5f,-0.30f,1.0f);
            glVertex3f(-0.5f,-0.30f,-1.0f);
            glVertex3f(-0.5f,-0.25f,-1.5f);
    //bottom
        glNormal3f(0.0f,-1.0f,0.0f);
        glVertex3f(-0.5f,-0.30f,1.0f);
        glVertex3f(-0.5f,-0.30f,-1.0f);
        glVertex3f(0.5,-0.30f,-1.0f);
        glVertex3f(0.5f,-0.30f,1.0f);

    glEnd();
}
void ModelY::drawUp()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glColor3f(1.0f,1.0f,1.0f);
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
        //tex.Bind();

        glTexCoord2f(0.0f,0.0f);
        glNormal3f(-1.0f,0.0f,0.0f);
        glVertex3f(-0.5f,0.15f,1.0f);
        glTexCoord2f(1.0,0.0);      glVertex3f(-0.5f,0.15f,-1.0f);
        glTexCoord2f(1.0f,1.0f);    glVertex3f(-0.3f,0.45f,-0.7f);
        glTexCoord2f(0.0f,1.0f);    glVertex3f(-0.3f,0.45f,0.7);
    //back
        glNormal3f(0.0f,0.0f,-1.0f);
        glVertex3f(-0.5f,0.15f,-1.0f);
        glVertex3f(0.5f,0.15f,-1.0);
        glVertex3f(0.4f,0.45f,-0.7);
        glVertex3f(-0.3,0.45f,-0.7);
    //top
        //tex.Bind();
        glTexCoord2f(0.0f,0.0f);
        glNormal3f(0.0f,1.0f,0.0f);
        glVertex3f(-0.3f,0.45f,0.7f);
        glTexCoord2f(1.0f,0.0f);        glVertex3f(0.4f,0.45f,0.7f);
        glTexCoord2f(1.0f,1.0f);        glVertex3f(0.4f,0.45f,-0.7f);
        glTexCoord2f(0.0f,1.0f);        glVertex3f(-0.3f,0.45f,-0.7f);

    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}
void ModelY::draw()
{
    tex.loadTexture(texFilename[1]);        //Cargando Textura
    //Dibujando el auto de forma solida
    glPushMatrix();

    // Estas funciones permiten posicionar al carro en su lugar
    glTranslatef(posX,posY,posZ);
    glRotatef(direction,0,-1,0);
    glPushMatrix();
        glRotatef(-90,0,-1,0);
        drawBase();

        tex.loadTexture(texFilename[0]);
        drawUp();
        glPushMatrix();
            drawRueda();
        glPopMatrix();

    glPopMatrix();
    glPopMatrix();
}
void ModelY::update()
{

}
