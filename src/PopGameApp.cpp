#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Sprite.h"
#include "Image.h"

#include "cinder/Camera.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/Material.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/Light.h"
#include "cinder/ip/Hdr.h"

#include "GroundHolder.h"
#include "Image2hD.h"
#include "Hero.h"
#include "Enemy.h"
#include "BulletHandler.h"

#include "EnemyHandler.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace neuro;

class PopGameApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );
    void keyDown(KeyEvent event);
    void keyUp(KeyEvent event);
	void update();
	void draw();
    
    CameraPersp			*mCamera;
    
    Sprite stage;
   Sprite stage2D;
    Hero *plane;
     Enemy *plane2;
    Image *logo;
    
    gl::GlslProg		mShader;
    gl::Fbo				mDepthFbo;
    gl::Light			*mLight;
    void initShadowMap();
	void updateShadowMap();
    
    
    EnemyHandler enemyHandler;
    GroundHolder groundHolder;
    double prevTime;
    
    
    float speed2;
};


static const int SHADOW_MAP_RESOLUTION = 512*4;



void PopGameApp::setup()
{
    
   
    
    speed2 =3.5;
    setWindowSize(1920,1080);
    //setWindowSize(1080/2,1920/2);
    setWindowPos(0, 0);
	mCamera = new CameraPersp( getWindowWidth(), getWindowHeight(), 45.0f );
	mCamera->lookAt( Vec3f( 0, -300, -400 ), Vec3f( 0, 0, 50 ) );
	mCamera->setPerspective( 80.0f, getWindowAspectRatio(),200.0f, 4000.0f );

    
    mLight = new gl::Light( gl::Light::POINT, 0 );
  
	mLight->lookAt( Vec3f(1000,-1000, -2000 ), Vec3f( 0, 1000, 0 ) );
    mLight->setShadowParams(60.0f,2000.f, 3500.0f );
	mLight->update( *mCamera );
	mLight->enable();
    

    
  
    mShader = gl::GlslProg( loadAsset("shadowMap_vert.glsl"),loadAsset("shadowMap_frag.glsl") );
    
	mShader.bind();
	mShader.uniform( "depthTexture", 1 );
    mShader.uniform( "difTexture", 0 );
    mShader.unbind();
    
     initShadowMap();
    
   
   
    groundHolder.setup();
    stage.addChild(&groundHolder);
    
    enemyHandler.setup();
    stage.addChild(&enemyHandler);
    BulletHandler::getInstance()->enemyHandler =&enemyHandler;
   
    
    
    
    plane =new Hero();
    plane->load("plane.png","planeh.png");
    plane->setAlign(neuro::ALIGN_CENTER);
    
    plane->z = 0;
   
   
    
 
    
     stage.addChild(plane);
    prevTime = cinder::app::getElapsedSeconds();
    
    BulletHandler::getInstance()->stage =&stage;
    
    
    logo =new Image();
    logo->load("logo.png");
  // logo->rotationX =-3.1415;
    logo->setAlign(neuro::ALIGN_BOTTOM_LEFT);
    logo->x =0;
    logo->y =1080*2;
    //logo->scaleX =logo->scaleY =logo->scaleZ =4;
    stage2D.scaleX=stage2D.scaleY =0.5;
    stage2D.addChild(logo);
    
}
void PopGameApp::initShadowMap()
{
    cinder::gl::Fbo::Format m;
    
	mDepthFbo = gl::Fbo( SHADOW_MAP_RESOLUTION, SHADOW_MAP_RESOLUTION, false, false, true );
   
	mDepthFbo.bindDepthTexture();
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
}
void PopGameApp::updateShadowMap()
{
    
	mDepthFbo.bindFramebuffer();
    
	glPolygonOffset( 1.0f, 1.0f );
	glEnable( GL_POLYGON_OFFSET_FILL );
	glClear( GL_DEPTH_BUFFER_BIT );
    
	glPushAttrib( GL_VIEWPORT_BIT );
	glViewport( 0, 0, SHADOW_MAP_RESOLUTION, SHADOW_MAP_RESOLUTION );
    
	gl::pushMatrices();
     mLight->setShadowRenderMatrices();
	  stage.int_draw();
   	gl::popMatrices();
    
	glPopAttrib();
    
	glDisable( GL_POLYGON_OFFSET_FILL );
    
	mDepthFbo.unbindFramebuffer();
}

