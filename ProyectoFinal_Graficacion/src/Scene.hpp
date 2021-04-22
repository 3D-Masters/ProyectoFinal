#ifndef SCENE_HPP_INCLUDED
#define SCENE_HPP_INCLUDED

#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <chrono>

#include "../util/Utilities.hpp"
#include "SkyBox.hpp"
#include "Camara.hpp"
#include "Carro.hpp"
#include "Model.hpp"
#include "Muro.hpp"
#include "Piso.hpp"

#define NUM_KARTS 6

class Scene
{
    private:
        std::chrono::steady_clock::time_point start;

        float angle;
        SkyBox sky;
        Camara cam;
        ModelX mx, mx2, mx3, mx4;
        ModelY my,my2;
        Carro *karts[NUM_KARTS];
        Muro muro;
        Piso piso;

        bool arrows[4];

        void updateOthers();
        void updateMovement();
        void handleCollisions();
        void draw();
    public:
        Scene();
        ~Scene();

        void init();
        void inputPressed(int,int,int);
        void inputReleased(int,int,int);
        void display();
};

#endif // SCENE_HPP_INCLUDED
