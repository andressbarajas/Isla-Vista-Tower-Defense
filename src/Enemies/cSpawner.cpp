#include "../../include/Enemies/cSpawner.h"

Spawner::Spawner() {
    m_group_sent = 1;

    m_spawn_img.LoadFromFile("media/Sprites/spawner.png");
    m_spawn_img.CreateMaskFromColor(sf::Color(255,0,255,255),0);
    SetImage(m_spawn_img);

    m_wave_sent = false;
    m_all_group_sent = true;

    Movement temp;

    temp.m_dir = East;
    temp.m_dist = 180;
    m_mov_q.push_back(temp);
    temp.m_dir = South;
    temp.m_dist = 70;
    m_mov_q.push_back(temp);
    temp.m_dir = West;
    temp.m_dist = 200;
    m_mov_q.push_back(temp);
    temp.m_dir = South;
    temp.m_dist = 150;
    m_mov_q.push_back(temp);
    temp.m_dir = East;
    temp.m_dist = 100;
    m_mov_q.push_back(temp);
    temp.m_dir = South;
    temp.m_dist = 70;
    m_mov_q.push_back(temp);
    temp.m_dir = East;
    temp.m_dist = 200;
    m_mov_q.push_back(temp);
    temp.m_dir = North;
    temp.m_dist = 80;
    m_mov_q.push_back(temp);
    temp.m_dir = East;
    temp.m_dist = 80;
    m_mov_q.push_back(temp);
    temp.m_dir = North;
    temp.m_dist = 190;
    m_mov_q.push_back(temp);
    temp.m_dir = West;
    temp.m_dist = 90;
    m_mov_q.push_back(temp);
}

void Spawner::resetEnemies() {

    vector<Enemy*>::iterator it;

    // Set Position. Adjust the Y by adding a number that could be 1-5.
    for(it = m_spwn_enemies.begin(); it != m_spwn_enemies.end(); it++) {
        (*it)->resetReachedBase();
        (*it)->SetX(GetPosition().x + (int)floor(rand() / (RAND_MAX + 1.0) * 26 + 15));
        (*it)->SetY(GetPosition().y + rand()%15+1);
        (*it)->setGroup((int)floor(rand() / (RAND_MAX + 1.0) * 5 + 1));
        (*it)->setDead(true);
        (*it)->setHealth(0);
        (*it)->setHBarPosition((*it)->GetPosition().x, (*it)->GetPosition().y - 3.0f);
        (*it)->selectDir(1);
    }
}

void Spawner::setTimeBtwnWaves(float time_btwn_waves) {
    m_time_btwn_waves = time_btwn_waves;
}

void Spawner::setTimeBtwnGroups(float time_btwn_groups) {
    m_time_btwn_groups = time_btwn_groups;
}

void Spawner::generateWave(){

    // instance of option class (for difficulty)
    vector<Enemy*>::iterator it;

    // Strength (Health and Speed)
    // Depending on the difficulty, generate a wave of enemies
    switch(2) {
        case 1: // Base enemies strength on a number between 1 and 10
            for(it = m_spwn_enemies.begin(); it != m_spwn_enemies.end(); it++) {
                (*it)->setMaxHealth(MINIMUM_HEALTH + (int)floor(rand() / (RAND_MAX + 1.0) * 10 + 1));
                (*it)->setSpeed(MINIMUM_SPEED + 0.4*(int)floor(rand() / (RAND_MAX + 1.0) * 10 + 1));
            }
            break;
        case 2: // Base enemies strength on a number between 3 and 10
            for(it = m_spwn_enemies.begin(); it != m_spwn_enemies.end(); it++) {
                (*it)->setMaxHealth(MINIMUM_HEALTH + (int)floor(rand() / (RAND_MAX + 1.0) * 8 + 3));
                (*it)->setSpeed(MINIMUM_SPEED + 0.4*(int)floor(rand() / (RAND_MAX + 1.0) * 8 + 3));
            }
            break;
        case 3: // Base enemies strength on a number between 5 and 10
            for(it = m_spwn_enemies.begin(); it != m_spwn_enemies.end(); it++) {
                (*it)->setMaxHealth(MINIMUM_HEALTH + (int)floor(rand() / (RAND_MAX + 1.0) * 6 + 5));
                (*it)->setSpeed(MINIMUM_SPEED + 0.4*(int)floor(rand() / (RAND_MAX + 1.0) * 6 + 5));
            }
            break;
        case 4: // Base enemies strength on a number between 7 and 10
            for(it = m_spwn_enemies.begin(); it != m_spwn_enemies.end(); it++) {
                (*it)->setMaxHealth(MINIMUM_HEALTH + (int)floor(rand() / (RAND_MAX + 1.0) * 4 + 7));
                (*it)->setSpeed(MINIMUM_SPEED + 0.4*(int)floor(rand() / (RAND_MAX + 1.0) * 4 + 7));
            }
            break;
        case 5: // Base enemies strength on a number between 9 and 10
            for(it = m_spwn_enemies.begin(); it != m_spwn_enemies.end(); it++) {
                (*it)->setMaxHealth(MINIMUM_HEALTH + (int)floor(rand() / (RAND_MAX + 1.0) * 2 + 9));
                (*it)->setSpeed(MINIMUM_SPEED + 0.4*(int)floor(rand() / (RAND_MAX + 1.0) * 2 + 9));
            }
            break;
        default: // Base enemies strength on a number between 5 and 10
            for(it = m_spwn_enemies.begin(); it != m_spwn_enemies.end(); it++) {
                (*it)->setMaxHealth(MINIMUM_HEALTH + (int)floor(rand() / (RAND_MAX + 1.0) * 6 + 5));
                (*it)->setSpeed(MINIMUM_SPEED + 0.4*(int)floor(rand() / (RAND_MAX + 1.0) * 6 + 5));
            }
            break;
    }

    resetEnemies();
}

