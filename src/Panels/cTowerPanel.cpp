
#include "../../include/Buttons/cTowerButton.h"
#include "../../include/Panels/cTowerPanel.h"

#include <iostream>
using namespace std;
TowerPanel::TowerPanel() {

    // create buttons (setting location, image, etc)
    // subAdd all the buttons

    TowerButton *temp = new TowerButton;
    m_button_image[0].LoadFromFile("media/Sprites/redcup.png");
    m_button_image[1].LoadFromFile("media/Sprites/water_balloon.png");
    m_button_image[2].LoadFromFile("media/Sprites/keg.png");
    m_button_image[3].LoadFromFile("media/Sprites/vodka.png");
    m_button_image[4].LoadFromFile("media/Sprites/dj.png");

    temp->SetImage(m_button_image[0]);
    temp->setDescription("Buy 50 red cups.\nCost: $10");
    temp->setCost(10);
    temp->SetPosition(sf::Vector2f(GetPosition().x+20.0f, GetPosition().y+80.0f));
    m_buttons.push_back(temp);

    temp = new TowerButton();
    temp->SetImage(m_button_image[1]);
    temp->setDescription("Buy water balloons\nCost: $5");
    temp->setCost(5);
    temp->SetPosition(sf::Vector2f(GetPosition().x+60.0f, GetPosition().y+80.0f));
    m_buttons.push_back(temp);

    temp = new TowerButton();
    temp->SetImage(m_button_image[2]);
    temp->setDescription("Purchasing a keg requires\nred cups.");
    temp->setCost(0);
    temp->SetPosition(sf::Vector2f(GetPosition().x+20.0f, GetPosition().y+120.0f));
    m_buttons.push_back(temp);

    temp = new TowerButton();
    temp->SetImage(m_button_image[3]);
    temp->setDescription("Purchasing hard alcohol\nrequires red cups.");
    temp->setCost(0);
    temp->SetPosition(sf::Vector2f(GetPosition().x+60.0f, GetPosition().y+120.0f));
    m_buttons.push_back(temp);

    temp = new TowerButton();
    temp->SetImage(m_button_image[4]);
    temp->setDescription("Purchasing a D.J. requires\nred cups");
    temp->setCost(0);
    temp->SetPosition(sf::Vector2f(GetPosition().x+20.0f, GetPosition().y+160.0f));
    m_buttons.push_back(temp);


    m_background.LoadFromFile("media/Sprites/towerpanelbg.png");
    SetImage(m_background);
    Player &player = Player::GetInstance();
    m_money.SetCount(player.getMoney());
    for(int i = 0; i < 5; i++) {
        m_button_pressed[i] = false;
    }
    m_press_guard = clock();
    Init();
    //cout<<m_buttons.size()<<endl;
}

void TowerPanel::Init() {
    m_selected_tower = NULL;
}

void TowerPanel::Draw(Application &App) {

    vector<TowerButton*>::iterator it_buttons;

    // Draw the Tower Panel background
    App.Draw(*this);
    // Draw Buttons
    for(it_buttons = m_buttons.begin(); it_buttons != m_buttons.end(); it_buttons++) {
        (*it_buttons)->Draw(App);
    }

    // Or you can add the following through subAdd() function
    m_money.Draw(App);
    m_desc_panel.Draw(App);
}

