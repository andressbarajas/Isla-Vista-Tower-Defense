#include "../../include/Towers/cGroundTower.h"

GroundTower::GroundTower()
{

    m_damage = 40;
    m_attackSpeed = 10;
    m_enemy_found = false;
    SetPosition(100.0f,100.0f);

}

GroundTower::~GroundTower()
{
    //dtor
}


void GroundTower::attack(vector<Enemy> enemies)
{
    if((m_current_target != NULL) && m_current_target->isDead()) {
        m_current_target = NULL;
        m_enemy_found = false;
    }

    if(m_enemy_found ){

    }

    if(!m_enemy_found) {

    }


}

void GroundTower::upgrade()
{
    m_damage = m_damage + 2;
    m_attackSpeed = 1;
}

