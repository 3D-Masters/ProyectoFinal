#include "Scene.hpp"

Scene::Scene():
    cam(0,0,0,0,0,1,0,1,0,0.75f,1.5f)
{
    karts[0] = &mx;
    karts[1] = &mx2;
    karts[2] = &mx3;
    karts[3] = &mx4;
    karts[4] = &my;
    karts[5] = &my2;

    for(int i = 0; i < 4; i++)
        arrows[i] = false;

    start = std::chrono::steady_clock::now();
    angle = 0.0f;
}

Scene::~Scene(){}

void Scene::init()
{
    Carro::setTimer(start);

    mx.setPositionPoint(0,mx.getPosY(),0);
    mx2.setPositionPoint(30,mx2.getPosY(),12);
    mx3.setPositionPoint(-30,mx3.getPosY(),20);
    mx4.setPositionPoint(12,mx4.getPosY(),30);
    my.setPositionPoint(10,my.getPosY(),-30);
    my2.setPositionPoint(30,my2.getPosY(),15);

    cam.display();
}

void Scene::inputPressed(int key, int x, int y)
{
    switch(key){
        case GLUT_KEY_UP:
             arrows[0] = true;
             break;
        case GLUT_KEY_DOWN:
             arrows[1] = true;
             break;
        case GLUT_KEY_RIGHT:
             arrows[2] = true;
             break;
        case GLUT_KEY_LEFT:
             arrows[3] = true;
             break;
    }
}

void Scene::inputReleased(int key, int x, int y)
{
    switch(key){
        case GLUT_KEY_UP:
             arrows[0] = false;
             break;
        case GLUT_KEY_DOWN:
             arrows[1] = false;
             break;
        case GLUT_KEY_RIGHT:
             arrows[2] = false;
             break;
        case GLUT_KEY_LEFT:
             arrows[3] = false;
             break;
    }
}

void Scene::updateOthers()
{
    //El kart2 ataca al kart5
    karts[1]->attack(karts[4],7);

    //El kart3 "vigila" una circunferencia y si se acerca
    //una cierta distancia el jugador, ataca
    float safeDistance = 15.0f;
    float distance = Util::pointDistance(mx3.getPosX(),
                                         mx3.getPosY(),
                                         mx3.getPosZ(),
                                         mx.getPosX(),
                                         mx.getPosY(),
                                         mx.getPosZ());
    if(distance - (mx3.getRadious() + mx.getRadious()) < safeDistance)
    {
        karts[2]->attack(karts[0],2);
    }
    else
    {
        mx3.moveRight();
        mx3.moveRight();
        mx3.accelerateForward();
    }

    //el kart4 ataca al kart6
    karts[3]->attack(karts[5],4);

    //kart5 y kart2 se atacan entre ellos
    karts[4]->attack(karts[1],3);

    //el kart 6 ataca al jugador
    karts[5]->attack(karts[0],5);
}

void Scene::updateMovement()
{
    // Update player
    if(arrows[0] | arrows[1] | arrows[2] | arrows[3])
    {
        if(arrows[0])
            mx.accelerateForward();
        if(arrows[1])
            mx.accelerateBackward();
        if(arrows[2])
            mx.moveRight();
        if(arrows[3])
            mx.moveLeft();
    }

    // NPC movement
    updateOthers();

    for(int i = 0; i < NUM_KARTS; i++)
    {

        karts[i]->setVelocity(
            karts[i]->getVelX()+karts[i]->getAccX(),
            karts[i]->getVelZ()+karts[i]->getAccZ()
        );

        karts[i]->setPositionPoint(
            karts[i]->getPosX()+karts[i]->getVelX(),
            karts[i]->getPosY(),
            karts[i]->getPosZ()+karts[i]->getVelZ()
        );

        karts[i]->setAcceleration(
            -karts[i]->getVelX()*0.015,
            -karts[i]->getVelZ()*0.015
        );

        float magnitude = sqrt(karts[i]->getVelX()*karts[i]->getVelX() + karts[i]->getVelZ()*karts[i]->getVelZ());
        if(magnitude >= karts[i]->getStepMagnitude())
        {
            karts[i]->setVelocity(
                karts[i]->getVelX()/magnitude,
                karts[i]->getVelZ()/magnitude
            );
        }
    }
}

