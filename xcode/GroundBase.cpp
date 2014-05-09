//
//  GroundBase.cpp
//  PopGame
//
//  Created by Kris Temmerman on 07/05/14.
//
//

#include "GroundBase.h"

#include "TextureManager.h"
#include "cinder/Filesystem.h"


void GroundBase::setup(float realY)
{
        //ci::app::getAssetPath("floor.png").string();
  
  
    
    texture  = ph::loadTexture(  ci::app::getAssetPath("floor.png").string());
    height =(float) texture.getHeight();
    width =(float) texture.getWidth();
    setHitRect(width , height);
    setAlign(al_int);
    vector<uint32_t> indices;
    vector<Vec2f> texCoords;
    vector<Vec3f> vertices;
    vector<Vec3f> normals;
    int indicesPos =0;
    float step=10;
    float nScale=180.1;
   float mScale=-40;
    int mMod=10;
    float nFactor =10;
    float minZ =-4;
    for(int x=0;x <100;x++)
    {
        for(int y=0;y<100;y++)
        {
            
            indices.push_back( indicesPos++);
            indices.push_back( indicesPos++);
            indices.push_back( indicesPos++);
            indices.push_back( indicesPos++ );
            
           
            
            float xp =x*step ;
            float yp=y*step;
            
            float zp=pNoise->noise (xp/nScale, (yp+realY)/nScale)*nFactor;
            
            if(zp<minZ) zp=minZ;
            Vec3f p1 =Vec3f(xp,yp,(int)zp%mMod *mScale );
            vertices.push_back( p1 );
            
            
            xp =x*step+step ;
            yp=y*step;
            zp=pNoise->noise (xp/nScale,(yp+realY)/nScale)*nFactor;
            
           if(zp<minZ) zp=minZ;
            
            
            Vec3f p2 =Vec3f(xp,yp,(int)zp%mMod *mScale);
            vertices.push_back( p2);
            
            xp =x*step +step;
            yp=y*step+step;
            
            
            zp=pNoise->noise (xp/nScale, (yp+realY)/nScale)*nFactor;
            
            if(zp<minZ) zp=minZ;
            Vec3f p3 =Vec3f(xp,yp,(int)zp%mMod*mScale);
            vertices.push_back( p3);
            
            xp =x*step ;
            yp=y*step+step;
            zp=pNoise->noise (xp/nScale, (yp+realY)/nScale)*nFactor;
            if(zp<minZ) zp=minZ;
            Vec3f p4 =Vec3f(xp,yp,(int)zp%mMod *mScale );
            vertices.push_back( p4 );
          
            
            float u =(float)((int)zp%mMod +4)/mMod ;
            float v =(float) (rand()%100)/100.0f;
            texCoords.push_back( Vec2f(u,v ) );
            //texCoords.push_back( Vec2f(u,v ) );
            //texCoords.push_back( Vec2f(u,v ) );
            //texCoords.push_back( Vec2f(u,v ) );
           texCoords.push_back( Vec2f(u+0.01,v ) );
            texCoords.push_back( Vec2f(u+0.01,v+0.01 ) );
            texCoords.push_back( Vec2f(u,v+0.01 ) );
            
            
            Vec3f n1 =p2-p1;
            Vec3f n2 =p4-p1;
           
        
            Vec3f n = n1.cross(n2);
         
            n.normalize();
            
            
       
            normals.push_back( n );
            normals.push_back( n );
            normals.push_back( n );
            normals.push_back( n );
        }
        
    }
  
    
  
    
    gl::VboMesh::Layout layout;
	layout.setStaticIndices();
	layout.setStaticPositions();
    layout.setStaticNormals();
	layout.setStaticTexCoords2d();
    
    
    
	mVboMesh = gl::VboMesh::create( indices.size(), indices.size(), layout, GL_QUADS );
	
    
    
    
    mVboMesh->bufferIndices( indices );
	mVboMesh->bufferTexCoords2d( 0, texCoords );
    mVboMesh->bufferPositions(vertices);
    mVboMesh->bufferNormals(normals);



};

void GroundBase::draw()
{
  

	if(global_alpha==0)return;
	glColor4f(1,1,1,global_alpha);
    if(texture){
        
      	texture.enableAndBind();
        gl::draw( mVboMesh );
    }
    

}