//
//  Shootable.h
//  PopGame
//
//  Created by Kris Temmerman on 07/05/14.
//
//

#ifndef __PopGame__Shootable__
#define __PopGame__Shootable__
#include "Image2hD.h"
#include <iostream>
class Shootable: public neuro::Image2hD
{
public:
    Shootable(){type=0;lives=1;}
   bool chekBulletHit(Vec2f &posB);
    
    int lives;
    int type;
};
#endif /* defined(__PopGame__Shootable__) */