void PopGameApp::mouseDown( MouseEvent event )
{

}

void PopGameApp::update()
{
    
    
    double now = cinder::app::getElapsedSeconds();
    double timeElapsed = now-prevTime;
    prevTime =now;
    
    
    
    groundHolder.updatePos(100);
    enemyHandler.update(timeElapsed);
    
  
   BulletHandler::getInstance()->update(timeElapsed);
    
    
    stage.int_update(timeElapsed );
    stage2D.int_update(timeElapsed);

}
void PopGameApp::keyDown(KeyEvent event)
{
    if(event.getCode () == KeyEvent::KEY_UP)
    {
        plane->setKey(0,0);
    
    }else if(event.getCode () == KeyEvent::KEY_DOWN)
    {
        plane->setKey(0,1);
        
    }else if(event.getCode () == KeyEvent::KEY_LEFT)
    {
        plane->setKey(0,2);
        
    }else if(event.getCode () == KeyEvent::KEY_RIGHT)
    {
        plane->setKey(0,3);
        
    }else if(event.getCode () == KeyEvent::KEY_SPACE)
    {
        plane->setKey(0,4);
        
    }


}
void PopGameApp::keyUp(KeyEvent event)
{
    if(event.getCode () == KeyEvent::KEY_UP)
    {
        plane->setKey(1,0);
        
    }else if(event.getCode () == KeyEvent::KEY_DOWN)
    {
        plane->setKey(1,1);
        
    }else if(event.getCode () == KeyEvent::KEY_LEFT)
    {
        plane->setKey(1,2);
        
    }else if(event.getCode () == KeyEvent::KEY_RIGHT)
    {
        plane->setKey(1,3);
        
    }else if(event.getCode () == KeyEvent::KEY_SPACE)
    {
        plane->setKey(1,4);
        
    }


}
void PopGameApp::draw()
{
    if(getElapsedFrames()>200)return;
    
    gl::pushMatrices();
    
    
    gl::setMatrices( *mCamera );
    gl::enable(GL_DEPTH_TEST);
   
    gl::clear(ColorA(0.5,0.5,0.5,1));
 gl::enableDepthWrite();
	glEnable( GL_LIGHTING );
	updateShadowMap();
    
	gl::enableDepthRead();
	// clear out the window with black
    glEnable( GL_TEXTURE_2D );
 
    
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.5);
	mShader.bind();
	mDepthFbo.bindDepthTexture(1);

  
	mShader.uniform( "shadowTransMatrix", mLight->getShadowTransformationMatrix( *mCamera ) );
    //gl::enable(GL_BLEND);
  	mLight->update( *mCamera );
    
    gl::pushMatrices();
    stage.int_draw();
    gl::popMatrices();
    
    
    
    gl::popMatrices();
   // gl::setMatrices( *mCamera );
    
    mShader.unbind();
    
    gl::disable (GL_DEPTH_TEST);
glDisable( GL_LIGHTING );
    glDisable (GL_ALPHA_TEST);
   glEnable(GL_BLEND);
    gl::enableAlphaBlending();
    
    stage2D.int_draw();
    glDisable(GL_BLEND);
    gl::disableAlphaBlending();
    
   
    
/*
    glDisable( GL_LIGHTING );
     
    gl::setMatricesWindow( getWindowSize() );
    Surface32f shadowMapSurface( mDepthFbo.getDepthTexture() );
    ip::hdrNormalize( &shadowMapSurface );
    gl::color( Color::white() );
    gl::draw( gl::Texture( shadowMapSurface ), Rectf( 0, 0, 128*2, 128*2 ) );
*/
}

CINDER_APP_NATIVE( PopGameApp, RendererGl )

