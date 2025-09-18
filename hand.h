#ifndef HAND_H
#define HAND_H

#include <string>
#include <vector>

class Hand{
    public:
    //defult construtor and distructor 
    Hand();

    //constructor
    Hand(std::string hand, int player_c); 

    //get hand value function
    std::string get_hand_value();
    
    //how strong is you hand
    int calculate_bet(std::string win_percentage, std::string hand, int stack);

    // hand string 
    std::string _hand;
    private:
    std::vector<char> card_one;
    std::vector<char> card_two;

    

    int player_count;
    



};



#endif