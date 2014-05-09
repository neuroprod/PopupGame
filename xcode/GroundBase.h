//
//  GroundBase.h
//  PopGame
//
//  Created by Kris Temmerman on 07/05/14.
//
//

#ifndef __PopGame__GroundBase__
#define __PopGame__GroundBase__


#include "Sprite.h"

#include "cinder/gl/Texture.h"
#include "cinder/gl/Vbo.h"
#include "cinder/Perlin.h"
class GroundBase: public neuro::Sprite
{

public:
    Perlin *pNoise;
    GroundBase(){};
    virtual ~GroundBase()
    {
    
    
    };
    void setup(float realY);
    virtual void draw();

    gl::Texture	texture;
    gl::VboMeshRef	mVboMesh;




};

#endif /* defined(__PopGame__GroundBase__) */
