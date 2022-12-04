

#include "Team.h"
/*
  //D'tor
  ~Team();
  //Copy C'tor
  Team(const& Team);
  //Assignment operator
  Team& operator=(const Team&);
  //print
 
  private:
  int teamId;
  int teamPointsCounter;
  int teamCardsCounter;
  int teamGoalsCounter;
  int numOfPlayersCounter;
  int goalKeeperCounter;
  //AVL<Player> teamPlayers;
  bool isValidTeam; // 11 players and at least 1 goalkeeper
 
*/
Team& Team::operator=(const Team& t){
    if( this == &t){
        return *this;
    }
    this->teamId = t.teamId;
    this->teamPointsCounter = t.teamPointsCounter;
    this->teamCardsCounter = t.teamCardsCounter;
    this->teamGoalsCounter = t.teamGoalsCounter;
    this->numOfPlayersCounter = t.numOfPlayersCounter;
    this->goalKeeperCounter = t.goalKeeperCounter;
    this->isValidTeam = t.isValidTeam;
    //this->teamPlayers = t.teamPlayers;
    return *this;
}
Team::Team(const Team& t){
     if(this != &t){
        this->teamId = t.teamId;
        this->teamPointsCounter = t.teamPointsCounter;
        this->teamCardsCounter = t.teamCardsCounter;
        this->teamGoalsCounter = t.teamGoalsCounter;
        this->numOfPlayersCounter = t.numOfPlayersCounter;
        this->goalKeeperCounter = t.goalKeeperCounter;
        this->isValidTeam = t.isValidTeam;
        //this->teamPlayers = t.teamPlayers;
    }
}


Team::Team(int teamId,int points):
teamId(teamId),
teamPointsCounter(points)
{
    teamGoalsCounter=0;
    teamCardsCounter=0;
    goalKeeperCounter=0;
    isValidTeam = false;
}

//getters and setters
int Team::getTeamId() const{
    return teamId;
}
int Team::getTeamPoints() const{
    return teamPointsCounter;
}
int Team::getTeamTotalCards() const{
    return teamCardsCounter;
}
int Team::getTeamTotalGoals() const{
    return teamGoalsCounter;
}
int Team::getNumOfPlayers() const{
    return numOfPlayersCounter;
}
int Team::getNumOfGoalKeepers() const{
    return goalKeeperCounter;
}
void Team::setTeamId(int new_teamId){
    teamId = new_teamId;
}


// operators
bool operator!=(const Team& t1, const Team& t2){
    return !(t1 == t2);
}
bool operator==(const Team& t1, const Team& t2){
    return t1.getTeamId() == t2.getTeamId();
}

bool operator<(const Team& t1, const Team& t2){
    return t1.getTeamId() < t2.getTeamId();
}

bool operator>(const Team& t1, const Team& t2){
    return t2<t1;
}
