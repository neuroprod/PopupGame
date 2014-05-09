//
//  GroundTile.h
//  PopGame
//
//  Created by Kris Temmerman on 07/05/14.
//
//

#ifndef __PopGame__GroundTile__
#define __PopGame__GroundTile__

#include <iostream>
#include "Sprite.h"
#include "Image.h"
#include "GroundBase.h"
class GroundTile:public neuro::Sprite
{
public:
    GroundTile(){}
    void setup();
    void recalculate();

    neuro::Image *base;
GroundBase *baseG;
      Perlin *pNoise;
    float realY;
};

#endif /* defined(__PopGame__GroundTile__) */
