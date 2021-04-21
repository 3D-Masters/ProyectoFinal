#include "Model.hpp"

ModelX::ModelX():Carro()
{
    initTextures();
}
ModelX::~ModelX(){}

void ModelX::initTextures()
{
    texFilename[0] = "res/upX.bmp";
    texFilename[1] = "res/baseX.bmp";
}

//Model Y
ModelY::ModelY():Carro()
{
    initTextures();
}
ModelY::~ModelY(){}

void ModelY::initTextures()
{
    texFilename[0] = "res/upY.bmp";
    texFilename[1] = "res/baseY.bmp";
}
