
#include <iostream>

#include "../include/cLevelGen.h"
#include "../include/Menus/cTitle.h"
#include "../include/Menus/cMainMenu.h"

using namespace std;

void LevelGen::Init() {
    m_level = new Level();
}

void LevelGen::Cleanup() {
    delete m_level;
}

void LevelGen::DoState() {

     m_level->DoLevel();
     PopState();
}
