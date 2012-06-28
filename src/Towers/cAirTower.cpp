#include "../../include/Towers/cAirTower.h"

AirTower::AirTower()
{
    m_damage = 40;
    m_attackSpeed = 10;

}

AirTower::~AirTower()
{
    //dtor
}


void AirTower::attack(vector<Enemy> enemies)
{

}

void AirTower::upgrade()
{
    m_damage = m_damage + 2;
    m_attackSpeed = 1;
}





