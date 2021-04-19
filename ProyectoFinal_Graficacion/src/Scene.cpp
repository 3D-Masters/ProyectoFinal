#include "Scene.hpp"

Scene::Scene():
    cam(0,0,0,0,0,1,0,1,0,0.75f,1.5f)
{
    karts[0] = &mx;
    karts[1] = &mx2;
    karts[2] = &mx3;

    for(int i = 0; i < 4; i++)
        arrows[i] = false;

    start = std::chrono::steady_clock::now();
}

Scene::~Scene(){}

void Scene::init()
{
    mx.setDirectionVector(0,0,1);
    mx.setPositionPoint(0,0,0);

    mx.setVelocity(0,0);

    mx2.setDirectionVector(0,0,1);
    mx2.setPositionPoint(30,0,0);

    mx3.setDirectionVector(0,0,1);
    mx3.setPositionPoint(-30,0,0);
    /*
    mx4.setDirectionVector(0,0,1);
    mx4.setPositionPoint(0,0,30);

    mx5.setDirectionVector(0,0,1);
    mx5.setPositionPoint(0,0,-30);
    */
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
    auto end = std::chrono::steady_clock::now();

    int elapsed_time = int(std::chrono::duration_cast <std::chrono::seconds>(end - start).count());
    float divisor =  1.0f; //std::rand() % 11;
    float a, b, c, d , e;

    //std::cout << elapsed_time << std::endl;

    if((elapsed_time % 2) == 0)
    {
        a = std::rand() % 2;
        b = std::rand() % 2;
        c = std::rand() % 2;
        d = std::rand() % 2;
        e = std::rand() % 2;

        a /= divisor;
        b /= divisor;
        c /= divisor;
        d /= divisor;
        e /= divisor;

        mx2.setDirectionVector(a,0,c);
        mx3.setDirectionVector(b,0,d);
        //mx4.setDirectionVector(c,0,e);
        //mx5.setDirectionVector(d,0,a);

        mx2.accelerateBackward();
        mx3.accelerateBackward();
        //mx4.moveBackward();
        //mx5.moveBackward();
    }
    else
    {
        mx2.accelerateForward();
        mx3.accelerateForward();
        //mx4.moveForward();
        //mx5.moveForward();
    }
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

    for(int i = 0; i < NUM_SPHERES; i++)
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

    float mass = 10.0f;
    float wallMass = 50.0f;

    float distance;
    float overlap, overlapX, overlapZ;

    std::vector<std::pair<Carro*,Carro*>> parDeColision;
    std::vector<Carro*> colisionConMuro;

    for(int i = 0; i < NUM_SPHERES; i++)
    {
        current = karts[i];
        for(int j = 0; j < NUM_SPHERES; j++)
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

                    // Calculate displacement required
                    overlap = 0.5f * (distance - current->getRadious() + target->getRadious());

                    // Displace Current Ball away from collision
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

            // Calculate displacement required
            overlap = current->getRadious() + distance - muro.getRadious();

            // Displace Current Ball away from collision
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

        float nx = (target->getPosX() - current->getPosX()) / distance;
        float nz = (target->getPosZ() - current->getPosZ()) / distance;

        float kx = (current->getVelX() - target->getVelX());
        float kz = (current->getVelZ() - target->getVelZ());
        float p = 2.0 * (nx * kx + nz * kz) / (mass + mass);

        float offsetX = p*mass*nx;
        float offsetZ = p*mass*nz;

        current->setVelX(current->getVelX() - offsetX);
        current->setVelZ(current->getVelZ() - offsetZ);

        target->setVelX(target->getVelX() + offsetX);
        target->setVelZ(target->getVelZ() + offsetZ);
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

        float nx = (muro.getX() - current->getPosX()) / distance;
        float nz = (muro.getZ() - current->getPosZ()) / distance;

        float kx = current->getVelX();
        float kz = current->getVelZ();
        float p = 2.0 * (nx * kx + nz * kz) / (mass + wallMass);

        current->setVelX(current->getVelX() - p*wallMass*nx);
        current->setVelZ(current->getVelZ() - p*wallMass*nz);
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
        mx.getDirY()-0.10,
        mx.getDirZ(),
        0.0f,1.0f,0.0f
    );
    cam.moveBackward();
    cam.moveBackward();
    cam.moveBackward();
    cam.display();

    glPushMatrix();

    glPushMatrix();

    muro.draw();

    glPopMatrix();

    mx.draw();
    mx2.draw();
    mx3.draw();

    glPopMatrix();

    glPopMatrix();
}

void Scene::display()
{
    updateMovement();
    handleCollisions();
    draw();
}
