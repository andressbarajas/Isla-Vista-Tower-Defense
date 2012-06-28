#ifndef PLAYER_H
#define PLAYER_H

/**
* Class: Player
* Purpose: keep track of data that is related to the user
* Contains data such as the user's money, score, and lives
*/

class Player
{
    public:

        virtual ~Player();
        /**
        * Function: GetMoney
        * function getter for _money
        * Pre-conditions: none
        * Post-Conditions: _money returned
        */
        int getMoney();
        /**
        * Function: increaseMoney
        * function increases _money by an amount
        * Pre-conditions: none
        * Post-Conditions: _money is increased by amount
        */
        void increaseMoney(int amount);
        /**
        * Function: decreaseMoney
        * function decreases _money by an amount
        * Pre-conditions: none
        * Post-Conditions: _money is decreased by amount
        */
        void decreaseMoney(int amount);

        void setMoney(int amount){m_money = amount;}
        /**
        * Function: getScore
        * function getter for _score
        * Pre-conditions: none
        * Post-Conditions: _score returned
        */
        int getScore();
        /**
        * Function: increaseScore
        * function increases _score by an amount
        * Pre-conditions: none
        * Post-Conditions: _score is increased by amount
        */
        void increaseScore(int amount);
        /**
        * Function: setLives
        * function setter for _lives
        * Pre-conditions: none
        * Post-Conditions: _lives is set to amount lives
        */
        void setLives(int lives);

        void setMoney(unsigned int money) { m_money = money; }
        /**
        * Function: getLives
        * function getter for _lives
        * Pre-conditions: none
        * Post-Conditions: _lives returned
        */
        int getLives();
        /**
        * Function: isDead
        * function checks if player is dead
        * Pre-conditions: player exists
        * Post-Conditions: user is checked if dead or alive
        */
        bool isDead();

        /**
    * Function: GetInstance
    * Is used to get the only instance of the Player class.
    * Pre-conditions: None
    * Post-conditions: The only instance of Player class is returned.
    */
	static Player& GetInstance() {
        static Player instance;
        return instance;
    }



protected:
    /**
    * The following constructors are used to help prevent additional creations of the
    * Player class.
    */
    Player();                             // Private constructor
    Player(const Player&);              // Prevent copy-construction
    Player& operator= (const Player&);  // Prevent assignment

    private:
        int m_score;
        int m_lives;
        int m_money;
};

#endif // PLAYER_H
