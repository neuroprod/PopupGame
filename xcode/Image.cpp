#include "Image.h"
#include "TextureManager.h"
#include "cinder/Filesystem.h"
using namespace neuro;


void Image::load(string _url,ci::gl::Texture::Format fmt)
{
    fmt.setMagFilter(GL_NEAREST);
    scaleX = scaleY = 8;
    scaleZ = 8;
  const string temp_url = _url;

	//straitload
	url =ci::app::getAssetPath(temp_url).string();

	if(url.size()== 0)
    {
      //first try 
      string firsttry ="images/"+temp_url;
      url =ci::app::getAssetPath(firsttry ).string();
      if(url.size()!= 0)
      {
          texture  = ph::loadTexture( url,fmt);
          height =(float) texture.getHeight();
          width =(float) texture.getWidth();
          setHitRect(width , height);
          setAlign(al_int);         
       
            
        }
    
     
	
      
    }else
    {
        
        texture  = ph::loadTexture( url,fmt);
        height =(float) texture.getHeight();
        width =(float) texture.getWidth();
        setHitRect(width , height);
        setAlign(al_int);
    
    }
    gl::VboMesh::Layout layout;
	layout.setStaticIndices();
	layout.setStaticPositions();
    layout.setStaticNormals();
	layout.setStaticTexCoords2d();
	mVboMesh = gl::VboMesh::create( 4, 4, layout, GL_QUADS );
	vector<uint32_t> indices;
    indices.push_back( 0);
    indices.push_back( 1 );
    indices.push_back( 2);
    indices.push_back( 3 );
    
	vector<Vec2f> texCoords;
    texCoords.push_back( Vec2f(0,0 ) );
    texCoords.push_back( Vec2f(1,0 ) );
    texCoords.push_back( Vec2f(1,1 ) );
    texCoords.push_back( Vec2f(0,1 ) );
    
    
    vector<Vec3f> vertices;
    vertices.push_back( Vec3f(0,0 ,0) );
    vertices.push_back( Vec3f( width,0,0 ) );
    vertices.push_back( Vec3f( width,height,0 ) );
    vertices.push_back( Vec3f(0,height,0 ) );
    
    
    
    vector<Vec3f> normals;
    normals.push_back( Vec3f(0,0 ,1) );
    normals.push_back( Vec3f( 0,0,1 ) );
    normals.push_back( Vec3f( 0,0,1 ) );
    normals.push_back( Vec3f(0,0,1 ) );
    
    
    
    mVboMesh->bufferIndices( indices );
	mVboMesh->bufferTexCoords2d( 0, texCoords );
    mVboMesh->bufferPositions(vertices);
    mVboMesh->bufferNormals(normals);
}



void Image::draw()
{
   
	
	if(global_alpha==0)return;
	glColor4f(1,1,1,global_alpha);
    if(texture){
        
      	texture.enableAndBind();
        gl::draw( mVboMesh );
    }
    
	
}
