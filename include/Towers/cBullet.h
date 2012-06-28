#ifndef BULLET_H
#define BULLET_H

#include "../cSpriteObj.h"
#include "../Enemies/cEnemy.h"
//#include "cTower.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include "../cPlayer.h"

class Tower;

//Not used currently
//#include "cTower.h"

class Bullet: public SpriteObj
{
    public:
        Bullet();

        virtual ~Bullet(){}

        void setTarget(Enemy *target);
        inline void setDamage(int damage) { m_damage = damage; }
        inline void setSpeed(float speed) { m_speed = speed; }
        inline void setTower(Tower *source){ m_source = source; }
        inline int getDamage(){return m_damage;}
        inline float getSpeed(){return m_speed;}
        virtual void nextFrame();
        bool checkCollision();
        void navigate();
        virtual void Draw(Application &App);
        inline bool hasTarget(){return (m_target != NULL);}
        inline bool hasHit(){return m_hit;}
        Tower * getTower(){return m_source;}

    protected:
    private:
    Enemy *m_target;
    Tower *m_source;
    int m_damage;
    float m_speed;
    bool m_hit;
    bool m_targetdead;

};
#endif // BULLET_H
