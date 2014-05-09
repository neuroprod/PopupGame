//
//  Image2hD.h
//  PopGame
//
//  Created by Kris Temmerman on 07/05/14.
//
//

#ifndef __PopGame__Image2hD__
#define __PopGame__Image2hD__

#include <iostream>
#include "Sprite.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/Vbo.h"
namespace neuro{
    
	class Image2hD: public Sprite
	{
        
	public:
		
       Image2hD(){};
        virtual ~Image2hD(){};
		void load(string url,string urlh  ,ci::gl::Texture::Format fmt=ci::gl::Texture::Format());
        float uStep;
        float vStep;
	
		virtual void update();
		virtual void draw();
        void makePixel(int x, int y,  unsigned char *data ,unsigned char *dataH);
        Vec4f  getPixel(int x, int y, unsigned char *data);
		bool isLoaded;
		string url;
        
		gl::Texture	texture;
        gl::VboMeshRef	mVboMesh;
        
        vector<uint32_t> indices;
        vector<Vec2f> texCoords;
         vector<Vec3f> vertices;
         vector<Vec3f> normals;
        int indicesPos;
	};
    
    
}
#endif /* defined(__PopGame__Image2hD__) */
