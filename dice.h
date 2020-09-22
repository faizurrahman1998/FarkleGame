#ifndef DICE_H 
#define DICE_H  

class Dice 
{
public:

    bool freeze = false;

    int roll();
    void changeState(); 
};

#endif