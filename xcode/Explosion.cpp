//
//  Explosion.cpp
//  PopGame
//
//  Created by Kris Temmerman on 09/05/14.
//
//

#include "Explosion.h"
#include "cinder/Utilities.h"

void Explosion::setup()
{
    for(int i=1;i<11;i++)
    {
        neuro::Image *im =new neuro::Image();
       // im->isAdditiveBlending =true;
        
        string file ="explosion" + toString(i)+".png";
        im->load(file);
        im->alpha =0;
        im->setAlign(neuro::ALIGN_CENTER);
        addChild(im);
        images.push_back(im);
    
    }
    
  
   // rotationX = -3.1415/2;
    
    reset();
}
void Explosion::reset()
{
    frame =0;
    time =0.03;
 images[0]->alpha =1;

}
void Explosion::update(float timeEllapsed)
{
    
    time-=timeEllapsed;
    if(time<0){
        time += 0.03;
    
    frame++;
        if(frame>=images.size()) frame =10;
    
    for(int i=0;i<10;i++)
    {
        if(i==frame)
        {
            images[i]->alpha =1;
        }else
        {
            images[i]->alpha =0;
        
        }
        
    }
    }
    
}