#ifndef BASICTOWER_H
#define BASICTOWER_H

#include "cTower.h"
#include <string>

using namespace std;

/**
* Class: BasicTower
* Child of Tower
* Attacks a single enemy at a time.
* Purpose: To attack single targets. This is different from
* towers that can target and attack multiple Enemy objects.
* the target attack area is circular.
* for more detail see "cTower.h"
*/
class BasicTower : public Tower
{
    public:
       /**
        * Constructor
        * BasicTower and Tower members are assigned default values
        * Pre-conditions: nothing
        * Post-conditions: BasicTower/Tower attributes modified.
        * BasicTower object was created.
        */
        BasicTower();
        //destructor
        virtual ~BasicTower();
        /**
        * Function: attack
        * Attacks current target. If current target is dead or null,
        * function looks for a new enemy to attack, that is in range.
        * Pre-conditions: vector of enemy objects : enemies (argument)
        * Post-conditions: member m_current_enemy modified if target changes
        * Enemy object was set as current target if in range (association made)
        * Enemy object takes damage if targeted (attributes modified)
        * Enemy object destroyed if health reaches zero.
        */
        void attack(vector<Enemy> enemies);
        /**
        * Function: upgrade
        * Upgrades BasicTower. Increasing its kill efficiency.
        * Pre-conditions: That the player has enough money.
        * Post-conditions: This BasicTower was upgraded giving it increased
        * attack speed or damage (attributes modified).
        */
        void upgrade();
    protected:
    private:
};

#endif // BASICTOWER_H
