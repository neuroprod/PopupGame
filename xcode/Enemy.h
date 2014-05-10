//
//  Enemy.h
//  PopGame
//
//  Created by Kris Temmerman on 07/05/14.
//
//

#ifndef __PopGame__Enemy__
#define __PopGame__Enemy__

#include "Shootable.h"
#include <iostream>
class Enemy: public Shootable
{
public:
    Enemy()
    {
        type=1;
    
    }
    void setup(int type);
    void reset(float posX, float posY);
    void update(float timeEllapsed);
    float xStart;
    float time ;
};

#endif /* defined(__PopGame__Enemy__) */
