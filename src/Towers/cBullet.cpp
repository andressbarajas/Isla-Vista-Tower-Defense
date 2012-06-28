#include "../../include/Towers/cBullet.h"
#include "../../include/Towers/cTower.h"
#include <cmath>

Bullet::Bullet() {
    m_target = NULL;
}

void Bullet::setTarget(Enemy *target){
    m_target = target;
    m_hit = false;

}
void Bullet::nextFrame(){

    if(m_target == NULL || m_target->isDead()) {
        m_target = NULL;
        SetPosition(m_source->GetPosition());
        return;
    }


    //move bullet toward enemy (rotation if needed)
    navigate();
    //check if bullet collided with enemy
    if(checkCollision())
    {
        m_target->takeDamage(m_damage);
        if(m_target->isDead()) {
            Player &player = Player::GetInstance();
            player.increaseMoney(3);
            m_targetdead = true;
            m_target = NULL;
        }

        //m_targetdead = false;

        //animation splash logic
        m_hit = true;
        SetPosition(m_source->GetPosition()); //.x + 16, m_source->GetPosition().y + 16);
    }

}

void Bullet::navigate(){

    float movex = 0;
    float movey = 0;
    float xdif = 0;
    float ydif = 0;

    // If it did not collide with the enemy, move it
    if(!checkCollision() && (m_target != NULL) && (!m_target->isDead())&&!m_hit)
    {
        xdif = m_target->GetPosition().x - GetPosition().x;
        ydif = m_target->GetPosition().y - GetPosition().y;
        movex = m_speed*cos(atan2(ydif, xdif));
        movey = m_speed*sin(atan2(ydif, xdif));
        /*
        //check x positions
        if(GetPosition().x < m_target->GetPosition().x){
            movex = m_speed;

        }
        else if(GetPosition().x > m_target->GetPosition().x){
            movex = -m_speed;
        }

        //check y positions
        if(GetPosition().y < m_target->GetPosition().y){
            movey = m_speed;
        }
        else if(GetPosition().y > m_target->GetPosition().y){
            movey = -m_speed;
        }
        */
    }

    Move(movex, movey);

}

bool Bullet::checkCollision(){

    float range = 15;

    if(GetPosition().x > (m_target->GetPosition().x - range) && (GetPosition().x < m_target->GetPosition().x + range)
       && (GetPosition().y < m_target->GetPosition().y + range) && (GetPosition().y > m_target->GetPosition().y - range)
       && m_target != NULL)
       {
           return true;
       }

    return false;
}

void Bullet::Draw(Application &App){

    if(m_target == NULL || m_damage == 0){
        m_target = NULL;
        return;
    }
    /*
    else if(m_target->isDead()){
        m_target = NULL;
        return;
    }*/

    App.Draw(*this);

}
