#include "dice.h"
#include <random> 
#include <ctime>
#include <iostream>

using namespace std;

int Dice::roll() {

    int random; 

    random_device random_gen; 
    mt19937 generator(random_gen());
    uniform_int_distribution<uint32_t> dice(1, 6);
    
    if (!freeze)
    {
        return dice(generator); 
    }

    cout << " Freezed "; 

    return 0; 
}

void Dice::changeState()
{
    if (freeze)
    {
        freeze = false; 
    }

    else
    {
        freeze = true; 
    }
}
