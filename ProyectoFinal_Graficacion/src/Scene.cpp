#include "Scene.hpp"

Scene::Scene():
    cam(0,0,0,0,0,1,0,1,0,0.75f,1.5f)
{
    karts[0] = &mx;
    karts[1] = &mx2;
    karts[2] = &mx3;
    karts[3] = &mx4;
    /*karts[4] = &mx5;
    karts[5] = &mx6;*/
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
    mx.setDirectionVector(0,0,1);
    mx.setPositionPoint(0,0,0);

    mx.setVelocity(0,0);

    mx2.setDirectionVector(0,0,1);
    mx2.setPositionPoint(30,0,0);

    mx3.setDirectionVector(0,0,1);
    mx3.setPositionPoint(-30,0,0);

    mx4.setDirectionVector(0,0,1);
    mx4.setPositionPoint(0,0,30);

    /*mx5.setDirectionVector(0,0,1);
    mx5.setPositionPoint(0,0,-30);*/
    my.setDirectionVector(0,0,1);
    my.setPositionPoint(0,0,-30);
    /*mx6.setDirectionVector(0,0,1);
    mx6.setPositionPoint(0,0,15);*/
    my2.setDirectionVector(0,0,1);
    my2.setPositionPoint(0,0,15);

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
    //El kart2 ataca al jugador (mx)
    attack(&mx2,&mx);

    //El kart3 "vigila" una circunferencia y si se acerca
    //una cierta distancia el jugador, ataca
    float safeDistance = 20.0f;
    float distance = Util::pointDistance(mx3.getPosX(),
                                         mx3.getPosY(),
                                         mx3.getPosZ(),
                                         mx.getPosX(),
                                         mx.getPosY(),
                                         mx.getPosZ());
    if(distance - (mx3.getRadious() + mx.getRadious()) < safeDistance)
    {
        attack(&mx3, &mx);
        //std::cout << "mx is being attacked!" << std::endl;
    }
    else
    {
        //mx3.setDirX(std::cos(step) * 2);
        //mx3.setDirZ(std::sin(step) * 2);
        //mx3.accelerateForward();
        //circular motion
        mx3.setPosX(mx3.getPosX() + (std::cos(angle)));// *5.0f)*0.1f);
        mx3.setPosZ(mx3.getPosZ() + (std::sin(angle)));// *5.0f)*0.1f);
    }

    //el kart4 ataca al kart2
    attack(&mx4,&mx2);

    //kart5 y kart6 se atacan entre elos
    /*attack(&mx5,&mx6);
    attack(&mx6,&mx5);*/
    attack(&my,&my2);
    attack(&my2,&my);

    //según calcular valores muy grandes de sin o cos es costoso
    if(angle >= 359.0f)
        angle = 0.0f;
    angle += 0.2f;
}

void Scene::attack(ModelX *enemy, ModelX *victim)
{
    auto end = std::chrono::steady_clock::now();
    int elapsed_time = int(std::chrono::duration_cast <std::chrono::seconds>(end - start).count());
    //nuevo vector de direccionamiento para enemigo

    float dirX = victim->getPosX() - enemy->getPosX();
    float dirZ = victim->getPosZ() - enemy->getPosZ();


    //normalizacion del vector
    float hyp = std::sqrt((dirX * dirX) + (dirZ * dirZ));
    dirX /= hyp;
    dirZ /= hyp;

    //actualizando posicion del enemigo
    enemy->setDirX(dirX);
    enemy->setDirZ(dirZ);

    //acelarcion cada 3 segundos por 1 segundo
    if(elapsed_time % 3 == 0)
        enemy->accelerateForward();
}
void Scene::attack(ModelY *enemy,ModelY *victim)
{
    auto end = std::chrono::steady_clock::now();
    int elapsed_time = int(std::chrono::duration_cast <std::chrono::seconds>(end - start).count());
    //nuevo vector de direccionamiento para enemigo

    float dirX = victim->getPosX() - enemy->getPosX();
    float dirZ = victim->getPosZ() - enemy->getPosZ();


    //normalizacion del vector
    float hyp = std::sqrt((dirX * dirX) + (dirZ * dirZ));
    dirX /= hyp;
    dirZ /= hyp;

    //actualizando posicion del enemigo
    enemy->setDirX(dirX);
    enemy->setDirZ(dirZ);

    //acelarcion cada 3 segundos por 1 segundo
    if(elapsed_time % 3 == 0)
        enemy->accelerateForward();
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
