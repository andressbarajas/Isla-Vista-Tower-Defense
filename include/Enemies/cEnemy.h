#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <deque>
#include <string>
#include <time.h>
#include <stdlib.h>

#include "../SFMLMappy.h"
#include "../sMovement.h"
#include "../cSpriteObj.h"
#include "../Drawables/cHealthBar.h"
#include "../cPlayer.h"

using namespace std;

/**
* Class: Enemy
* Enemy class is an ancestral class. Meant to be inherited by other classes.
* Enemy inherits sf::Sprite so that it may be drawn onto the application window
* Purpose: To attack reach target destination (Free-birds). Reducing player lives
* eventually making player lose.
*/
class Enemy : public SpriteObj {
public:
    /**
    * Constructor
    * Initializes Enemy members to default values.
    * Pre-conditions: nothing
    * Post-conditions: An Enemy object was instantiated.
    */
    Enemy();
    virtual ~Enemy() {}

    //Function setter for protected image directory
    void setImgDir(sf::Image *imgdir) { m_img_dir = imgdir; }

    //Function setter for m_health
    void setHealth(unsigned int hp);

    void setMaxHealth(unsigned int hp) { m_health.setMaxHealth(hp); }

    unsigned int getMaxHealth() { return m_health.getMaxHealth(); }

    int getDirection();

    // Sets the position of the health bar
    void setHBarPosition(const float x, const float y) { m_health.setBarPosition(x,y); }

    //function setter for m_speed
    inline void setSpeed(float speed) { m_speed = speed; }     //LM 11/11/2010

    //Function getter for m_speed
    inline float getSpeed() { return m_speed; }                //LM 11/11/2010

    //Function getter for m_type
    virtual string getType();

     /**
    * Function: navigate
    * Enemy object is able to navigate itself throughout the map.
    * This navigation path is currently pre-defined in the constructor.
    * Pre-conditions: The Enemy object exists and has a position.
    * Enemy has a speed greater than 0.
    * Enemy has a set movement queue m_mov_q.
    * Post-conditions: The Enemy moved itself a distance determined by
    * m_speed protected attribute in a direction determined by
    */
    void navigate();                                        //LM 11/11/2010

    //Enemy object takes damage, health is subtracted.
    void takeDamage(unsigned int damage);

    //Function getter for protected member m_isDead

    bool isDead() { return m_isDead; }

    void setDead(bool dead) { m_isDead = dead; }

    // Draw the enemy and its health bar
    virtual void Draw(Application &App);

    // Updates everything that has to do with the enemy
    virtual void nextFrame();

    void setGroup(int group) { m_group_num = group; }
    int getGroup() { return m_group_num; }

    void setMovement(deque<Movement> mov_q) {  m_mov_q = mov_q; }
    deque<Movement> getMovement(){return m_mov_q;}
    bool reachedBase();

    void selectDir(int dir) { SetImage(*(m_img_dir+dir)); }

    inline int getMovesLeft(){return m_mov_q.size();}       //used for attack precedence LM
    inline float getDistLeft(){return m_mov_q.front().m_dist;}//used for attack precedence LM
    inline void resetReachedBase(){m_already_reachedbase = false;}

protected:

    string m_type;                    //enemy type could be used to check attack effect
    HealthBar m_health;               //enemy health. If 0 enemy is dead.
    bool m_isDead;                    //true if Enemy is dead
    float m_speed;                    //LM 11/11/2010 enemy movement speed factor.
    sf::Image *m_img_dir;             //pointer to image directory
    int m_group_num;
    bool m_already_reachedbase;

private:

    deque<Movement> m_mov_q;            //Movement queue has the enemies pre-defined path.
};

#endif /* ENEMY_H */
