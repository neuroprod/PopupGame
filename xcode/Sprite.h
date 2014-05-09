#pragma once

#include "cinder/gl/gl.h"
#include "cinder/app/AppNative.h"
#include "cinder/Timeline.h"
#include "cinder/Matrix.h"

#include <iostream>
#include <vector>
#include <string>

#include "TouchEvent.h"
#include "TouchPoint.h"

using namespace std;
using namespace ci;
using namespace cinder;
using namespace gl;

namespace neuro
{

	
	//touches
	enum touchType {TOUCH_DOWN, TOUCH_UP, TOUCH_TAP,TOUCH_UP_OUTSIDE,TOUCH_MOVE,TOUCH_OVER,TOUCH_OUT};

	enum align {ALIGN_TOP_LEFT,ALIGN_CENTER,ALIGN_BOTTOM_LEFT,ALIGN_CENTER_BOTTOM,ALIGN_TOP_RIGHT,ALIGN_CENTER_TOP,ALIGN_LEFT_CENTER,ALIGN_RIGHT_CENTER};

	class TouchEvent;
    class TouchPoint;
	class Sprite
	{
	protected:
		
		
		
		float width;
		float height;
		float global_alpha;
		cinder::Matrix44f lockalMatrix;
		cinder::Matrix44f globalMatrix;
		cinder::Matrix44f mouseMatrix;
		vector<Sprite *> children;
		Sprite * parent;
		
		Rectf hitRect;

	public:
	
		Sprite()
		{
			parent =NULL;
			width =0;
			height =0;
			isAdditiveBlending =false;
			center.set(0,0,0);
		
			x=0;
			y=0;
            z=0;
			alpha =1;
			global_alpha =1;
			rotationZ  =0;
            rotationX  =0;
            rotationY  =0;
			scaleX=1;
			scaleY=1;
            scaleZ=1;
			hitRect.set(0,0,0,0);
		
			touchEnabled =true;
			touchChildren=true;
            al_int=ALIGN_TOP_LEFT;
		
		};
		
		virtual ~Sprite(){};

		virtual void update(float timeEllapsed);
		virtual void draw();
        virtual void drawHitrect();
		virtual void int_update(float timeEllapsed);
		virtual void int_draw();
        bool isOver;
		void addChild(Sprite *);
		void removeChild(Sprite *);
        void removeAllChildren();
		float getWidth()
		{
		return width;
		}
		float getHeight()
		{
		return height;
		}
	
		//touch
		void setHitRect(int width, int height);
	void setHitRectAlign(int width, int height);

		virtual bool  setTouch(TouchPoint* touchPoint );
        virtual bool chekHitRecursive(TouchPoint* touchPoint);
		virtual bool chekHit(TouchPoint* touchPoint);
		bool touchEnabled;
		bool touchChildren;
		//touchevents
		void addTouchEvent(touchType type,std::function<void( TouchEvent)>);
		void dispatchTouchEvent(touchType type,TouchPoint* touchPoint);
		vector<TouchPoint *>touchPoints;
		vector< std::pair <touchType,std::function<void (TouchEvent)> >> touchEvents;
	
		void setAlign(align al);
		void setCenter(float x, float y);
		Vec3f center;
		
		Anim<float> x;
		Anim<float> y;
        Anim<float> z;
		Anim< float> rotationX;
        Anim< float> rotationY;
        Anim< float> rotationZ;
		Anim< float> scaleX;
		Anim< float> scaleY;
        Anim< float> scaleZ;
		Anim<float> alpha;
		bool isAdditiveBlending;
        align al_int;
		int id;
	 void int_setLanguage(int currentLanguage);
        virtual void setLanguage(int currentLanguage){};
	};



}