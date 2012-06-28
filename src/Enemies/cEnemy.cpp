#include "../../include/Enemies/cEnemy.h"


Enemy::Enemy() {
    m_type = "enemy";
    m_isDead = true;
    m_group_num = 0;
    m_already_reachedbase = false;
    //m_health.setMaxHealth(100);
    //m_health.setHealth(100);
    m_health.setBarWidth(18);
    m_health.setBarHeight(3);
    m_health.setBarPosition(GetPosition().x, GetPosition().y - 3.0f);

    (*this).subAdd(&m_health);
}

string Enemy::getType()
{
    return m_type;
}

int Enemy::getDirection() {
    return m_mov_q.front().m_dir;
}
void Enemy::takeDamage(unsigned int damage) {
    if(!m_isDead) {
        if(damage > m_health.getHealth()) {
            m_health.setHealth(0);
            m_isDead = true;
            return;
        }
        m_health.decHealth(damage);
        return;
    }

}

void Enemy::setHealth(unsigned int hp) {
    m_health.setHealth(hp);
    if(hp > 0) {
        m_isDead = false;
    } else {
        m_isDead = true;
    }
}

void Enemy::navigate() {

    if(m_mov_q.empty() || (m_isDead == true)) return;

    float distance = 0;

    // Decrement the distance that we have left to travel
    m_mov_q.front().m_dist -= m_speed;

     /*
    if(m_mov_q.front().m_dist < 0) {
        distance = m_mov_q.front().m_dist + m_speed;
    } else {
        distance = m_speed;
    }
*/
    distance = m_speed;

    // If we are done with traveling in a certain direction
    if(m_mov_q.front().m_dist <= 0) {
        // Pop the movement off the queue
        m_mov_q.pop_front();
        // If there is a movement left on the queue
        if(m_mov_q.size() > 0) {
            // Set the image to the new direction
            SetImage(*(m_img_dir+m_mov_q.front().m_dir));
        }
        else {
            // Enemy is dead because he reached home base
            m_isDead = true;
            Player &player = Player::GetInstance();
            //player.setLives(player.getLives() - 1);
            SetImage(*(m_img_dir+1)); // Face east AKA HACK
            // have a function of enemy that returns true when m_isDead is true and health > 0

        }
    }

    // Move the enemies and its sub drawables
    if(m_mov_q.front().m_dir == North) {
        moveObjects(0, -distance);
    } else if(m_mov_q.front().m_dir == East) {
        moveObjects(distance, 0.0f);
    } else if(m_mov_q.front().m_dir == South) {
        moveObjects(0, distance);
    } else if(m_mov_q.front().m_dir == West) {
        moveObjects(-distance, 0);
    }
}

void Enemy::Draw(Application &App) {
    // If the enemy is dead we should not draw it
    if(m_isDead) {
        return;
    }

    // Draw the enemy
    App.Draw(*this);

    // Draw the health bar
    m_health.Draw(App);
}

void Enemy::nextFrame() {
    // Check if dead
    if(m_health.isZero()) {
        m_isDead = true;
        return;
    }

    // Move enemy
    navigate();

    // Move health bar attached to enemy
    m_health.nextFrame();
}

bool Enemy::reachedBase() {
    if(m_mov_q.empty() && m_health.getHealth() > 0 && !m_already_reachedbase) {
        m_already_reachedbase = true;
        return true;
    }


    return false;
}









