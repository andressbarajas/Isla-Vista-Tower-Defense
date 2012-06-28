#ifndef MULTIBULLET_H
#define MULTIBULLET_H
#include <ctime>
#include "cBullet.h"
#include <vector>

/**
* This is a specialized class
* Used specifically for party towers
* Attacks all targets in range, Has a %
* chance to instantly draw them in (kill)
*/
class MultiBullet: public Bullet
{
    public:
        MultiBullet();
        virtual ~MultiBullet();
        virtual void nextFrame();
        virtual void Draw(Application &App);
        void setTargets(vector<Enemy*> &enemy_v);
        void pulse();
    protected:
    private:
        vector<Enemy*> m_targets;
        float m_attack_radius;
        clock_t m_last_pulse;
        sf::Shape m_circ;

};

#endif // MULTIBULLET_H
