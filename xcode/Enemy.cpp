//
//  Enemy.cpp
//  PopGame
//
//  Created by Kris Temmerman on 07/05/14.
//
//

#include "Enemy.h"


void Enemy::setup(int type)
{

    load("plane2.png","plane2h.png");
    setAlign(neuro::ALIGN_CENTER);


}
void Enemy::reset(float posX, float posY)
{
    alpha =1;
    lives =1;
    x=posX;
    xStart = posX;
    y=posY;
    z= rand()%100-50;
    time =(float)rand()/RAND_MAX *2;

}
void Enemy::update(float timeEllapsed)
{

    time +=timeEllapsed;
    
    float xOld =x.value();
    x= xStart+sin (time*2)*200;
    
   float s = xOld-x;
    rotationY = s/50;

}