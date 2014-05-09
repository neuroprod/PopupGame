#pragma once
#include "Sprite.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/Vbo.h"
namespace neuro{

	class Image: public Sprite
	{

	public:
		
        Image(){};
        	virtual ~Image(){};
		void load(string url ,ci::gl::Texture::Format fmt=ci::gl::Texture::Format());

		bool hasTexture(string textureID);
		//void setTexture(string textureID,gl::Texture _texture);
	
		virtual void draw();

		bool isLoaded;
		string url;
	
		gl::Texture	texture;
        gl::VboMeshRef	mVboMesh;
    

    
	};


}
