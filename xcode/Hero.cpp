//
//  Hero.cpp
//  PopGame
//
//  Created by Kris Temmerman on 07/05/14.
//
//

#include "Hero.h"
#include "BulletHandler.h"

void Hero::update(float timeEllapsed)
{
    if(isLeft) speedX+=2800*timeEllapsed;
    if(isRight) speedX-=2800*timeEllapsed;
    if(speedX>1000) speedX =1000;
    if(speedX<-1000) speedX =-1000;
    speedX *=0.95;
    rotationY = -speedX/2500;
    x =x+ speedX*timeEllapsed;
    
    
    
    if(isUp) speedY+=2800*timeEllapsed;
    if(isDown) speedY-=2800*timeEllapsed;
    if(speedY>1000) speedY =1000;
    if(speedY<-1000) speedY =-1000;
    speedY *=0.95;
  
    y =y+ speedY*timeEllapsed;
   
    
    if(y<-280) {
        speedY =0;
        y=-280 ;
    };
    if(y>400) y=400;
    if(x<-550) x=-550;
    if(x>550) x=550;
    lastShoot -=timeEllapsed;
    
    if(isShoot)
    {
        if (lastShoot<0)
        {
            BulletHandler::getInstance()->shootBullet(x.value()-6*8,y.value(),z.value(),true);
            
            BulletHandler::getInstance()->shootBullet(x.value()+5*8,y.value(),z.value(),true);
            lastShoot =0.2;
        }
    
    }
    
    
}

void Hero::setKey(int updown, int key)
{

    if(updown ==0)
    {
        if(key== 0)
        {
            isUp =true;
            isDown = false;
        
        }else if(key== 1)
        {
            isUp =false;
            isDown = true;
            
        }else  if(key== 2)
        {
            isLeft =true;
            isRight = false;
            
        }else if(key== 3)
        {
            isRight =true;
            isLeft = false;
            
        }else if(key== 4)
        {
            isShoot =true;
            
            
        }
    
    
    }
    if(updown ==1)
    {
        if(key== 0)
        {
            isUp =false;
            
        }else if(key== 1)
        {
            
            isDown = false;
            
        }else if(key== 2)
        {
            
            isLeft = false;
            
        }else if(key== 3)
        {
            
            isRight = false;
            
        }else if(key== 4)
        {
            isShoot =false;
            
            
        }
        
        
    }



}