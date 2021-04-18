#ifndef MODEL_HPP_INCLUDED
#define MODEL_HPP_INCLUDED

#include "Carro.hpp"
#include "Texture.hpp"
class ModelX:public Carro
{
    private:
        char* filename[6];
        Texture t;

        void drawBase();
        void drawUp();
    public:
        float ang;

        ModelX();
        ~ModelX();
        void draw();
        void update();
};
class ModelY:public Carro
{
    public:
        ModelY();
        ~ModelY();
        void draw();
        void update();
};

#endif // MODEL_HPP_INCLUDED
