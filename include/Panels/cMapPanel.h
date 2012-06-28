
#ifndef _MAPPANEL_H_
#define _MAPPANEL_H_

#include <deque>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <SFML/System/Vector2.hpp>

#include "../sMovement.h"
#include "../SFMLMappy.h"
#include "../cHomeBase.h"
#include "cPanelInterface.h"
#include "../Towers/cTower.h"
#include "../Enemies/cEnemy.h"
#include "../Enemies/cSpawner.h"


/*
   Inherits PanelInterface class and holds the SFMLMappy variable instance.  Deals with
   interactions between the map and enemies/towers such as collision detection/tower
   placement.
*/
class MapPanel : public PanelInterface {
public:
    /**
    * Constructor
    * Currently makes the imgset
    * Pre-conditions:
    * Post-conditions:
    */
    MapPanel();

    virtual ~MapPanel() {}

    void Init();

    /**
    * Function: Draw
    * Draws panel onto the Application Window
    * Pre-conditions: There is an existing application window
    * Post-conditions: This panel was drawn onto the application window.
    */
    virtual void Draw(Application &App);
    /**
    * Function: handleEvent
    * function handles input events that may occur inside the panel.
    * **CURRENTLY EMPTY**
    * Pre-conditions: An event has occured.
    * Post-conditions: The event was handled.
    */
    virtual bool handleEvent(const sf::Input& Input);
    /**
    * Functin: moveObjects
    * moves child objects. see SpriteObj for more details.
    * ***CURRENTLY EMPTY***
    * Pre-conditions: nothing.
    * Post-conditions: Moves childeren with the panel.
    */
    virtual void moveObjects(const float x, const float y);
    /**
    * Function: nextFrame
    * Called each couple of frames.
    * Pre-conditions: nothing
    * Post-conditions: Operations intended to be called frame by frame
    * occur here.
    */
    virtual void nextFrame();

    /* SFML Mappy Functions */
    void SetMap(const char* map_name);
    void SetMapDimension(sf::Vector2f map_dim);
    void SetStartPosition(sf::Vector2f start_posi);
    void GenerateMapLookUp();

    /* Enemy Functions */
    /**
    * Function: GenerateWave
    * Generates Enemy objects stores them in m_enemies vector
    * Pre-conditions: Wave is intended to be initiated. (By player)
    * Post-conditions: A collection of enemy objects was created.
    * and set on map.
    * ***Currently has dummy difficulty***
    */
    //void GenerateWave(int difficulty);
    /**
    * Function: MoveEnemies
    * Calls for enemies to navigate themselves.
    * Pre-conditions: wave has been generated.
    * there are Enemy objects that need moving.
    * Post-conditions: All objects in m_enemies Enemy object
    * collection have navigated themselves.
    */
    void UpdateEnemies();

    void UpdateTowers();

    void UpdateSpawner();

    void UpdateBase();

    void CreateEnemies();

    void setPath(const deque<Movement> & movement) { m_path = movement; }

    void reachBase();

    inline Tower* getSelectedTower() { return m_selected_tower; }

    void Start();

    void Pause();

    void UnPause();

private:
    SFMLMappy m_map;              // SFML mappy object the map.
    vector<Enemy*> m_enemies[4];     // Collection of Enemy monsters.
    vector<Tower*> m_towers;      // Collection of Towers
    Tower *m_selected_tower;
    deque<Movement> m_path;
    Spawner m_spawners[4];
    HomeBase m_base;

    sf::Image m_imgset[6];             // Image set referenced by enemies:N,E,S,W


};

#endif
