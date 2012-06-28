#ifndef AIRTOWER_H
#define AIRTOWER_H

#include "cTower.h"
#include "../Enemies/cEnemy.h"
#include <string>
#include <iostream> // Used for cout and endl

using namespace std;

/**
* Class: AirTower
* Child of Tower
* Attacks single target AirEnemy objects.
* Purpose: Attack AirEnemy objects, single attack type tower,
* circular attack area.
* for more detail see "cTower.h"
* ***Implementation is still up for discussion***
*/
class AirTower : public Tower
{
    public:
        /**
        * Constructor
        * AirTower and Tower members are assigned default values
        * Pre-conditions: nothing
        * Post-conditions: AirTower/Tower attributes modified.
        * AirTower object was created.
        */
        AirTower();
        //destructor
        virtual ~AirTower();
        /**
        * Function: attack
        * tower attacks AirEnemy objects.
        * Pre-conditions: AirEnemy objects in range.
        * Post-conditions: Association made with AirEnemy (current target)
        * AirEnemy object takes damage (attribute modified).
        * AirEnemy object destroyed.
        * Player earns money when Enemy destroyed
        *** Implementation still up for discussion ***
        */
        void attack(vector<Enemy> enemies);
        /**
        * Function: upgrade
        * Upgrades tower, making it attack faster and/or do more damage.
        * Pre-conditions: Player has enough money to upgrade.
        * Post-conditions: Tower attributes modified, attack/attack speed.
        *** Implementation still up for discussion ***
        */
        void upgrade();
        protected:
    private:
};

#endif // AIRTOWER_H
