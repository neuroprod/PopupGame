//
//  TouchPoint.cpp
//  Automative
//
//  Created by Kris Temmerman on 27/03/14.
//
//

#include <TouchPoint.h>
using namespace neuro;
//TOUCH_DOWN, TOUCH_UP, TOUCH_TAP,TOUCH_UP_OUTSIDE,TOUCH_MOVE,TOUCH_OVER,TOUCH_OUT
void TouchPoint::setMove()
{
    for(int i=0;i<downTargets.size();i++)
    {
        
        bool hit =downTargets[i]->chekHitRecursive(this);
        downTargets[i]->dispatchTouchEvent(neuro::TOUCH_MOVE, this);
        if(hit)
        {
            if(!downTargets[i]->isOver){
                downTargets[i]->dispatchTouchEvent(neuro::TOUCH_OVER, this);
                downTargets[i]->isOver =true;
            }
        }else
        {
            if(downTargets[i]->isOver){
                downTargets[i]->dispatchTouchEvent(neuro::TOUCH_OUT, this);
                downTargets[i]->isOver =false;
            }
        }
        
    }
    
    // downTargets.clear();
    
};
void TouchPoint::setUp()
{
    for(int i=0;i<downTargets.size();i++)
    {
        bool hit =downTargets[i]->chekHitRecursive(this);
         downTargets[i]->dispatchTouchEvent(neuro::TOUCH_UP, this);
        if(hit)
        {
            downTargets[i]->dispatchTouchEvent(neuro::TOUCH_TAP, this);
        }else
        {
            downTargets[i]->dispatchTouchEvent(neuro::TOUCH_UP_OUTSIDE, this);
        }
        
        
    }
    
    downTargets.clear();
    
};