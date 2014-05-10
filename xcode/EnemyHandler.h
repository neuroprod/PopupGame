//
//  EnemyHandler.h
//  PopGame
//
//  Created by Kris Temmerman on 10/05/14.
//
//

#ifndef __PopGame__EnemyHandler__
#define __PopGame__EnemyHandler__

#include <iostream>
#include "Sprite.h"
#include "Enemy.h"
class EnemyHandler :public neuro::Sprite
{
public:
    EnemyHandler(){};
    void setup();
    void update(float timeEllapsed);
    
    
    
    
    
    
    void createEnemy(int type, float posX, float posY);
    
    
    
    vector <Enemy * > enemys;
    vector <Enemy * > enemysBuffer;
    



};
#endif /* defined(__PopGame__EnemyHandler__) */