bool TowerPanel::handleEvent(const sf::Input& Input) {
    // Each Button handles its own input
    Player &player = Player::GetInstance();
    vector<TowerButton*>::iterator it_buttons;
    for(it_buttons = m_buttons.begin(); it_buttons != m_buttons.end(); it_buttons++) {
        (*it_buttons)->handleEvent(Input);
    }

    if(Input.IsKeyDown(sf::Key::C) && m_selected_tower != NULL
       && (m_press_guard + int(CLOCKS_PER_SEC*.5) < clock())) {
        cout<<"C pressed."<<endl;
        m_press_guard = clock();
        if(player.getMoney() >= 10){
            player.decreaseMoney(m_selected_tower->upgrade(0));
            m_money.SetCount(player.getMoney());

        }

    }
    if(Input.IsKeyDown(sf::Key::B) && m_selected_tower != NULL
       && (m_press_guard + int(CLOCKS_PER_SEC*.5) < clock())) {
        cout<<"B pressed."<<endl;
        m_press_guard = clock();
        if(player.getMoney() >= 5){
            player.decreaseMoney(m_selected_tower->upgrade(1));
            m_money.SetCount(player.getMoney());
        }
    }

    if(Input.IsKeyDown(sf::Key::K) && m_selected_tower != NULL
       && (m_press_guard + int(CLOCKS_PER_SEC*.5) < clock())) {
        cout<<"K pressed."<<endl;
        m_press_guard = clock();
        if(player.getMoney() >= 60){
            player.decreaseMoney(m_selected_tower->upgrade(2));
            m_money.SetCount(player.getMoney());
        }
    }
    if(Input.IsKeyDown(sf::Key::V) && m_selected_tower != NULL
       && (m_press_guard + int(CLOCKS_PER_SEC*.5) < clock())) {
        cout<<"V pressed."<<endl;
        m_press_guard = clock();
        if(player.getMoney() >= 40){
            player.decreaseMoney(m_selected_tower->upgrade(3));
            m_money.SetCount(player.getMoney());
        }
    }

    if(Input.IsKeyDown(sf::Key::M) && m_selected_tower != NULL
       && (m_press_guard + int(CLOCKS_PER_SEC*.5) < clock())) {
        cout<<"M pressed."<<endl;
        m_press_guard = clock();
        if(player.getMoney() >= 200*((m_selected_tower->getRadius()/5 )- 9)){
            player.decreaseMoney(m_selected_tower->upgrade(4));
            m_money.SetCount(player.getMoney());
        }
    }


    return true;
}

void TowerPanel::moveObjects(const float x, const float y) {

}

