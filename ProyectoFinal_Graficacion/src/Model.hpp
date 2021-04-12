#ifndef MODEL_HPP_INCLUDED
#define MODEL_HPP_INCLUDED

#include "Carro.hpp"

class ModelX:public Carro
{
    private:
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
