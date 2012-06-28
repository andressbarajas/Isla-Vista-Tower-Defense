#include "../../include/Towers/cMultiBullet.h"
#include <iostream>
#include "../../include/Towers/cTower.h"
using namespace std;

MultiBullet::MultiBullet()
{

    setDamage(2);    //equates to 30% kill chance

    setSpeed(.25f);  //.25 times per second
    m_last_pulse = clock();


}

MultiBullet::~MultiBullet()
{
    //dtor
}

void MultiBullet::nextFrame(){
    Tower *temp = getTower();
    if(temp != NULL){
        SetPosition(temp->GetPosition().x, temp->GetPosition().y);
        m_circ = sf::Shape::Circle(temp->GetPosition().x, temp->GetPosition().y, m_attack_radius, sf::Color::Red, 2, sf::Color::Blue);
    }

}

void MultiBullet::Draw(Application &App){

    if(m_last_pulse + CLOCKS_PER_SEC < clock())
    {
        App.Draw(m_circ);
    }
    else{
        return;
    }

}

void MultiBullet::setTargets(vector<Enemy*> &enemy_v){

    vector<Enemy*>::iterator it;

    m_targets.clear();
    //m_targets = enemy_v;

    for(it = enemy_v.begin(); it != enemy_v.end(); it++) {
            m_targets.push_back(*it);
        }


}

void MultiBullet::pulse(){


    //cout<<"calling pulse"<<endl;
    if(!m_targets.empty() && (getTower()->getAmmo() > 0)){
        if((m_last_pulse + int(CLOCKS_PER_SEC/(getSpeed()+1)) < clock())){
            int random;
            srand ( time(NULL) );
            m_last_pulse = clock();
            vector<Enemy*>::iterator it;
            for(it = m_targets.begin(); it != m_targets.end(); it++) {
                random = rand() % 10 + 1;
                if(random <= getDamage()){
                    Player &player = Player::GetInstance();
                    player.increaseMoney(3);
                    (*it)->setDead(true);
                    getTower()->decAmmo();

                }


            }




    }

}
}
