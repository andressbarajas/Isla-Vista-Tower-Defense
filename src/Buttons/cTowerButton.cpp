
#include "../../include/Buttons/cTowerButton.h"

void TowerButton::Draw(Application &App) {
    App.Draw(*this);

	subDraw(App);
}

void TowerButton::nextFrame() {
  // handled during handleEvent()
  //buttonEvent();

  // set tint to dark if button is disabled or doesn't allow for the specific tower


}

void TowerButton::buttonEvent() {

    //if clicked

    //if highlighted

}

void TowerButton::getDescription(string &desc) {
    desc = m_tower_desc;
}

void TowerButton::disable(unsigned int money) {
    // If the amount of money we have is greater than or equal to the cost of the upgrade
    // the upgrade tower button is not disabled
    if(money >= m_cost) {
        setDisabled(false);
        return;
    }
    // If the cost of the upgrade is greater than the amount of money we have the button
    // is disabled
    setDisabled(true);
}