void Scene::handleCollisions()
{
    // Handle static collisions

    Carro* current;
    Carro* target;

    float distance;
    float overlap, overlapX, overlapZ;

    float nx, nz, kx, kz, momentum;

    std::vector<std::pair<Carro*,Carro*>> parDeColision;
    std::vector<Carro*> colisionConMuro;

    for(int i = 0; i < NUM_KARTS; i++)
    {
        current = karts[i];
        for(int j = 0; j < NUM_KARTS; j++)
        {
            target = karts[j];
            if(current->getID() != target->getID())
            {
                // Static collision between karts
                if((distance = Util::pointDistance(
                    current->getPosX(),
                    current->getPosY(),
                    current->getPosZ(),
                    target->getPosX(),
                    target->getPosY(),
                    target->getPosZ()
                )) <= current->getRadious() + target->getRadious())
                {
                    parDeColision.push_back({current,target});

                    // Calculate distance to move of the overlap
                    overlap = 0.5f * (distance - current->getRadious() + target->getRadious());

                    // Move circles to a safe position
                    overlapX = overlap * (current->getPosX() - target->getPosX()) / distance;
                    overlapZ = overlap * (current->getPosZ() - target->getPosZ()) / distance;

                    current->setPositionPoint(
                        current->getPosX() + overlapX,
                        current->getPosY(),
                        current->getPosZ() + overlapZ
                    );

                    target->setPositionPoint(
                        target->getPosX() - overlapX,
                        target->getPosY(),
                        target->getPosZ() - overlapZ
                    );
                }
            }
        }

        // Static collision between karts and wall
        if((distance = Util::pointDistance(
            current->getPosX(),
            current->getPosY(),
            current->getPosZ(),
            muro.getX(),
            muro.getY(),
            muro.getZ()
        )) + current->getRadious() >= muro.getRadious())
        {
            colisionConMuro.push_back(current);

            // Calculate overlap between wall and circle
            overlap = current->getRadious() + distance - muro.getRadious();

            // Move circle to a safe place
            current->setPositionPoint(
                current->getPosX() - overlap * (current->getPosX() - muro.getX()) / distance,
                current->getPosY(),
                current->getPosZ() - overlap * (current->getPosZ() - muro.getZ()) / distance
            );
        }
    }

    // Handle dynamic collisions

    // Dynamic collision between karts
    for(unsigned i = 0; i < parDeColision.size(); i++)
    {
        current = parDeColision[i].first;
        target = parDeColision[i].second;

        distance = Util::pointDistance(
            current->getPosX(),
            current->getPosY(),
            current->getPosZ(),
            target->getPosX(),
            target->getPosY(),
            target->getPosZ()
        );

        nx = (target->getPosX() - current->getPosX()) / distance;
        nz = (target->getPosZ() - current->getPosZ()) / distance;

        kx = (current->getVelX() - target->getVelX());
        kz = (current->getVelZ() - target->getVelZ());
        momentum = 2.0 * (nx * kx + nz * kz) / (current->getMass() + target->getMass());

        current->setVelX(current->getVelX() - momentum*target->getMass()*nx);
        current->setVelZ(current->getVelZ() - momentum*target->getMass()*nz);

        target->setVelX(target->getVelX() + momentum*current->getMass()*nx);
        target->setVelZ(target->getVelZ() + momentum*current->getMass()*nz);
    }

    // Dynamic collision between karts and wall
    for(unsigned i = 0; i < colisionConMuro.size(); i++)
    {
        current = colisionConMuro[i];

        distance = Util::pointDistance(
            current->getPosX(),
            current->getPosY(),
            current->getPosZ(),
            muro.getX(),
            muro.getY(),
            muro.getZ()
        );

        nx = (muro.getX() - current->getPosX()) / distance;
        nz = (muro.getZ() - current->getPosZ()) / distance;

        kx = current->getVelX();
        kz = current->getVelZ();
        momentum = 2.0 * (nx * kx + nz * kz) / (current->getMass());

        current->setVelX(current->getVelX() - momentum*current->getMass()*nx);
        current->setVelZ(current->getVelZ() - momentum*current->getMass()*nz);
    }
}

void Scene::draw()
{
    glPushMatrix();

    glLoadIdentity();
    cam.set(
        mx.getPosX(),
        mx.getPosY()+0.75f,
        mx.getPosZ(),
        mx.getDirX(),
        mx.getDirY(),
        mx.getDirZ(),
        0.0f,1.0f,0.0f
    );
    cam.display();

    glPushMatrix();

    glPushMatrix();

    sky.set(mx.getPosX(),0,mx.getPosZ());
    sky.draw();

    muro.draw();
    piso.draw();

    glPopMatrix();

    for(int i = 0; i < NUM_KARTS; i++)
        karts[i]->draw();

    glPopMatrix();

    glPopMatrix();
}

void Scene::display()
{
    updateMovement();
    handleCollisions();
    draw();
}
