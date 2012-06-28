#include "../../include/Towers/cTower.h"
#include "../../include/Towers/cBullet.h"

#include <iostream>
using namespace std;

/** NOTES: The tower should be able to handle input now that it is a SpriteObj.  Input is needed
* to make towers selectable.
*     Does a tower need a type? If it does...instead of using a string for tower type, an enumeration
* should be created maybe in a seperate header file?  The should go for enemy.
*/

Tower::Tower() {

    m_bullet_img.LoadFromFile("media/Sprites/bullet.png");
    m_bullet_img.CreateMaskFromColor(sf::Color(255,0,255,255),0);
    m_bullet_img.SetSmooth(false);
    m_bullet.SetImage(m_bullet_img);
    m_bullet.setTower(this);
    SetCenter(25,28);

    m_snd_buffer.LoadFromFile("media/Level/bullet.wav");

    reset();
}

void Tower::reset(){

    m_ammo = 0;
    m_framecount = 0;
    m_damage = 0;
    m_attackSpeed = 0;
    m_attack_radius = 80.0f;
    m_selected = false;
    m_attacked_enemy = NULL;
    m_bullet.setSpeed(2.0f);
    m_bullet.setDamage(0);
    m_sound.SetBuffer(m_snd_buffer);
    m_multi_bullet = NULL;
    m_selected = false;
    m_lastfire = clock();
    //upgrade(0);

}


void Tower::attack(vector<Enemy*> &enemies) {
    //looks for enemies 6 times per second
    if(!(m_lastfire + int(CLOCKS_PER_SEC/5) < clock())){

        return;
    }

    m_lastfire = clock();

    // Check if the tower can attack ... maybe should have a private bool member
    // for this
    /*
    if(!m_can_attack) {
        return;
    }
    */
    //cout<<"Calling attack"<<endl;

    // If we already have an enemy that we are attacking
    // Make sure it is still in attacking range and alive; If it is, attack it.


    if((m_attacked_enemy != NULL) && inRange(m_attacked_enemy) && (!m_attacked_enemy->isDead())
       && m_bullet.hasTarget() && m_bullet.hasHit()) {
        m_bullet.setTarget(m_attacked_enemy);
        m_bullet.SetPosition(GetPosition());
        //m_sound.Play();
        return;
    } else {
        // Set attacked enemy to NULL because it is no longer in range or we werent attacking an
        // enemy in the first place.
        m_attacked_enemy = NULL;
        m_bullet.setTarget(NULL);
        m_bullet.SetPosition(GetPosition());

        // Search for enemies in range
        enemiesInRange(enemies);

        // Select an enemy to attack based on precedence
        if(attackingPrecedence()) { // Only returns false when there are no enemies in range

            if(hasMultiBullet() && m_ammo > 0){
                m_multi_bullet->setTargets(enemies);
                m_multi_bullet->pulse();

            }

            m_bullet.setTarget(m_attacked_enemy);
            //m_sound.Play();
            return;
        }

        //m_multi_bullet->setTargets(NULL);

    }
}

int Tower::upgrade(int grade) {
    if(!m_selected) {
        return 0;
    }
    int radcost = 0;

        switch(grade){
        case 0:
                if(m_multi_bullet == NULL){
                    m_damage = 1;
                    m_attackSpeed = .25;
                    m_ammo = 50;
                    m_multi_bullet = new MultiBullet();
                    m_multi_bullet->setTower(this);
                    m_multi_bullet->setDamage(m_damage);
                    return 10;
                }
                    //GetImage().LoadFromFile("media/Sprites/party_house.png");

                    m_ammo = m_ammo + 50;
                    return 10;

                break;
        case 1:
            m_bullet.setDamage(m_bullet.getDamage()+5);
            return 5;
            break;
        case 2:
            if(hasMultiBullet()){
                if(m_multi_bullet->getDamage() <= 5){
                    m_damage++;
                    m_multi_bullet->setDamage(m_multi_bullet->getDamage()+1);
                    return 60;
                }
            }
            break;

        case 3:
            if(m_multi_bullet != NULL){

                m_attackSpeed = m_attackSpeed + .1;
                m_multi_bullet->setSpeed(m_attackSpeed);
                return 40;
            }
            break;
        case 4:
            if(m_multi_bullet != NULL){
                radcost = (((m_attack_radius - 80)/5) + 1)*200;
                m_attack_radius = m_attack_radius + 5.0f;
                return radcost;
            }
            break;
        default: // this is an error.
            break;
        }

        return 0;


}

