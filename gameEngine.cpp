#include "gameEngine.h"
#include "player.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>

constexpr auto newline = "\n";

void GameEngine::saveGame()
{
    std::ofstream saveGame("gameState.txt"); 

    for (auto player : players)
    {
        saveGame << player.getName() << " " << player.getScore() << newline; 
    }

    saveGame << "LIMITS " << minScoretoUpdate << " " << minScoretowin; 
}

char GameEngine::welcomeMessage() 
{

    char option;

    std::cout << "\nRoll Again?(r) or Bank Points(b)? or Show scores(s) or Save and Quit(q)?" << newline;
    std::cin >> option;

    return option;

}

int GameEngine::countScore() 
{
    int numCount, tempScore, singles, pairs, triplets, fourfold, pairofone, pairoffive;

    numCount = 0; 
    tempScore = 0; 
    singles = 0; 
    pairs = 0; 
    triplets = 0; 
    fourfold = 0; 
    pairofone = 0;
    pairoffive = 0; 

    for (int counter = 1; counter < 7; counter++)
    {
        numCount = count(bank.begin() , bank.end(), counter);

        switch (numCount)
        {
        case 1: 
        case 2:

            if (numCount == 1)
            {
                singles++; 
            }
            else
            {
                pairs++; 
            }

            if (counter == 1)
            {
                tempScore += (100 * numCount);

                if (numCount == 2)
                {
                    pairofone++; 
                }
            }

            else if (counter == 5)
            {
                tempScore += (50 * numCount); 

                if (numCount == 2)
                {
                    pairoffive++; 
                }
            }

            break; 

        case 3:

            triplets++; 
            
            if (counter == 1)
            {
                tempScore += 300; 
            }

            else
            {
                tempScore += (100 * counter); 
            }

            break; 

        case 4:
            fourfold++; 
            tempScore += 1000; 
            break; 

        case 5:
            tempScore += 2000; 
            break; 

        case 6:
            tempScore += 3000; 
            break; 

        default:
            break; 
        }

        if (singles == 6 || pairs == 3 || (fourfold == 1 && pairs == 1))
        {
            tempScore = 1500; 
        }

        else if (triplets == 2)
        {
            tempScore = 2500; 
        }
    }

    std::cout << newline <<"Score in this turn: " << tempScore << newline; 
    return tempScore; 
}

void GameEngine::bankDices() {

    char choice;

    std::cout << "\nWhich dices you wanna bank?" << newline;

    for (int counter = 0; counter < points.size(); counter++) 
    {

        if (points.at(counter) != 0)
        {
            std::cout << "Dice " << counter + 1 <<
                ": Bank(b) or Roll(r)??" << newline;
            std::cin >> choice;

            if (choice == 'b')
            {

                bank.push_back(points.at(counter));
                dices.at(counter).changeState(); 
                bankedDiceCounter++; 

            }
        }    
    }

    points.clear(); 
}

void GameEngine::startGame() {

    int playerTracker, keeper, score = 0;

    std::ifstream file2("gameState.txt"); 

    if (file2.is_open())
    {
        file2.seekg(0, std::ios::end); 
    }


    char choice = 'a';

    std::cout << "\n\t\t\t\t\t  Welcome to the  FARKLE game.\n\t\t\t\t\t    Press Enter to continue." << newline;
    std::cin.ignore(); 

    if (file2.tellg() != 0)
    {
        char decision;
        std::cout << "Load saved game?? ";
        std::cin >> decision;

        if (decision == 'y')
        {
            loadGame();
        }
        else
        {
            createPlayers();
            selectLevel(); 
        }
    }
    else
    {
        createPlayers();
        selectLevel();

    }

    std::cout << "\nLets play Farkle!!!" << newline;

    playerTracker = 0;

    for (; playerTracker < numberofplayers; playerTracker++) {

        bool state = true;

        while (state) {

            if (choice != 'a') {
                choice = welcomeMessage();
            }

            switch (choice)
            {
            case 'a':

                dices.clear(); 
                createDices(); 
                std::cout << newline << newline <<players[playerTracker].getName() << "'s turn. \n\nRolling the dices: \n" << newline;
                rollDices();

                bankedDiceCounter = 0; 
                bank.clear(); 

                bankDices();
                keeper = countScore();

                if (keeper == 0) {
                    std::cout << "\n+++++++++++++++++++++++++++++++++\n\t.....Farkled.....\n+++++++++++++++++++++++++++++++++" << newline;
                    state = false;

                    if (playerTracker == numberofplayers - 1) {
                        playerTracker = -1;
                    }

                    break;
                }

                score += keeper;

                choice = 'm';
                break;

            case 'r':

                if (bankedDiceCounter == 6) {
                    std::cout << "\nNo Dice left." << newline;
                   std::cout << players[playerTracker].getName() << " scored: " << players[playerTracker].getScore() << "\n\n" << newline;
                    state = false;
                    score = 0;
                    choice = 'a'; 
                    break;
                }

                std::cout << "\nRolling " << 6 - bankedDiceCounter << " dices again!" << newline;
                rollDices(); 

                bank.clear(); 
                bankDices();

                keeper = countScore();

                if (keeper == 0) {
                    std::cout << "\n+++++++++++++++++++++++++++++++++\n\t.....Farkled.....\n+++++++++++++++++++++++++++++++++" << newline ;
                    state = false;

                    choice = 'a'; 
                    break;
                }
                score += keeper;
                keeper = 0;
                break;

            case 'b':

                if (score >= minScoretoUpdate) {
                    std::cout << "Score updated!" << newline;
                    players[playerTracker].updateScore(score);

                    if (players[playerTracker].getScore() >= minScoretowin) {

                        std::cout << "\n\n\n" << players[playerTracker].getName() <<" scored: " << players[playerTracker].getScore() << ".\n>>>>> WINNER <<<<<" << newline; 
                        state = false; 
                        playerTracker = 5; 

                    }

                }
                else {

                    std::cout << "Not enough Score to update the score." << newline;

                }


                score = 0;
                state = false; 
                choice = 'a';
                break;

            case 's':

                for (auto player : players)
                {
                    std::cout << player.getName() << "'s score is: " << player.getScore() << newline; 
                }
                break;

            case 'q':

                saveGame();

                state = false; 
                playerTracker = 5; 

                break;


            default:
                state = false;
                break;
            }
        }

        if (playerTracker == numberofplayers - 1)
        {
            playerTracker = -1;
        }

    }
}

