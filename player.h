#ifndef PLAYER_H 
#define PLAYER_H

#include <string>


class Player {

private:
    std::string name;
    int score = 0;

public:
    std::string getName() const
    {
        return name;
    }
    int getScore() const
    {
        return score;
    }
    void updateScore(int score) {
        this->score = this->score + score;
    }
    Player(std::string);
};

#endif