//Only checks North and East Directions

bool Tower::attackingPrecedence() {

    // If there are no enemies in range we have nothing to attack
    if(m_enemies_in_range.empty()) {
        return false;
    }

    vector<Enemy*>::iterator it;

    Enemy *temp = m_enemies_in_range.front();

    //the enemy closest to free-birds is attacked. (traveled most distance)
    for(it = m_enemies_in_range.begin(); it != m_enemies_in_range.end(); it++) {

        if((**it).getMovesLeft() < temp->getMovesLeft()) {
            temp = *it;

        }
        else if((**it).getDistLeft() < temp->getDistLeft()) {
            temp = *it;
        }
    }

    // Precedence formula to select an enemy then
    m_attacked_enemy = temp;

    // Empty the vector because we selected an enemy to attack
    m_enemies_in_range.clear();

    return true;
}

bool Tower::inRange(Enemy *enemy_var) {

    int xdif = 0;
    int ydif = 0;
    float enemy_dist = 0;

    if(enemy_var == NULL || enemy_var->isDead()) {
        return false;
    }

    //check if enemy in radius
    //takes difference in x & y coordinates then
    //uses pythagorean theorem a^2+b^2 = c^2 to calculate distance
    xdif = abs((int)(GetPosition().x - enemy_var->GetPosition().x));
    ydif = abs((int)(GetPosition().y - enemy_var->GetPosition().y));
    enemy_dist = sqrt(pow(xdif, 2) + pow(ydif, 2));


    //compares distance from enemy to attack radius
    if (m_attack_radius >= enemy_dist && !(enemy_var->reachedBase())) {
        return true;
    }
    //m_attacked_enemy = NULL;
    return false;
}

void Tower::enemiesInRange(vector<Enemy*> &enemy_v) {

    vector<Enemy*>::iterator it;

    m_enemies_in_range.clear();

    for(it = enemy_v.begin(); it != enemy_v.end(); it++) {
        //compares distance from enemy to attack radius
        if (inRange(*it)) {
            m_enemies_in_range.push_back(*it);
        }
    }
}

void Tower::nextFrame() {

    m_circ = sf::Shape::Circle(GetPosition().x, GetPosition().y, m_attack_radius, sf::Color(255,0,0,64), 2, sf::Color(0,0,0,64));

    if(hasMultiBullet()){
        m_multi_bullet->setTargets(m_enemies_in_range);
        m_multi_bullet->nextFrame();
    }

    // handle attack speed- either use a clock or do a countdown using frames.
    // when the count is zero the tower can attack.  As soon as the tower attacks
    // the count is set equal to his attack speed and gets decremented each frame by 1
    // till it reaches zero and can attack again.  Need to add private attribute to
    // handle the count down.
    m_bullet.nextFrame();
}

bool Tower::handleEvent(const sf::Input &Input){

    bool leftMouseDown = Input.IsMouseButtonDown(sf::Mouse::Left);
    unsigned int mouseX = Input.GetMouseX();
    unsigned int mouseY = Input.GetMouseY();



    if( mouseX >= (GetPosition().x - 24) && mouseY >= (GetPosition().y - 24) &&
            mouseX <= (GetPosition().x + GetImage()->GetWidth()-24) && mouseY <= (GetPosition().y + GetImage()->GetHeight()-24)
            && leftMouseDown ){
                m_selected = true;
            }


    return m_selected;
}

void Tower::Draw(Application &App){
    App.Draw(*this);
    m_bullet.Draw(App);
    if(m_selected){
        App.Draw(m_circ);
    }

}

void Tower::setTowerPosition(sf::Vector2f pos){
    SetPosition(pos);
    m_bullet.SetPosition(pos.x, pos.y);
}

void Tower::getStatus(string &status) {

    stringstream ss;

    ss << "Attack Damage: " << m_damage << endl << "Attach Radius: " << m_attack_radius << endl << "Attack Speed: " << m_attackSpeed << endl;
    ss >> status;

    /*
    Return a char* that contains:
     - attack damage of the tower
     - type of tower
     - attack radius of the tower
     - attack speed of the tower

     Check Money class for help with construction of strings
    */

}
