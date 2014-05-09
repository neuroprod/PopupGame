//
//  Bullet.cpp
//  PopGame
//
//  Created by Kris Temmerman on 07/05/14.
//
//

#include "Bullet.h"


void Bullet::setup()
{
    isAdditiveBlending =true;
   load("bullet.png");
    scaleX = scaleY = 8;
     scaleZ = 8;
}
