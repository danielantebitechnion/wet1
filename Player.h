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
    // setters
    void setPlayerId(int newPlayerId);
    void setTeamId(int newTeamId);
    void setGamesPlayed(int newGamesPlayed);
    void setGoals(int newGoals);
    void setCards(int newCards);
    void setIsGoalKeeper(bool isGoalKeeper);
    Player& operator=(const Player&);
    private:
    int playerId;
    int teamId;
    int gamesPlayed;
    int goals;
    int cards;
    bool goalKeeper;
    static int playersCounter;

};
bool operator!=(const Player&, const Player&);
bool operator==(const Player&, const Player&);
//bool operator>=(const Player&, const Player&);
//bool operator<=(const Player&, const Player&);
bool operator<(const Player&, const Player&);
bool operator>(const Player&, const Player&);

