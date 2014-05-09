#pragma once
#include <vector>
#include "Sprite.h"
namespace neuro
{
	enum touchPointType {TOUCH_POINT_DOWN, TOUCH_POINT_UP, TOUCH_POINT_MOVE};
    class Sprite;
	class TouchPoint: public ci::Vec2f{
	public:
		// id is a string because it includes the source
		std::string id;

	
		touchPointType type;
		
		TouchPoint(){};
		bool change;
        std::vector<neuro::Sprite *> downTargets;
        
        //TOUCH_DOWN, TOUCH_UP, TOUCH_TAP,TOUCH_UP_OUTSIDE,TOUCH_MOVE,TOUCH_OVER,TOUCH_OUT
        void setMove();
		void setUp();
	};
}