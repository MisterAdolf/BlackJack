#include <iostream>
#include <vector> //dynamic array which can automaticaly changes its size when items are added or removed
#include <cstdlib> // library contains functions for memory management, data conversion, random number generation, and program termination
#include <ctime>

using namespace std;

const int BLACKJACK = 21;
const int DEALER_THRESHOLD = 17;

int draw_card() {            //Generate random card (1-13)
    return rand() % 13 + 1;
}

int card_value(int card) {    //Function to get card value
    if (card > 10) return 10; // Face cards (J, Q, K)
    if (card == 1) return 11; // Ace is initially worth 11
    return card;
}

int calculate_score(const vector<int>& hand) { //function for count score
    int score = 0;
    int aces = 0;

    for (int card : hand) {
        score += card_value(card);
        if (card == 1) aces++;
    }

    while (score > BLACKJACK && aces > 0) {
        score -= 10; // Convert Ace from 11 to 1
        aces--;
    }

    return score;
}

void print_hand(const vector<int>& hand, const string& owner) {   //function for print cards from the players or dealers hand
    cout << owner << "'s hand: ";
    for (int card : hand) {
        cout << card << " ";
    }
    cout << "(Score: " << calculate_score(hand) << ")\n";
}

void play_blackjack() {  //Two cards are deal to the player and dealer
    srand(time(0));

    vector<int> player_hand;
    vector<int> dealer_hand;

    player_hand.push_back(draw_card());
    player_hand.push_back(draw_card());
    dealer_hand.push_back(draw_card());
    dealer_hand.push_back(draw_card());

    cout << "Welcome to Blackjack!\n";

    bool player_stands = false;   //player choose hit or stand, if player have 21 points> he lose
    while (!player_stands && calculate_score(player_hand) <= BLACKJACK) {
        print_hand(player_hand, "Player");
        print_hand(vector<int>{dealer_hand[0]}, "Dealer (showing)");

        cout << "Do you want to hit or stand? (h/s): ";
        char choice;
        cin >> choice;

        if (choice == 'h') {
            player_hand.push_back(draw_card());
        }
        else if (choice == 's') {
            player_stands = true;
        }
        else {
            cout << "Invalid input. Please type 'h' to hit or 's' to stand.\n";
        }
    }

    int player_score = calculate_score(player_hand); // points of the player and the dealer are compared.
    if (player_score > BLACKJACK) {
        print_hand(player_hand, "Player");
        cout << "You lose dealer wins\n";
        return;
    }

    cout << "\nDealer's turn...\n";   // dealer takes cards as while his points are less than 17. If dealer have 21 points> , he loses
    
    while (calculate_score(dealer_hand) < DEALER_THRESHOLD) {
        dealer_hand.push_back(draw_card());
    }
    
    int dealer_score = calculate_score(dealer_hand); // points of the player and the dealer are compared. A winner or a draw is declared.

    
    print_hand(player_hand, "Player");
    print_hand(dealer_hand, "Dealer");

    if (dealer_score > BLACKJACK || player_score > dealer_score) {
        cout << "you win\n";
    }
    else if (dealer_score == player_score) {
        cout << "It's a draw\n";
    }
    else {
        cout << "dealer wins\n";
    }
}

int main() {
    play_blackjack();
    return 0;
}
