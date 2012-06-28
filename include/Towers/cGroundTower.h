#ifndef GROUNDTOWER_H
#define GROUNDTOWER_H

#include "cTower.h"

#include <cmath>
#include <string>
#include <iostream>


using namespace std;

/**
* Class: GroundTower
* Child of Tower
* Only attacks GroundEnemy objects. Attacks a single enemy at a time.
* Purpose: To attack single targets. This is different from
* towers that can target and attack multiple Enemy objects.
* the target attack area is circular.
* for more detail see "cTower.h"
*/
class GroundTower : public Tower
{
    public:
        /**
        * Constructor
        * GroundTower and Tower members are assigned default values
        * Pre-conditions: nothing
        * Post-conditions: GroundTower/Tower attributes modified.
        * GroundTower object was created.
        */
        GroundTower();
        /**
        * Destructor
        * Pre-conditions: GroundTower exists
        * Post-conditions: GroundTower object and its members were destroyed.
        */
        virtual ~GroundTower();
        /**
        * Function: attack
        * Attacks current target. If current target is dead or null,
        * function looks for a new enemy to attack, that is in range.
        * Pre-conditions: vector of enemy objects : enemies (argument)
        * Post-conditions: member m_current_enemy modified if target changes
        */
        void attack(vector<Enemy> enemies);
        /**
        * Function: upgrade
        * Upgrades GroundTower. Increasing its kill efficiency.
        * Pre-conditions: That the player has enough money.
        * Post-conditions: This GroundTower was upgraded giving it increased
        * attack speed or damage (attributes modified).
        */
        void upgrade();
    protected:
    Enemy *m_current_target;       //pointer to current enemy target of tower
    bool m_enemy_found;            //true if an enemy was found in range

    private:
};

#endif // GROUNDTOWER_H
