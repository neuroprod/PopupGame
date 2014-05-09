//
//  GroundTile.cpp
//  PopGame
//
//  Created by Kris Temmerman on 07/05/14.
//
//

#include "GroundTile.h"
void GroundTile::setup()
{
    pNoise =new Perlin();
  
    recalculate();
}
void GroundTile::recalculate()
{
    
    for (int i = 0; i < children.size(); ++i) {
        delete children[i]; // Calls ~object and deallocates *tmp[i]
        children[i] =nullptr;
    }
    children.clear();
    
    baseG =new GroundBase();
    baseG->pNoise = pNoise;
    baseG->setup(realY);
    addChild(baseG);
    
    
 
    
    
  /*  for(int i=0;i<20;i++)
    {
        neuro::Image *t=new neuro::Image ();
        t->load("three.png");
        t->setAlign(neuro::ALIGN_CENTER);
      
        t->x = rand()%500 ;
        t->y = rand()%500;
        t->z =-rand()%500;
       addChild(t );
    }*/
   
}