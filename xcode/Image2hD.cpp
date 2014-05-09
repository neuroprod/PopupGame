//
//  Image2hD.cpp
//  PopGame
//
//  Created by Kris Temmerman on 07/05/14.
//
//

#include "Image2hD.h"
#include "TextureManager.h"
#include "cinder/Filesystem.h"
using namespace neuro;


void Image2hD::load(string _url,string _urlh,ci::gl::Texture::Format fmt)
{
    fmt.setMagFilter(GL_NEAREST);
    scaleZ =8;
    scaleX =8;
     scaleY =8;
	//straitload
	url =ci::app::getAssetPath(_url).string();
   string  urlh =ci::app::getAssetPath(_urlh).string();
	   
        texture  = ph::loadTexture( url,fmt);
        height =(float) texture.getHeight();
        width =(float) texture.getWidth();
        setHitRect(width , height);
        setAlign(al_int);
        
   
    uStep =1.0f/width;
     vStep =1.0f/height;
     Surface k= Surface( loadImage(loadFile(url) ) );
    unsigned char *data =   k.getData();
    
    Surface kh= Surface( loadImage(loadFile(urlh) ) );
    unsigned char *datah =   kh.getData();
    
   indicesPos =0;
   
    for(int x=0;x <width;x++)
    {
        for(int y=0;y<height;y++)
        {
            makePixel (x,y,data,datah);
        
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
}
void Image2hD::makePixel(int x, int y,  unsigned char *data,  unsigned char *dataH)
{
    Vec4f color  =  getPixel(x,y,  data);
    if(color.w ==0)return;
    
    
    
    float u= x*uStep;
    float v=y*vStep;
    
    Vec4f colorH  =  getPixel(x,y,  dataH);
 
    
    indices.push_back( indicesPos++);
    indices.push_back( indicesPos++);
    indices.push_back( indicesPos++);
    indices.push_back( indicesPos++ );
    
	
    texCoords.push_back( Vec2f(u,v ) );
    texCoords.push_back( Vec2f(u+ uStep,v ) );
    texCoords.push_back( Vec2f(u+uStep,v+vStep ) );
    texCoords.push_back( Vec2f(u,v+vStep ) );
    
    int h = -colorH.x /255 *6;
    
    vertices.push_back( Vec3f(0+x,0+y ,h) );
    vertices.push_back( Vec3f( 1+x,0+y,h ) );
    vertices.push_back( Vec3f(1+x,1+y,h ) );
    vertices.push_back( Vec3f(0+x,1+y,h ) );
    
    
    
    
    normals.push_back( Vec3f(0,0 ,1) );
    normals.push_back( Vec3f( 0,0,1 ) );
    normals.push_back( Vec3f( 0,0,1 ) );
    normals.push_back( Vec3f(0,0,1 ) );
    
    
    
    Vec4f colorFront   =  getPixel(x,y-1,  data);
      Vec4f hightFront   =  getPixel(x,y-1,  dataH);
    if(colorFront.w==0 ||hightFront.x<colorH.x)
    {
        
        float h2;
        
        if( colorFront.w ==0)
        {
        
            
            h2=h+1;
        
        }else
        {
        
            int hs2 = -hightFront.x /255 *6;
            h2 = hs2-h;
        
        }
        
        indices.push_back( indicesPos++);
        indices.push_back( indicesPos++);
        indices.push_back( indicesPos++);
        indices.push_back( indicesPos++ );
        
        
        texCoords.push_back( Vec2f(u,v ) );
        texCoords.push_back( Vec2f(u+ uStep,v ) );
        texCoords.push_back( Vec2f(u+uStep,v+vStep ) );
        texCoords.push_back( Vec2f(u,v+vStep ) );
        
       
        
        vertices.push_back( Vec3f(0+x,y ,h) );
        vertices.push_back( Vec3f( 1+x,y,h ) );
        vertices.push_back( Vec3f(1+x,y,h +h2) );
        vertices.push_back( Vec3f(0+x,y,h +h2) );
        
        
        
        
        normals.push_back( Vec3f(0,1 ,0) );
        normals.push_back( Vec3f( 0,1,0 ) );
        normals.push_back( Vec3f( 0,1,0 ) );
        normals.push_back( Vec3f(0,1,0 ) );
    
    }
    
    Vec4f colorRight   =  getPixel(x+1,y,  data);
    hightFront   =  getPixel(x+1,y,  dataH);
    if(colorRight.w==0 ||hightFront.x<colorH.x )
    {
        
        float h2;
        
        if( colorRight.w ==0)
        {
            
            
            h2=h+1;
            
        }else
        {
            
            int hs2 = -hightFront.x /255 *6;
            h2 = hs2-h;
            
        }

        indices.push_back( indicesPos++);
        indices.push_back( indicesPos++);
        indices.push_back( indicesPos++);
        indices.push_back( indicesPos++ );
        
        
        texCoords.push_back( Vec2f(u,v ) );
        texCoords.push_back( Vec2f(u+ uStep,v ) );
        texCoords.push_back( Vec2f(u+uStep,v+vStep ) );
        texCoords.push_back( Vec2f(u,v+vStep ) );
        
        
        
        vertices.push_back( Vec3f(1+x,y ,h) );
        vertices.push_back( Vec3f( 1+x,y+1,h ) );
        vertices.push_back( Vec3f(1+x,y+1,h +h2) );
        vertices.push_back( Vec3f(1+x,y,h +h2) );
        
        
        
        
        normals.push_back( Vec3f(1,0 ,0) );
        normals.push_back( Vec3f( 1,0,0 ) );
        normals.push_back( Vec3f( 1,0,0 ) );
        normals.push_back( Vec3f(1,0,0 ) );
        
    }
    
    Vec4f colorLeft  =  getPixel(x-1,y,  data);
     hightFront   =  getPixel(x-1,y,  dataH);
    if(colorLeft.w==0||hightFront.x<colorH.x)
    {
        
        float h2;
        
        if( colorLeft .w ==0)
        {
            
            
            h2=h+1;
            
        }else
        {
            
            int hs2 = -hightFront.x /255 *6;
            h2 = hs2-h;
            h2*=-1;
            
        }
        
        indices.push_back( indicesPos++);
        indices.push_back( indicesPos++);
        indices.push_back( indicesPos++);
        indices.push_back( indicesPos++ );
        
        
        texCoords.push_back( Vec2f(u,v ) );
        texCoords.push_back( Vec2f(u+ uStep,v ) );
        texCoords.push_back( Vec2f(u+uStep,v+vStep ) );
        texCoords.push_back( Vec2f(u,v+vStep ) );
        
        int h = 0;//-rand()%30;
        
        vertices.push_back( Vec3f(x,y ,h) );
        vertices.push_back( Vec3f( x,y+1,h ) );
        vertices.push_back( Vec3f(x,y+1,h +h2) );
        vertices.push_back( Vec3f(x,y,h +h2) );
        
        
        
        
        normals.push_back( Vec3f(-1,0 ,0) );
        normals.push_back( Vec3f( -1,0,0 ) );
        normals.push_back( Vec3f(- 1,0,0 ) );
        normals.push_back( Vec3f(-1,0,0 ) );
        
    }

}
Vec4f  Image2hD::getPixel(int x, int y,  unsigned char *data)
{
   
    Vec4f color;
    if(x<0  || x>=width || y<0  || y>=width)
    {
        color.set(0, 0, 0, 0);
        return color;
    
    }
    int pos = (x+y*width)*4;
    color.x = data[pos];
    color.y = data[pos+1];
    color.z = data[pos+2];
    color.w = data[pos+3];
    return color;


}

void Image2hD::update()
{
    
    //overwrite
}
void Image2hD::draw()
{
    
	
	if(global_alpha==0)return;
	glColor4f(1,1,1,global_alpha);
    if(texture){
        
      	texture.enableAndBind();
        gl::draw( mVboMesh );
    }
    
	
}
