//
//  GroundHolder.h
//  PopGame
//
//  Created by Kris Temmerman on 07/05/14.
//
//

#ifndef __PopGame__GroundHolder__
#define __PopGame__GroundHolder__

#include <iostream>
#include "Sprite.h"
#include "GroundTile.h"
#include "cinder/app/AppNative.h"
class GroundHolder: public neuro::Sprite
{

public:
    GroundHolder(){}
    void setup();
    void updatePos (float speed);
   
    GroundTile tile1;
    GroundTile tile2;
    double prevTime;
    
  
};
#endif /* defined(__PopGame__GroundHolder__) */
