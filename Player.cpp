#include "Player.h"
#include <iostream>

Player::Player(int playerId,int teamId,int gamesPlayed,int goals,int cards,bool goalKeeper)
    :
    playerId(playerId),
    teamId(teamId),
    gamesPlayed(gamesPlayed),
    goals(goals),
    cards(cards),
    goalKeeper(goalKeeper),
    teamGamesPlayedOnArrival(0)
    {}

Player::~Player(){  
}

// getters
int Player::getPlayerId() const{
    return playerId;
}
int Player::getTeamId() const{
    return teamId;
}
int Player::getGamesPlayed() const{
    return gamesPlayed;
}
int Player::getGoals() const{
    return goals;
}
int Player::getCards() const{
    return cards;
}
bool Player::getIsGoalKeeper() const{
    return goalKeeper;
}
int Player::getTeamGamesPlayedOnArrival () const {
    return teamGamesPlayedOnArrival;
}

// setters
void Player::setPlayerId(int newPlayerId){
    playerId = newPlayerId;
}
void Player::setTeamId(int newTeamId){
    teamId = newTeamId;
}
void Player::setGamesPlayed(int newGamesPlayed){
    gamesPlayed = newGamesPlayed;
}
void Player::setGoals(int newGoals){
    goals = newGoals;
}
void Player::setCards(int newCards){
    cards = newCards;
}
void Player::setIsGoalKeeper(bool isGoalKeeper){
    goalKeeper = isGoalKeeper;
}
void Player::setTeamGamesPlayedOnArrival (int numOfTeamGamesPlayedOnArrival){
    teamGamesPlayedOnArrival = numOfTeamGamesPlayedOnArrival;
}

// operators
bool operator==(const Player& p1, const Player& p2){
    return p1.getPlayerId() == p2.getPlayerId();
}
bool operator!=(const Player& p1, const Player& p2){
    return !(p1==p2);
}


bool operator<(const Player& p1, const Player& p2){
    return p2 > p1;
}

bool operator>(const Player& p1, const Player& p2){
    if (p1.getGoals() > p2.getGoals()){
        return true;
    }
    else if (p1.getGoals() < p2.getGoals()){
        return false;
    }
    else{ // p1.getGoals() == p2.getGoals()
        if (p1.getCards() < p2.getCards()){
            return true;
        }
        else if (p1.getCards() > p2.getCards()){
            return false;
        }
        else{ //p1.getCards() == p2.getCards()
            if (p1.getPlayerId() > p2.getPlayerId()){
                return true;
            }
            else{
                return false;
            }
           
        }
    }
}
Player::Player(const Player& p){
    if( this != &p){
        this->playerId = p.playerId;
        this->teamId = p.teamId;
        this->gamesPlayed = p.gamesPlayed;
        this->goals = p.goals;
        this->cards = p.cards;
        this->goalKeeper = p.goalKeeper;
        this->teamGamesPlayedOnArrival = p.teamGamesPlayedOnArrival;
    }
}
Player& Player::operator=(const Player& p){
    if(this == &p){
        return *this;
    }
    this->playerId = p.playerId;
    this->teamId = p.teamId;
    this->gamesPlayed = p.gamesPlayed;
    this->goals = p.goals;
    this->cards = p.cards;
    this->goalKeeper = p.goalKeeper;
    this->teamGamesPlayedOnArrival = p.teamGamesPlayedOnArrival;
    return *this;
}

// int main() {
//     Player player1(1,1,1,1,1,true);
//     Player player2(2,2,2,2,2,false);
//     Player player3(3,3,3,3,3,true);
//     Player player4(4,4,4,4,4,false);
//     std::cout << "It works." << std::endl;
//     return 0;
// }