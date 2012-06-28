
#ifndef _SPAWNER_H_
#define _SPAWNER_H_

#include <ctime>
#include <deque>
#include <vector>
#include <iostream>

#include "cEnemy.h"
#include "../cSpriteObj.h"
#include "../cTimer.h"

#define MINIMUM_SPEED 0
#define MINIMUM_HEALTH 100

using namespace std;

class Spawner : public SpriteObj {
public:
    Spawner();
    ~Spawner() {}
    void generateWave();
    void resetEnemies();
    void setTimeBtwnWaves(float time_btwn_waves);
    void setTimeBtwnGroups(float time_btwn_groups);
    void setPath(const deque<Movement> &mov_q) { m_mov_q = mov_q; }
    void giveEnemyPath();
    void setSpawnerPosition(sf::Vector2f pos);
    void getEnemies(vector<Enemy*> &spwn_enemies);
    void genPaths(int i);

    virtual void nextFrame();
    virtual void Draw(Application &App);

    void Start();
    void Pause();
    void UnPause();

protected:

private:
    int m_group_sent;

    bool m_wave_sent;
    bool m_all_group_sent;

    float m_totime;
    float m_time_btwn_waves;
    float m_time_btwn_groups;

    Timer m_clock_wave;
    Timer m_clock_group;

    sf::Image m_spawn_img;

    vector<Enemy*> m_spwn_enemies;
    deque<Movement> m_mov_q;
};

#endif /* _SPAWNER_H_ */

