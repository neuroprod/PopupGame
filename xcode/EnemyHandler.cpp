//
//  EnemyHandler.cpp
//  PopGame
//
//  Created by Kris Temmerman on 10/05/14.
//
//

#include "EnemyHandler.h"
void EnemyHandler::setup()
{


};
void EnemyHandler::update(float timeEllapsed)
{
    if(rand()%50==1)
    {
        createEnemy(5, rand()%1200 -600, 1400);
    
    
    
    }
    for(int i=0;i<enemys.size();i++)
    {
       
        if(enemys[i]->y<-500 || enemys[i]->lives==0)
        {
            enemysBuffer.push_back(enemys[i]);
            removeChild(enemys[i]);
            enemys.erase (enemys.begin()+i);
            i--;
            
        }else{
        
        enemys[i]->y =enemys[i]->y -400*timeEllapsed;
        }
    
    }

};



void EnemyHandler::createEnemy(int type, float posX , float posY)
{

    Enemy *en;
    
    if(enemysBuffer.size()>0)
    {
        en = enemysBuffer.back();
        enemysBuffer.pop_back();
        
    }else
    {
    
    
    
        en  =new Enemy();
  
        en->setup(type);
    }
    en->reset(posX, posY);
    addChild(en);
    enemys.push_back(en);
    


}