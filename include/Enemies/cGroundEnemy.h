#ifndef GROUNDENEMY_H
#define GROUNDENEMY_H

#include "../Enemies/cEnemy.h"
#include <string>

/**
* Class: GroundEnemy
* Child of Enemy
* Cannot fly, must abide by path obstructions.
* see "Enemy.h" for more information.
* *** currently not used ***
*/
class GroundEnemy : public Enemy
{
    public:
        GroundEnemy() { m_type = "ground"; }
        virtual ~GroundEnemy() {}
    protected:
    private:
};

#endif // GROUNDENEMY_H
