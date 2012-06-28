

#include "../../include/Drawables/cBanner.h"

Banner::Banner(sf::Image &image) {

	SetImage(image);
}

void Banner::Draw(Application &App) {

	App.Draw(*this);

	SpriteObj::subDraw(App);
}

void Banner::moveObjects(const float x, const float y) {

    Move(x, y);

    moveSubs(x, y);
}
