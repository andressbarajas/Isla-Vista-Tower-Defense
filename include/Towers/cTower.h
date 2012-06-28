#ifndef TOWER_H
#define TOWER_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <ctime>

#include "cBullet.h"
#include "../Enemies/cEnemy.h"
#include "cMultiBullet.h"

using namespace std;

class Bullet;

/**
* Class: Tower
* Tower class is an ancestral class. Meant to be inherited by other classes.
* Tower inherits sf::Sprite so that it may be drawn onto the application window
* Purpose: To attack Enemy objects and destroy them, earning money for the player.
*/
class Tower: public SpriteObj {
    public:
       /**
        * Constructor
        * Tower members are assigned default values
        * Pre-conditions: nothing
        * Post-conditions: Tower attributes modified. Tower object was created.
        */
        Tower();
        virtual ~Tower() {}

        /**
        * Function: attack
        * currently empty, meant to be overriden for different types of towers.
        * different towers will have different attack functions to accomodate their
        * different methods of attack.
        * Pre-coditions: A wave has started.
        * Post-conditions: an enemy has taken damage if in range. The tower has
        * selected a target if the tower does not have a target, and
        * the enemy is in range.
        */
        virtual void attack(vector<Enemy*> &enemies);

        /**
        * Function: upgrade
        * Upgrades tower. Increasing its
        * Pre-conditions: That the player has enough money.
        * Post-conditions: This tower was upgraded giving it increased attack speed
        * or damage (attributes modified).
        *************This function is currently empty****************
        */
        virtual int upgrade(int grade);

        /**
        * Function: enemiesInRange
        * Checks all enemies in a vector to see if they are in range,
        * then returns them.
        * Pre-conditions: The tower is not currently attacking a target.
        * Vector of enemies : enemy_v passed as an argument.
        * Post-conditions: The tower was upgraded. Attributes m_attackSpeed
        * and m_damage increased.
        */
        void enemiesInRange(vector<Enemy*> &enemy_v);

        // Returns true when a single enemy is in range of the tower
        bool inRange(Enemy *enemy_var);

        // Searches through the vector "m_enemies_in_range" and selects an enemy to attack and sets
        // m_attacked_enemy equal to that enemy.  Pops all the enemies since we have an enemy that
        // we are attacking.
        bool attackingPrecedence();

        /**
        * Function: setAttackRadius
        * Sets the attack radius of tower.
        * Pre-conditions: a float argument to set tower attack radius to.
        * Post-conditions: the tower m_attack_radius attribute was modified.
        */
        inline void setAttackRadius(float rad){ m_attack_radius = rad; }

        // Draw the enemy and its health bar
        virtual void Draw(Application &App);

        virtual void nextFrame();

        virtual bool handleEvent(const sf::Input &Input);

        void setTowerPosition(sf::Vector2f pos);

        inline bool isSelected() { return m_selected; }
        inline void setSelected(bool select){m_selected = select;}
        inline bool hasMultiBullet(){return (m_multi_bullet != NULL);}
        inline int getDamage(){return m_damage;}
        inline int getSingleDmg(){return m_bullet.getDamage();}
        inline float getAttackSpeed(){return m_attackSpeed;}
        inline float getRadius(){return m_attack_radius;}
        void getStatus(string &status);
        inline int getAmmo(){return m_ammo;}
        inline void setAmmo(int ammo){m_ammo = ammo;}
        inline void decAmmo(){m_ammo--;}
        void reset();

    protected:
        int m_framecount;
        int m_damage;                    //the damage done per hit by the tower.
        float m_attackSpeed;             //the frequency in which the tower attacks.
        float m_attack_radius;           //the radius in which tower can attack.(Tower range)
        bool m_selected;
        int m_ammo;

        sf::Shape m_circ;       // To show the radius
        vector<Enemy*> m_enemies_in_range;
        Enemy *m_attacked_enemy;
        Bullet m_bullet;
        MultiBullet *m_multi_bullet;
        sf::Image m_bullet_img;
        clock_t m_lastfire;
        sf::Sound m_sound;
        sf::SoundBuffer m_snd_buffer;

    private:
};

#endif // TOWER_H