void TowerPanel::nextFrame() {
    // Call nextFrame() for each button
    vector<TowerButton*>::iterator it_buttons;
    string desc;
    Player &player = Player::GetInstance();
    m_money.SetCount(player.getMoney());
    stringstream tempDesc;


    // Iterate through all the towers to see if any of them are selected
    if(m_selected_tower != NULL){
        m_selected_tower->getStatus(desc);

        if(m_selected_tower->getAmmo() > 0){
            int kegs = m_selected_tower->getDamage() - 1;
            string keg;
            string alc;
            string mus;
            //desc = "Kegs at party: " + kegs + "\nPurchase a keg\nCost: $60";

            //tempDesc >> keg;
            //tempDesc.str("");
            tempDesc <<"This party has " << m_selected_tower->getAmmo() << "\nred cups.\n"
                     <<"buy 50 more for $10.";
            m_buttons.front()->setCost(10);
            m_buttons.front()->setDescription(tempDesc.str());
            //grey button logic...
            tempDesc.str("");
            tempDesc << "Kegs at party: " << kegs << "\nPurchase a keg\nCost: $60";
            m_buttons.at(2)->setDescription(tempDesc.str());
            tempDesc.str("");
            m_buttons.at(2)->setCost(60);

            float alcohol = (m_selected_tower->getAttackSpeed() -.25) * 10;//truncation problem fix!
            tempDesc << "Hard Alcohol at party: " << alcohol <<"\nPurchase hard alcohol\nCost: $40";
            //tempDesc >> alc;
            //tempDesc.str("");
            m_buttons.at(3)->setDescription(tempDesc.str());
            tempDesc.str("");
            m_buttons.at(3)->setCost(40);

            int costOfMusic = 200;
            int music = ((m_selected_tower->getRadius() - 80)/5) + 1;

            tempDesc << "Purchase Music Upgrade\nCost: $" << costOfMusic * music;
            //tempDesc >> mus;
            //tempDesc.str("");
            m_buttons.at(4)->setDescription(tempDesc.str());
            tempDesc.str("");
            m_buttons.at(4)->setCost(costOfMusic * music);


        }
        else{

            m_buttons.at(0)->setDescription("Buy 50 red cups.\nCost: $10\nCan't have a party\nwithout red cups!");
            m_buttons.at(0)->setCost(10);

            m_buttons.at(2)->setDescription("Purchasing a keg requires\nred cups.");
            m_buttons.at(2)->setCost(0);

            m_buttons.at(3)->setDescription("Purchasing hard alcohol\nrequires red cups.");
            m_buttons.at(3)->setCost(0);

            m_buttons.at(4)->setDescription("Purchasing a D.J. requires\nred cups");
            m_buttons.at(4)->setCost(0);

        }

        int balupg = int(m_selected_tower->getSingleDmg()/5);
        tempDesc.str("");
        tempDesc << "Buy water balloons\nCost:$5\nUpgrade: #" << balupg;
        m_buttons.at(1)->setDescription(tempDesc.str());
        m_buttons.at(1)->setCost(5);
        tempDesc.str("");
    }

    // Iterate through all the buttons to set their tint value if they are disabled or
    // to get their description if highlighted
    int j = 0;
    for(it_buttons = m_buttons.begin(); it_buttons != m_buttons.end(); it_buttons++) {
        // Tell the button the amount of money we have
        // If we have less than the cost of the upgrade...disable(darker tint) the button
        (*it_buttons)->disable(m_money.GetCount());
        (*it_buttons)->nextFrame();

        // If a button is highlighted and we aren't already displaying the status of a
        // tower(since it has precedence) have the description panel get the description
        // of the tower button to display.
        if((*it_buttons)->isHighlighted()) {
            (*it_buttons)->getDescription(desc);
            m_desc_panel.setDescription(desc);
            m_desc_panel.setHeader("Description");
        }

        /*
           if a tower is selected and a button is selected(and not disabled)
           upgrade the tower which will include setting new:
           - attack radius
           - attach damage
           - music?
           - sound?
           - image
        */
        if((m_selected_tower != NULL) && ((*it_buttons)->isPressed())&& !m_button_pressed[j]) {
            /*
            m_selected_tower->SetImage();
            m_selected_tower->setAttackRadius(float rad);
            m_selected_tower->setAttackDamage(int damage);
            m_selected_tower->setAttackSpeed(float atk_speed);
            */
            // Get new Status since Tower has been upgraded
            Player &player = Player::GetInstance();
            player.decreaseMoney(m_selected_tower->upgrade(j));
            m_selected_tower->getStatus(desc);
            m_desc_panel.setDescription(desc);
            m_desc_panel.setHeader("Status");
            //m_selected_tower->setSelected(false);
            //m_selected_tower = NULL;
           m_button_pressed[j] = true;
          // cout<<"pressed"<<endl;
            //(*it_buttons->)
        }

        if(!(*it_buttons)->isPressed()){
            //cout<<"button not pressed."<<endl;
            m_button_pressed[j] = false;
        }

        j++;
    }

    // set desc_panel private variables using public functions
    // for the header and the description then call nextFrame if
    // needed.
    m_money.nextFrame();
    m_desc_panel.nextFrame();

    // What the desc panel should do is keep the last description it had.
    // Should have an iterator through all the buttons and find one that
    // is highlighted(only one button possible at a time) and send its
    // description to the description panel.

}

void TowerPanel::setTowerPanelPosition(sf::Vector2f pos) {
    SetPosition(pos);
    m_money.SetPosition(pos.x+50.0f, pos.y+10.0f);
    m_desc_panel.setDescPanelPosition(sf::Vector2f(pos.x, pos.y+m_background.GetHeight()));


    m_buttons.at(0)->SetPosition(sf::Vector2f(GetPosition().x+50.0f, GetPosition().y+80.0f));
    m_buttons.at(1)->SetPosition(sf::Vector2f(GetPosition().x+130.0f, GetPosition().y+80.0f));
    m_buttons.at(2)->SetPosition(sf::Vector2f(GetPosition().x+50.0f, GetPosition().y+160.0f));
    m_buttons.at(3)->SetPosition(sf::Vector2f(GetPosition().x+130.0f, GetPosition().y+160.0f));
    m_buttons.at(4)->SetPosition(sf::Vector2f(GetPosition().x+50.0f, GetPosition().y+240.0f));
    //for(it_buttons = m_buttons.begin(); it_buttons != m_buttons.end(); it_buttons++) {
        //(*it_buttons)->SetPosition(pos.x+20.0f, pos.y+80.0f);
    //}
}

