#include <iostream> 
#include <ctime> 
#include <random>
#include <vector> 
#include <bits/stdc++.h>

using namespace std;

class Dice {
    public: 
        vector<int> roll(int = 6); 
}; 

vector<int> Dice::roll(int numofDice) {

    int random; 
    vector<int> points; 

    mt19937 generator; 
    generator.seed(time(NULL)); 

    uniform_int_distribution<uint32_t> dice(1, 6); 

    for (int counter = 0; counter < numofDice; counter++) {

        random = dice(generator); 
        cout << random << endl; 
        points.push_back(random); 

    }

    return points; 
}


class Player {

    private: 
        string name; 
        int score = 0; 
    
    public: 
        string getName(){
            return name; 
        }
        int getScore(){
            return score; 
        }
        void updateScore(int score){
            this-> score = this-> score + score; 
        }
        Player(string); 
};

Player::Player(string name){
    this -> name = name; 
}


class GameEngine {

    public: 
        Dice dice; 
        vector<int> points, bank;      
   
        GameEngine(); 
        void startGame(); 
        void bankDices(); 
        int countScore(); 
        char choiceMessage(); 
}; 

char GameEngine::choiceMessage(){

    char option; 

    cout << "\nRoll Again?(r) or Bank Points(b)? or Show scores(s)?" << endl; 
    cin >> option; 

    return option; 

}

int GameEngine::countScore(){

    int numCount, tempScore, singles, pairs, pairofone, pairoffive, tempTripletScore, triplets;
    tempScore = 0; 
    singles = 0; 
    pairs = 0; 
    pairofone = 0; 
    pairoffive = 0;   
    tempTripletScore = 0;  
    triplets = 0; 
    numCount = 0; 

    for (int counter = 1; counter <= 6; counter++) {

        numCount = count(bank.begin() + 6 - points.size(), bank.end(), counter); 

        switch (numCount) {
            case 1:
            case 2: 

                if (numCount == 1){
                    singles += 1; 
                }
                else
                {
                    pairs += 1; 
                }

                if (counter == 1){
                    tempScore += (100 * numCount); 

                    if (numCount == 2){
                        pairofone++; 
                    }

                    break; 
                } 

                else if (counter == 5){
                    tempScore += (50 * numCount); 

                    if (numCount == 2){
                        pairoffive++; 
                    }

                    break; 
                }

                else{
                    break; 
                }
            case 3: 
                triplets += 1; 

                if (counter == 1){
                    tempTripletScore += 300; 
                    break; 
                }
                else{
                    tempTripletScore += (counter*100); 
                    break; 
                }
            case 4: 
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

    }

    if (singles == 6){
        tempScore = tempScore - 150 + 1500; 
    }
    else if (pairs == 3) {
        tempScore = tempScore - (pairofone * 200) - (pairoffive * 100) + 1500; 
    }
    
    if (triplets == 2) {
        tempScore += 2500;     
    }
    else{
        tempScore += tempTripletScore; 
    }

    cout<< "\nScore in this trun:" << tempScore << "\n\n" << endl; 

    return tempScore; 
}

void GameEngine::bankDices(){

    char choice;

    cout << "\nWhich dices you wanna bank?" << endl; 

    for (int counter = 0; counter < points.size(); counter++){

        cout<< "Dice "<< counter+1 << 
            ": Bank(b) or Roll(r)??" << endl; 
        cin >> choice; 

        if (choice =='b'){
            bank.push_back(points.at(counter)); 
            points.at(counter) = 0; 
        }
    }
}

void GameEngine::startGame(){

    string name; 
    int keeper, score = 0; 
    bool state = true; 
    char choice = 'a'; 

    cout << "\n\t\t\tWelcome To the FARCLE game. Press Enter to continue." << endl; 
    cin.ignore(); 
    cout << "Enter your name: "; 
    cin >> name; 

    Player player1(name); 

    cout << "\n\nHello "<< player1.getName() << 
        " !!! Lets play Farkle!!!\n" << endl;  
    
    while (state){

        if (choice != 'a'){
            choice = choiceMessage(); 
        }

        switch (choice)
        {
            case 'a':

                cout<< "Rolling the dices: \n" << endl; 
                points = dice.roll();

                bankDices();
                keeper = countScore(); 

                if (keeper == 0){
                    cout << "\nFarkled!!!" << endl; 
                    state = false; 
                    break; 
                }
                score += keeper; 

                choice = 'q'; 
                break; 
            
            case 'r': 

                if (bank.size() == 6){
                    cout<< "\nNo Dice left" << endl; 
                    cout << player1.getName() << " scored: " << player1.getScore() << "\n\n" << endl; 
                    cout << "\nStart Again? yes(y) or no(n)?" << endl; 
                    cin >> choice; 

                    if (choice == 'y'){
                        bank.clear(); 

                        break; 
                    }
                    else{
                        state = false; 
                        score = 0; 
                        break; 
                    }
                }

                cout << "\nRolling " << 6 - bank.size() << " dices again!" << endl; 
                points.clear();
                points = dice.roll(6 - bank.size());  

                bankDices(); 
                
                keeper = countScore(); 

                if (keeper == 0){
                    cout << "\nFarkled!!!" << endl; 
                    state = false; 
                    break; 
                }
                score += keeper; 
                keeper = 0; 
                break; 
            
            case 'b':

                if (score >= 500) {
                    cout << "Score updated!" << endl; 
                    player1.updateScore(score); 
                   
                }
                else {
                    cout << "Not enough Score to add on the board.\n\nTry again!" << endl; 

                }
                score = 0; 
                break; 
            
            case 's':

                cout << player1.getName() << "'s score is : " << player1.getScore()<< "\n\n" << endl; 
                break; 
            

            default:
                state = false; 
                break;
        }
    }
}

GameEngine::GameEngine() { 
    startGame(); 
}


int main() { 
    GameEngine Engine1; 
}