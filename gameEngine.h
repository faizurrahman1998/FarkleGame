#ifndef GAMEENGINE_H 
#define GAMEENGINE_H

#include "dice.h"
#include "player.h"
#include <vector>

class GameEngine 
{

public:

    int numberofplayers, bankedDiceCounter, minScoretoUpdate, minScoretowin; 

    std::vector<Dice> dices;
    std::vector<int> points, bank;
    std::vector<Player> players;

    GameEngine();
    static void introduction(); 
    void createPlayers();
    void selectLevel();
    void rollDices(); 
    void createDices(); 
    void startGame();
    char welcomeMessage();
    void bankDices();
    int countScore();
    void saveGame(); 
    void loadGame(); 
 
};

#endif 