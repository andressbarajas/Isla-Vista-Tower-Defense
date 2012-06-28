#ifndef AIRENEMY_H
#define AIRENEMY_H

#include "../Enemies/cEnemy.h"
#include <string>

using namespace std;

/**
* Class: AirEnemy
* Child of Enemy
* Purpose, an enemy that can fly directly to destination
* see "Enemy.h" for more information.
* ***Implementation still up to discussion***
*/
class AirEnemy : public Enemy
{
    public:
        AirEnemy() {}
        virtual ~AirEnemy() {}

    protected:
    private:
};

#endif // AIRENEMY_H
