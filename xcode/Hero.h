//
//  Hero.h
//  PopGame
//
//  Created by Kris Temmerman on 07/05/14.
//
//

#ifndef __PopGame__Hero__
#define __PopGame__Hero__

#include "Shootable.h"
#include <iostream>
class Hero: public Shootable
{
public:
    Hero(){
    
        isUp =false;
        isDown =false;
        isLeft =false;
        isRight =false;
        isShoot =false;
        speedX=0;
        speedY=0;
    
    }
    virtual void update(float timeEllapsed);
    void setKey(int updown, int key);
    float speedX;
    float speedY;
    bool isUp;
    bool isDown;
    bool isLeft;
    bool isRight;
     bool isShoot;
    float lastShoot;
};

#endif /* defined(__PopGame__Hero__) */
