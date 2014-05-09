#pragma once
#include "Sprite.h"
#include "TouchPoint.h"
namespace neuro
{
	class Sprite;
    class TouchPoint;
	class TouchEvent
	{
	public:
		TouchEvent(){};
		Sprite *target;
		TouchPoint *touchPoint;
        ci::Vec2f lockalPos;


	};
}