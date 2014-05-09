//
//  Explosion.h
//  PopGame
//
//  Created by Kris Temmerman on 09/05/14.
//
//

#ifndef __PopGame__Explosion__
#define __PopGame__Explosion__
#include "Image.h"
#include "Sprite.h"
class Explosion :public neuro::Sprite
{
    
    
public:
    Explosion(){};
    void setup();
    void update(float timeEllapsed);
    vector<neuro::Image * > images;
    void reset();
    
    float time;
    int frame;
};

#endif /* defined(__PopGame__Explosion__) */
