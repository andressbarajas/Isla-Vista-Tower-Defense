#include "../../include/Towers/cBasicTower.h"

BasicTower::BasicTower()
{
    m_damage = 20;
    m_attackSpeed = 10;

}

BasicTower::~BasicTower()
{
    //dtor
}

void BasicTower::attack(vector<Enemy> enemies)
{

}

void BasicTower::upgrade()
{
    m_damage = m_damage + 1;
    m_attackSpeed = 1;
}
