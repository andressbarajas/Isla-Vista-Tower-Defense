
#include "../../include/Panels/cMapPanel.h"

MapPanel::MapPanel() {
    m_imgset[0].LoadFromFile("media/Sprites/up.png");
    m_imgset[1].LoadFromFile("media/Sprites/right.png");
    m_imgset[2].LoadFromFile("media/Sprites/down.png");
    m_imgset[3].LoadFromFile("media/Sprites/left.png");

    Tower *t = NULL;
    m_imgset[4].LoadFromFile("media/Sprites/house.png");
    m_imgset[5].LoadFromFile("media/Sprites/party_house.png");


    int num = 3;
    srand ( time(NULL) );

    for(int i = 0; i < 9; i++){
        //if(num <= (rand() % 3 + 1)){
            t = new Tower();
            t->SetImage(m_imgset[4]);
            t->setTowerPosition(sf::Vector2f(60.0f + i*83,115.0f));
            m_towers.push_back(t);


    }

    for(int j = 0; j < 4; j++)
        for(int i = 0; i < 10; i++){
            //if(num <= (rand() % 3 + 1)){
                t = new Tower();

                t->SetImage(m_imgset[4]);
                t->setTowerPosition(sf::Vector2f(60.0f + i*83, 205.0f + 95*j));
                m_towers.push_back(t);

        }


    for(int i = 0; i < 6; i++){
        m_imgset[i].CreateMaskFromColor(sf::Color(255,0,255,255),0);
        m_imgset[i].SetSmooth(false);
    }

    CreateEnemies();

    // 20 seconds between waves
    for(int i = 0; i < 4; i++){
        m_spawners[i].setTimeBtwnWaves(50.0f);

        // 1 second between group
        m_spawners[i].setTimeBtwnGroups(0.5f);

        // So m_spawner can edit m_enemies
        m_spawners[i].getEnemies(m_enemies[i]);

        m_spawners[i].setSpawnerPosition(sf::Vector2f(-50, 145.0f + i*95.0f));
        m_spawners[i].genPaths(i);
    }

    m_base.SetPosition(sf::Vector2f(750.0f, 55.0f));

    m_base.setMaxHealth(50);
    m_base.setHealth(50);
    m_base.setBaseHealthPosition(sf::Vector2f(860.0f, 30.0f));

    Init();
}

void MapPanel::Init() {
    vector<Tower*>::iterator it_towers;

    for(int i = 0; i < 4; i++) {
        m_spawners[0].resetEnemies();
    }

    for(it_towers = m_towers.begin(); it_towers != m_towers.end(); it_towers++) {
        (*it_towers)->reset();
    }

    m_selected_tower = NULL;
}

void MapPanel::Draw(Application &App) {

    for( int i = 0; i < 8; i++) {
        m_map.ChangeMapLayer(i);
        m_map.DrawMapBG(App, 0, 0);
    }

    // Draw Enemies
    vector<Enemy*>::iterator it_enemys;

    for(int i = 0; i < 4; i++)
        for(it_enemys = m_enemies[i].begin(); it_enemys != m_enemies[i].end(); it_enemys++){
            (*it_enemys)->Draw(App);
        }

    // Draw Spawner
    for(int i = 0; i < 4; i++)
        m_spawners[i].Draw(App);

    // Draw Towers
    vector<Tower*>::iterator it_towers;
    for(it_towers = m_towers.begin(); it_towers != m_towers.end(); it_towers++){
        (*it_towers)->Draw(App);
    }

    m_base.Draw(App);
}

void MapPanel::nextFrame() {
    // Update Map Animations
    m_map.UpdateMapAnims();

    // Update Spawner
    UpdateSpawner();

    // Update Enemies
    UpdateEnemies();

    // Update Towers
    UpdateTowers();

    reachBase();

    // Update Home base
    UpdateBase();
}

bool MapPanel::handleEvent(const sf::Input& Input) {
    vector<Tower*>::iterator it_towers;

    bool leftMouseDown = Input.IsMouseButtonDown(sf::Mouse::Left);
    unsigned int mouseX = Input.GetMouseX();
    unsigned int mouseY = Input.GetMouseY();


    for(it_towers = m_towers.begin(); it_towers != m_towers.end(); it_towers++) {
        if(m_selected_tower != NULL)
            if( (mouseX < m_selected_tower->GetPosition().x || mouseY < m_selected_tower->GetPosition().y ||
                mouseX > (m_selected_tower->GetPosition().x + m_selected_tower->GetImage()->GetWidth())
                || mouseY > (m_selected_tower->GetPosition().y + m_selected_tower->GetImage()->GetHeight()))
                && leftMouseDown && !(mouseX > 860 && mouseY > 0)){
                    m_selected_tower->setSelected(false);
                    m_selected_tower = NULL;
                }


        (*it_towers)->handleEvent(Input);
    }
    return true;
}


