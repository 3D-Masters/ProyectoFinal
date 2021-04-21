#ifndef MODEL_HPP_INCLUDED
#define MODEL_HPP_INCLUDED

#include "Carro.hpp"
#include "Texture.hpp"
class ModelX:public Carro
{
    private:
        void initTextures();
    public:
        ModelX();
        ~ModelX();
};
class ModelY:public Carro
{
    private:
        void initTextures();
    public:
        ModelY();
        ~ModelY();
};

#endif // MODEL_HPP_INCLUDED
