#include "hand.h"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

//split string helper function
std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::string token;
    std::stringstream ss(str);  // Create a stringstream from the input string

    // Extract substrings separated by the delimiter
    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}


Hand::Hand(){
  
}

Hand::Hand(std::string hand, int player_c) {
    card_one = {'0','0'};
    card_two = {'0','0'}; 
    _hand = "72";

    card_one.at(0) = hand.at(0);  // Card one first character
    card_one.at(1) = hand.at(1);  // Card one second character
    card_two.at(0) = hand.at(2);  // Card two first character
    card_two.at(1)= hand.at(3);  // Card two second character
    player_count = player_c;
}


std::string Hand::get_hand_value(){
    
    // check if suited
    bool suited = false;

    if(card_one[1] == card_two[1]){
        suited = true;
    }

    // check if connectors 
    bool connectors = false;

    int first_card_number;

    switch(card_one.at(0)){
        case '2': first_card_number = 2; break;
        case '3': first_card_number = 3; break;
        case '4': first_card_number = 4; break;
        case '5': first_card_number = 5; break;
        case '6': first_card_number = 6; break;
        case '7': first_card_number = 7; break;
        case '8': first_card_number = 8; break;
        case '9': first_card_number = 9; break;
        case 'T': first_card_number = 10; break;
        case 'J': first_card_number = 11; break;
        case 'Q': first_card_number = 12; break;
        case 'K': first_card_number = 13; break;
        case 'A': first_card_number = 14; break;
        default: first_card_number = 0; break;
    }

    int second_card_number;
    switch(card_two.at(0)){
        case '2': second_card_number = 2; break;
        case '3': second_card_number = 3; break;
        case '4': second_card_number = 4; break;
        case '5': second_card_number = 5; break;
        case '6': second_card_number = 6; break;
        case '7': second_card_number = 7; break;
        case '8': second_card_number = 8; break;
        case '9': second_card_number = 9; break;
        case 'T': second_card_number = 10; break;
        case 'J': second_card_number = 11; break;
        case 'Q': second_card_number = 12; break;
        case 'K': second_card_number = 13; break;
        case 'A': second_card_number = 14; break;
        default: second_card_number = 0; break;
    }


    if(first_card_number - 1 == second_card_number){
        connectors = true;
    }

    // Build hand string to search
    std::string hand_string;
    hand_string.push_back(card_one.at(0));
    hand_string.push_back(card_two.at(0));
    if(connectors){
        if(suited){
            hand_string += 's';
        }else{
            hand_string += 'o';
        }
    }

    _hand = hand_string;
    // get percent 

    std::ifstream fin;
    fin.open("hand_chart.csv");

    if (!fin.is_open()){ 
        std::cout <<" FAILED TO OPEN INPUT FILE";
        return "FAILED TO OPEN INPUT FILE"; 
    }

    std::string line;
    std::string output;

    for(int i = 0; i <= 114; i++){
        
        fin >> line;
        if(line.substr(0,hand_string.length()) ==  hand_string){
            
            std::vector<std::string> result = splitString(line, ',');

            output = result.at(player_count-1);
        }
    }




    return output;
}


int Hand::calculate_bet(std::string win_percentage, std::string hand, int stack) {
    double bet = 0.0;

    // Remove "%" from win_percentage string and convert to double
    win_percentage = win_percentage.substr(0, win_percentage.size() - 1);  // Remove the "%" symbol
    double win_percentage_value = std::stod(win_percentage);  // Convert to double

    // Check for premium hands
    if (hand == "AA" || hand == "KK" || hand == "QQ" || hand == "AKs" || hand == "AKo") {
        // Premium hands get a high base bet, regardless of win percentage
        bet = 1.0;  // You can adjust this value as needed
    }
    else {
        // Adjust bet based on win percentage
        if (win_percentage_value >= 80.0) {
            bet = .8;  // High bet for very strong hands
        }
        else if (win_percentage_value >= 60.0) {
            bet = .50;   // Moderate bet for medium-strength hands
        }
        else if (win_percentage_value >= 40.0) {
            bet = .20;   // Low bet for weaker hands
        }
        else {
            bet = 0.0;    // Fold (no bet) for very weak hands
        }
    }

    // Scale bet relative to the player's stack size
    return stack * bet;
}

