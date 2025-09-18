#include <iostream>
#include <fstream>
#include <string> 

#include "hand.h"
#include "Array.hpp"


using namespace std;

int main(){

    
    Array<string> hand_array; 
    int endingIndex = 0 ;
    bool running = true;


    cout << "\nnPoker Pre-flop Bot: \n----------------------------------------------------------------------------------\n"<< endl;
     
    while(running){

        // get players hand
        string player_hand;
        cout << "What Hand did you get, please put them in order from highest to lowest:";
        cin >> player_hand;
        int number_of_players;
        cout << "How many people are playing at your table(2-9): " ;
        cin >> number_of_players;
        int stack;
        cout << "How many chips do you have: " ;
        cin >> stack;
        
        Hand hand(player_hand, number_of_players);
 
        //Percent win
        cout << "Your hand wins " << hand.get_hand_value() << " of the time"<< endl;
        //how much you can bet 
        cout << "You can bet or call up to: " << hand.calculate_bet(hand.get_hand_value(), hand._hand, stack)<< " chips."<< endl;


        // ask player if they playing another hand 
        char again;
        cout << "Are you playing another hand (y/n): ";
        cin >> again;
        hand_array.insert( endingIndex, hand._hand);
        endingIndex ++;
        
        if(again == 'n' || again == 'N') {
            running = false;
        }


    }
    //

    string hands_played = "";
    for(int i = 0; i < hand_array.size(); i++){
        hands_played += " " + hand_array.get(i);

    }
    
    cout << "Thank You for using the Pre-flop Poker Bot during this session you we dealt these hands: " << hands_played << endl;

    return 0;
}

