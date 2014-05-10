//
//  BulletHandler.h
//  PopGame
//
//  Created by Kris Temmerman on 07/05/14.
//
//

#ifndef __PopGame__BulletHandler__
#define __PopGame__BulletHandler__

#include <iostream>
#include "Sprite.h"
#include "Image.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Explosion.h"
#include  "EnemyHandler.h"
class BulletHandler
{

public:
    BulletHandler (){};
    void shootBullet(float x, float y, float z, bool isHero );
    static BulletHandler * getInstance();

    static BulletHandler* instance;
    neuro::Sprite * stage;
    
    void update(double timeEllapsed);
    
    void showExplosion(Shootable *);
    
    vector<Bullet *> bullets;
    vector<Bullet *> bulletBuffer;
    
    vector<Explosion *> explosions;
    vector<Explosion *> explosionBuffer;
    
    EnemyHandler * enemyHandler;
    
};

#endif /* defined(__PopGame__BulletHandler__) */