void GameEngine::rollDices()
{
    int point; 

    std::cout << newline; 

    for (auto dice : dices)
    {
        point = dice.roll(); 
        
        if (point != 0)
        {
            std::cout << point << " "; 
        }

        points.push_back(point); 
    }

    std::cout << newline; 
}

void GameEngine::createDices()
{
    for (int counter = 0; counter < 6; counter++)
    {
        dices.push_back(Dice()); 
    }
}

void GameEngine::selectLevel()
{
    char choice; 
    std::cout << newline << newline << "Select a level: \n\n\ta. Rookie\n\tb. Roller\n\tc. High Roller" << newline; 
    std::cout << newline << newline << "See the GamePlay for details about the levels." << newline; 

    std::cin >> choice; 

    switch (choice)
    {
    case 'a':

        minScoretoUpdate = 200; 
        minScoretowin = 5000; 

        break; 

    case 'b':

        minScoretoUpdate = 350; 
        minScoretowin = 8000; 
        break; 

    case 'c':

        minScoretoUpdate = 500; 
        minScoretowin = 15000; 
        break; 

    default:

        minScoretoUpdate = 200; 
        minScoretowin = 5000;
        break; 
    }

    std::cout << "Minimum score to save score set to: " << minScoretoUpdate << "." << newline;
    std::cout << "Minimum score to win set to: " << minScoretowin << "." << newline << newline;
}

void GameEngine::createPlayers() 
{

    bool state = true;
    std::string name;

    while (state) {

        std::cout << "How many players?" << newline;
        std::cin >> numberofplayers;

        if (numberofplayers < 5 && numberofplayers > 0) {

            for (int counter = 0; counter < numberofplayers; counter++) {

                std::cout << "\nEnter player" << counter + 1 << "'s name: " << newline;
                std::cin >> name;
                players.push_back(Player(name));
            }

            state = false;

        }

        else {

            std::cout << "Maximum 4 players can play. Try again." << newline;

        }
    }
}

void GameEngine::loadGame()
{
    int score; 
    std::string line;
    std::ifstream file1("gameState.txt"); 

    numberofplayers = 0; 

    while (getline(file1, line))
    {
        if (line.substr(0, line.find(" ")) != "LIMITS")
        {
            players.push_back( Player( line.substr(0, line.find(" ")) ));

            std::stringstream converter(line.substr(line.find(" ") + 1)); 
            converter >> score; 

            players.back().updateScore(score);
            numberofplayers++;
        }

        else
        {
            line = line.substr(line.find(" ") + 1);

            std::stringstream converter(line);

            converter >> score; 
            minScoretoUpdate = score; 

            converter >> score; 
            minScoretowin = score;                         
        }

    }
    file1.close(); 

    std::ofstream file3("gameState.txt");
    file3.close();

    for (auto player : players)
    {
        std::cout << player.getName() << " " << player.getScore() << newline; 
    }
     
}

void GameEngine::introduction()
{
    std::string line; 
    std::ifstream file1("rules.txt"); 

    while (getline(file1, line))
    {
        std::cout << line << newline; 
    }
}

GameEngine::GameEngine() {
    startGame();
}
