//
//  Shootable.cpp
//  PopGame
//
//  Created by Kris Temmerman on 07/05/14.
//
//

#include "Shootable.h"


bool Shootable::chekBulletHit(Vec2f &posB)
{
    Vec2f pos =Vec2f(x.value(),y.value());
    if( pos.distanceSquared(posB)< 10000)
    {
        alpha =0;
        return true;
    }

    return false;
    
    
}