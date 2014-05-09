#include "Sprite.h"

using namespace neuro;

void Sprite::update(float timeEllapsed)
{
	//overwrite
}
void Sprite::draw()
{
		//overwrite
}
void Sprite::removeAllChildren()
{
    
   



}
void Sprite::addChild(Sprite *child)
{
		child->parent  =this;
		children.push_back(child);
}
void Sprite::removeChild(Sprite * child)
{
	std::vector<Sprite *>::iterator it = std::find(children.begin(),children.end(), child);
	if (it != children.end()) 
	{
			child->parent =NULL;
			children.erase (it);
	}
	
}

void Sprite::int_update(float timeEllapsed)
{
	
	lockalMatrix.setToIdentity();
		
	lockalMatrix.translate(Vec3f(x,y,z));
	if(scaleX != 1 || scaleY != 1|| rotationY != 0 || rotationX != 0 || rotationZ != 0 || scaleZ != 0)
	{
			globalMatrix.translate( center);
            lockalMatrix.rotate(Vec3f(1,0,0),rotationX);
            lockalMatrix.rotate(Vec3f(0,1,0),rotationY);
			lockalMatrix.rotate(Vec3f(0,0,1),rotationZ);
			lockalMatrix.scale(Vec3f(scaleX,scaleY,scaleZ));
			globalMatrix.translate( -center);
	}

	if(!parent)
	{
		globalMatrix.set(&lockalMatrix.m[0]);
		global_alpha =alpha;
	}
	else 
	{
		global_alpha =parent->global_alpha *alpha;
		globalMatrix =  parent->globalMatrix *lockalMatrix;
	}

		
		
	for(int i=0;i<children.size();i++)
    {
    children[i]->int_update(timeEllapsed);
    
    }

	/*for(std::vector< Sprite *>::iterator it = children.begin(); it != children.end(); ++it) {
			(*it)->int_update(timeEllapsed);
	}*/
	globalMatrix.translate( -center);

	
		
	/*
		mouseRect.set(global_x ,global_y,global_x+width*global_scale,global_y+height*global_scale);
	*/


	update(timeEllapsed);
}

	void Sprite::int_draw()
	{

		if(global_alpha==0) return;
	
		gl::pushMatrices();
		gl::multModelView(globalMatrix );


		if(isAdditiveBlending){
            glEnable(GL_BLEND);
            gl::enableAdditiveBlending();
        }
		draw();
        //drawHitrect();
		if(isAdditiveBlending)glDisable(GL_BLEND);;
		gl::popMatrices();

		for(std::vector< Sprite *>::iterator it = children.begin(); it != children.end(); ++it) 
		{
			(*it)->int_draw();
		}
	}
    void Sprite::int_setLanguage(int currentLanguage)
    {
        setLanguage(currentLanguage);
        for(std::vector< Sprite *>::iterator it = children.begin(); it != children.end(); ++it)
		{
			(*it)->int_setLanguage(currentLanguage);
		}
    }



    void Sprite::drawHitrect()
    {
        if(touchEnabled)
        gl::drawStrokedRect(hitRect);
    }




	bool Sprite::setTouch(TouchPoint* touchPoint )
	{
		
        
        if(alpha==0) return false;
		if(touchEnabled== false) return false;
      
		bool hit =false;
		if(touchChildren)
		{
			if(children.size()>=1)
			{
				for(int i=(children.size()-1);i >= 0;i--)
				{
					if(	children[i]->setTouch( touchPoint ))
					{
						hit =true;
						break;
					}
	
				}
			}
		}
		if(!hit)
		{
			hit = chekHit(touchPoint);
		}
	
 

		if(touchEvents.size())
		{
			
            if(hit)
			{
                
				if(touchPoint->type==neuro::TOUCH_POINT_DOWN)
				{
				
                    touchPoint->downTargets.push_back(this);
					dispatchTouchEvent(TOUCH_DOWN,touchPoint);
                    isOver =true;
		
				}
				
			}
			
		}

		return hit;

	}
bool Sprite::chekHitRecursive(TouchPoint* touchPoint)
{
    if(alpha==0) return false;
    if(touchEnabled== false) return false;
    
    bool hit =false;
     hit = chekHit(touchPoint);
    if(hit) return true;
    
    if(touchChildren)
    {
        if(children.size()>=1)
        {
            for(int i=(children.size()-1);i >= 0;i--)
            {
                if(	children[i]->chekHitRecursive( touchPoint ))
                {
                    hit =true;
                    break;
                }
                
            }
        }
    }
 
	return hit;
	
    
}
	bool Sprite::chekHit(TouchPoint* touchPoint)
	{
        mouseMatrix = globalMatrix.affineInverted();
		Vec4f touchLocal = mouseMatrix.postMultiply(Vec4f(touchPoint->x,touchPoint->y,0,1));
		
		return hitRect.contains(Vec2f(touchLocal.x,touchLocal.y));
	
		
	}

	void  Sprite::setHitRect(int w, int h)
	{
		hitRect.set(0,0,w,h);
	
	}
void  Sprite::setHitRectAlign(int w, int h)
{
    hitRect.set(-w/2+center.x,-h/2+center.y,w/2+center.x,h/2+center.y);
	
}
	void Sprite::addTouchEvent(touchType type,std::function<void (TouchEvent) > funct)
	{
		touchEvents.push_back(std::pair<touchType,std::function<void (TouchEvent) >>(type, funct));
	}

	 void Sprite::dispatchTouchEvent(touchType type,TouchPoint* touchPoint)
	{
		TouchEvent t;
		t.target = this;
		t.touchPoint = touchPoint;
         mouseMatrix = globalMatrix.affineInverted();
        Vec4f touchLocal = mouseMatrix.postMultiply(Vec4f(touchPoint->x,touchPoint->y,0,1));
        t.lockalPos.x = touchLocal.x;
        t.lockalPos.y = touchLocal.y;
		for(int i=0;i<touchEvents.size();i++ )
		{
			if(touchEvents[i].first ==type )touchEvents[i].second(t);
		}
		

	}
	
	



void Sprite::setCenter(float x,float y)
{
		center.x = x;
		center.y = y;
}
void Sprite::setAlign(align al)
{
    al_int =al;
	if(al==ALIGN_CENTER)
	{
		center.x =(int) width/2;
		center.y = (int)height/2;
	}else if(al==ALIGN_LEFT_CENTER)
	{
		center.x =0;
		center.y = (int)height/2;
	}else if(al==ALIGN_TOP_LEFT)
	{
		center.x =0;
		center.y = 0;
	}else if(al==ALIGN_RIGHT_CENTER)
	{
		center.x =(int)width;
		center.y = (int)height/2;
	}else if(al==ALIGN_CENTER_BOTTOM)
    {
    	center.x =(int)width/2;
		center.y = (int)height;
    
    }else if(al==ALIGN_CENTER_TOP)
    {
    	center.x =(int)width/2;
		center.y = 0;
        
    }else if(al== ALIGN_BOTTOM_LEFT)
    {
        center.x =0;
		center.y = (int)height;
    }else if(al== ALIGN_TOP_RIGHT)
    {
    	center.x =(int) width;
		center.y = 0;
    }
    else
	{
	
		ci::app::console()<< "implement Align "<< al <<endl;
	}

}