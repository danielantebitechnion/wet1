#ifndef PLAYER_H
#define PLAYER_H

const int NUM_OF_AVL_TREES = 4;

#include <iostream>

class Player{
    public:
    //C'tor
    Player(int playerId,int teamId,int gamesPlayed,int goals,int cards,bool goalKeeper);
    // D'tor
    ~Player();
    // Copy C'tor
    Player(const Player&);
    // getters
    int getPlayerId() const;
    int getTeamId() const;
    int getGamesPlayed() const;
    int getGoals() const;
    int getCards() const;
    bool getIsGoalKeeper() const;
    int getTotalPlayers() const;
    int getTeamGamesPlayedOnArrival () const;
    // setters
    void setPlayerId(int newPlayerId);
    void setTeamId(int newTeamId);
    void setGamesPlayed(int newGamesPlayed);
    void setGoals(int newGoals);
    void setCards(int newCards);
    void setIsGoalKeeper(bool isGoalKeeper);
    void setTeamGamesPlayedOnArrival (int numOfTeamGamesPlayedOnArrival);
    Player& operator=(const Player&);

    private:
    int playerId;
    int teamId;
    int gamesPlayed;
    int goals;
    int cards;
    bool goalKeeper;
    int teamGamesPlayedOnArrival;

};
bool operator!=(const Player&, const Player&);
bool operator==(const Player&, const Player&);
//bool operator>=(const Player&, const Player&);
//bool operator<=(const Player&, const Player&);
bool operator<(const Player&, const Player&);
bool operator>(const Player&, const Player&);

#endif /* PLAYER_H */
