//
//  GroundHolder.cpp
//  PopGame
//
//  Created by Kris Temmerman on 07/05/14.
//
//

#include "GroundHolder.h"
void GroundHolder::setup()
{
    scaleX =scaleY =8;
    z= 400;
    x =0;
    tile1.realY =0;
     tile1.y = 500;
     tile2.realY = -1000;
    tile2.y = -500;
    tile1.x = -500;
    tile2.x = -500;
    tile1.setup();
    tile2.setup();
    addChild(&tile1);
    addChild(&tile2);
    prevTime =cinder::app::getElapsedSeconds();
     
}
void GroundHolder::updatePos (float speed)
{
    double now = cinder::app::getElapsedSeconds();
    double timeElapsed = now-prevTime;
    prevTime =now;
    tile1.y = tile1.y  -speed*timeElapsed;
    tile2.y = tile2.y  -speed*timeElapsed;
 
    if( tile1.y<-1100){
        
        tile1.y =tile1.y +2000;
        tile1.realY +=2000;
        tile1.recalculate();
    
    }
    if( tile2.y<-1100){
        tile2.y =tile2.y +2000;
         tile2.realY +=2000;
        tile2.recalculate();
    }
}