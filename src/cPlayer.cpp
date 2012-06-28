#include "../include/cPlayer.h"

Player::Player(){
    m_lives = 50;
    m_score = 0;
    m_money = 100;



}
Player::~Player()
{
    //dtor
}

int Player::getLives()
{
    return m_lives;
}

int Player::getMoney()
{
    return m_money;
}

int Player::getScore()
{
    return m_score;
}

void Player::decreaseMoney(int amount)
{
    m_money = m_money - amount;
}

void Player::increaseMoney(int amount)
{
    m_money = m_money + amount;
}

bool Player::isDead()
{
    if(m_lives <= 0)
    {
        return true;
    }

    return false;

}

void Player::increaseScore(int amount)
{
    m_score = m_score + amount;
}

void Player::setLives(int lives)
{
    m_lives = lives;
}

