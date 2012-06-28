#include "../../include/Drawables/cScene.h"

void Scene::Draw(Application &App) {
    subDraw(App);
}

bool Scene::handleEvent(const sf::Input &Input) {
    return handleSubEvents(Input);
}

void Scene::moveObjects(const float x, const float y) {
    moveSubs(x, y);
}
