
#include "../include/cGamePlay.h"
#include "../include/cGameStateBase.h"

void GameStateBase::ChangeState(GameStateBase* state) {
    GamePlay &game = GamePlay::GetInstance();
    game.ChangeState(state);
}

void GameStateBase::PushState(GameStateBase* state) {
    GamePlay &game = GamePlay::GetInstance();
    game.PushState(state);
}

void GameStateBase::PopState() {
    GamePlay &game = GamePlay::GetInstance();
    game.PopState();
}

