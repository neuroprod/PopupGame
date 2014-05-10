//
//  BulletHandler.cpp
//  PopGame
//
//  Created by Kris Temmerman on 07/05/14.
//
//

#include "BulletHandler.h"

#include "Enemy.h"


void BulletHandler::shootBullet(float x, float y, float z, bool isHero )
{
    Bullet *b;
    if( bulletBuffer.size()==0){

        b =new Bullet();
       
        b->setup();
        
    }else
    {
    
        b = bulletBuffer.back();
        bulletBuffer.pop_back();
        b->alpha =1;
    }
    
    b->x = x;
    b->y = y;
    b->z = z;
    stage->addChild(b);
    bullets.push_back(b);
}
void BulletHandler::update(double timeEllapsed)
{
   
    
    for(int i=0;i<bullets.size();i++)
    {
        
        if(bullets[i]->y >900) {
           
            bulletBuffer.push_back(bullets[i]);
            stage->removeChild(bullets[i]);
            bullets.erase (bullets.begin()+i);
           
            continue;
        }
        bullets[i]->y =bullets[i]->y +1400*timeEllapsed;
        
        Vec2f posB = Vec2f(bullets[i]->x ,bullets[i]->y );
        
        
        for(int j=0;j<enemyHandler->enemys.size();j++)
        {
        
            Enemy * en  =enemyHandler->enemys[j];
            if(en->chekBulletHit(posB))
            {
                
                showExplosion(en);
              
                  stage->removeChild(bullets[i]);
                bulletBuffer.push_back(bullets[i]);
                bullets.erase (bullets.begin()+i);
               
                break;
        
            };
        }
    
    }
    for(int i=0;i< explosions.size();i++)
    {
        explosions[i]->y =explosions[i]->y -timeEllapsed *1000;
        if(explosions[i]->frame ==10)
        {
            explosionBuffer.push_back(explosions[i]);
            stage->removeChild(explosions[i]);
            explosions.erase (explosions.begin()+i);

        
        }
    }

}

void BulletHandler::showExplosion(Shootable * en)
{
    {
        Explosion *b;
    if( explosionBuffer.size()==0){
        
      
        b=new Explosion();
        b->setup();
        
    }else
    {
        
        b = explosionBuffer.back();
        explosionBuffer.pop_back();
        b->reset();
    }

   
    b->x = en->x;
    b->y = en->y;
    b->z = en->z;
   
    stage->addChild(b);
    explosions.push_back(b);

    }
    
   

}

BulletHandler*  BulletHandler::instance = NULL;


BulletHandler* BulletHandler::getInstance(){
    if(instance == NULL)
    {
        instance = new BulletHandler();
    }
    
    return instance;
}