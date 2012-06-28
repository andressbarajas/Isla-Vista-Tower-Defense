
#include "../../include/Buttons/cBasicButton.h"

void BasicButton::Draw(Application &App) {
    App.Draw(*this);

	subDraw(App);
}