void MapPanel::moveObjects(const float x, const float y) {
    //Move(x, y);
    //SetStartPosition(sf::Vector2f(x,y));
    moveSubs(x, y);
}

void MapPanel::SetMap(const char * map_name) {
    m_map.LoadMap(map_name);
}

void MapPanel::SetStartPosition(sf::Vector2f start_posi) {
    m_map.SetMapStartPosition(start_posi.x, start_posi.y);
}

void MapPanel::SetMapDimension(sf::Vector2f map_dim) {
    m_map.SetMapDimensions(map_dim.x, map_dim.y);
}

void MapPanel::GenerateMapLookUp() {
    m_map.GenerateMapYLookup();
}

/*
void MapPanel::GenerateWave(int difficulty) {

    if(difficulty == 1)
    {
        Enemy *temp;
        int randomx = 0;
        int randomy = 0;

        //setting up the single test enemy image
		//temp.SetImage(m_imgright);
        srand ( time(NULL) );
		for(int i = 0; i < 10; i++) {

            randomx = rand()%10 + 1;
            randomy = rand()%10 + 1;
		    temp = new Enemy();
		    temp->setImgDir(m_imgset);
		    temp->SetImage(m_imgset[1]);                 //1 is east img
            temp->SetPosition(30.0f+randomx*5,400.0f+randomy*8);
            temp->setHBarPosition(30.0f+randomx*5,400.0f+randomy*8 - 3.0f);
            temp->setSpeed(3.0f);
		    m_enemies.push_back(temp);
		}
	}
}
*/

void MapPanel::CreateEnemies() {
    Enemy * temp;

    for(int j = 0; j < 4; j++)
        for(int i = 0; i < 15; i++) {
            temp = new Enemy();
            temp->setImgDir(m_imgset);
            temp->SetImage(m_imgset[1]);                 //1 is east img
            m_enemies[j].push_back(temp);
        }
}

void MapPanel::UpdateEnemies() {

    vector<Enemy*>::iterator it;
    for(int i = 0; i < 4; i++)
        for(it = m_enemies[i].begin(); it != m_enemies[i].end(); it++) {
            (*it)->nextFrame();
        }
}

void MapPanel::UpdateTowers() {

    vector<Tower*>::iterator it;

    for(int i = 0; i < 4; i++)
        for(it = m_towers.begin(); it != m_towers.end(); it++) {
            if((*it)->isSelected()){
                if(m_selected_tower != (*it)){
                    if(m_selected_tower != NULL)
                        m_selected_tower->setSelected(false);
                    m_selected_tower = *it;
                }


            }

            if((*it)->getAmmo() > 0){
                (*it)->SetImage(m_imgset[5]);


            }
            else
                (*it)->SetImage(m_imgset[4]);

            (*it)->attack(m_enemies[i]);
            (*it)->nextFrame();
        }
}

void MapPanel::UpdateSpawner() {
    for(int i = 0; i < 4; i++)
        m_spawners[i].nextFrame();
}

void MapPanel::UpdateBase() {
    m_base.nextFrame();
}

void MapPanel::reachBase() {
    vector<Enemy*>::iterator it;
    Player &player = Player::GetInstance();
    for(int i = 0; i < 4; i++)
        for(it = m_enemies[i].begin(); it != m_enemies[i].end(); it++) {
            if((*it)->reachedBase()) {
                m_base.decHealth(1);
                player.setLives(player.getLives() - 1);
                cout<<"Lives left: " << player.getLives()<<endl;
            }
        }
}

void MapPanel::Start() {
    for(int i = 0; i < 4; i++) {
        m_spawners[i].Start();
    }
}

void MapPanel::Pause() {
    for(int i = 0; i < 4; i++) {
        m_spawners[i].Pause();
    }
}

void MapPanel::UnPause() {
    for(int i = 0; i < 4; i++) {
        m_spawners[i].UnPause();
    }
}