void Spawner::nextFrame() {

    vector<Enemy*>::iterator it;

    // Check wave time
    if(!m_wave_sent) {
        m_totime = m_clock_wave.get_time();
        if(m_totime > m_time_btwn_waves) {
            generateWave();
            // Reset the pathes because they poped off the whole deque
            giveEnemyPath();
            m_wave_sent = true;
            m_all_group_sent = false;
            m_clock_group.start();
        }
    }

    // Check group time
    if(!m_all_group_sent) {
        m_totime = m_clock_group.get_time();
        if(m_totime > m_time_btwn_groups) {

            for(it = m_spwn_enemies.begin(); it != m_spwn_enemies.end(); it++) {
                if((*it)->getGroup() == m_group_sent) {
                    (*it)->setDead(false);
                    (*it)->setHealth((*it)->getMaxHealth());
                }
            }

            // Increment to the next group to be sent
            m_group_sent++;

            // Reset the timer so we don't send all groups at once
            m_clock_group.stop();
            m_clock_group.start();

            // If we just sent out group 5
            if( m_group_sent > 5 ) {
                 // Reset back to group 1
                 m_group_sent = 1;
                 // Set boolean value true that we have sent all
                 // the groups.
                 m_all_group_sent = true;
                 // Set to false so we can start the timer for the
                 // next wave
                 m_wave_sent = false;
                 m_clock_wave.stop();
                 m_clock_wave.start();
            }
        }
    }
}

void Spawner::Draw(Application &App) {
    App.Draw(*this);
}

void Spawner::getEnemies(vector<Enemy*> &spwn_enemies) {
    m_spwn_enemies = spwn_enemies;
}

void Spawner::setSpawnerPosition(sf::Vector2f pos) {

    vector<Enemy*>::iterator it;

    // Sets the position of the Spawner
    SetPosition(pos);

    // Set Position. Adjust the Y by adding a number that could be 1-5.
    for(it = m_spwn_enemies.begin(); it != m_spwn_enemies.end(); it++) {
        (*it)->SetPosition(pos);
        (*it)->setHBarPosition((*it)->GetPosition().x,(*it)->GetPosition().y - 3.0f);
    }
}

void Spawner::giveEnemyPath() {
    // instance of option class (for difficulty)
    vector<Enemy*>::iterator it;

    for(it = m_spwn_enemies.begin(); it != m_spwn_enemies.end(); it++) {
        (*it)->setMovement(m_mov_q);
    }
}

void Spawner::genPaths(int i){
    m_mov_q.clear();
    Movement temp;
    temp.m_dir = East;
    temp.m_dist = 860;
    m_mov_q.push_back(temp);

    switch(i){
        case 0:
            temp.m_dir = North;
            temp.m_dist = 80;
            m_mov_q.push_back(temp);

        break;
        case 1:
            temp.m_dir = North;
            temp.m_dist = 170;
            m_mov_q.push_back(temp);

        break;
        case 2:
            temp.m_dir = North;
            temp.m_dist = 255;
            m_mov_q.push_back(temp);
        break;
        case 3:
            temp.m_dir = North;
            temp.m_dist = 340;
            m_mov_q.push_back(temp);
        break;
        default: //error
        break;

    }

    temp.m_dir = West;
    temp.m_dist = 30;
    m_mov_q.push_back(temp);

}

void Spawner::Start() {
    m_clock_wave.start();
}

void Spawner::Pause() {
    m_clock_wave.pause();
    m_clock_group.pause();
}

void Spawner::UnPause() {
    m_clock_wave.unpause();
    m_clock_group.unpause();
}
