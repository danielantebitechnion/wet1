#include "AVL.h"
#include "Team.h"
#include "Player.h"

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
    this->teamPlayers = t.teamPlayers;
    this->isValidTeam = t.isValidTeam;
    this->teamGamesPlayed = t.teamGamesPlayed;
    this->team_top_scorer = t.team_top_scorer;
    return *this;
}
Team::Team(const Team& t) {
     if(this != &t){
        this->teamId = t.teamId;
        this->teamPointsCounter = t.teamPointsCounter;
        this->teamCardsCounter = t.teamCardsCounter;
        this->teamGoalsCounter = t.teamGoalsCounter;
        this->numOfPlayersCounter = t.numOfPlayersCounter;
        this->goalKeeperCounter = t.goalKeeperCounter;
        this->teamPlayers = t.teamPlayers;
        this->isValidTeam = t.isValidTeam;
        this->teamGamesPlayed = t.teamGamesPlayed;
        this->team_top_scorer = t.team_top_scorer;
    }
}


Team::Team(int teamId,int points)
    :
teamId(teamId),
teamPointsCounter(points),
teamCardsCounter(0),
teamGoalsCounter(0),
numOfPlayersCounter(0),
goalKeeperCounter(0),
teamPlayers(nullptr),
isValidTeam(false),
teamGamesPlayed(0),
team_top_scorer(0)
{}

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
bool Team::getValidity() const {
    return isValidTeam;
}
AVL<Player,Player>* Team::getTeamPlayers() {
    return &teamPlayers;
}
int Team::getTeamGamesPlayed () const {
    return teamGamesPlayed;
}
int Team::getTeamTopScorer() const{
    return team_top_scorer;
}

void Team::setTeamTopScorer(int id){
    team_top_scorer = id;
}
void Team::setTeamId(int new_teamId){
    teamId = new_teamId;
}
void Team::addCardsNum(int num){
    teamCardsCounter += num;
}
void Team::addGoalsNum(int num){
    teamGoalsCounter += num;
}
void Team::addPlayersNum(int num){
    numOfPlayersCounter += num;
}
void Team::addGoalKeepersNum(int num){
    goalKeeperCounter += num;
}
void Team::validitySetter(bool validity){
    isValidTeam = validity;
}
void Team::addToPoints (int howMuchToAdd) {
    teamPointsCounter += howMuchToAdd;
}
void Team::addToTeamGamesPlayed (int howMuchToAdd) {
    teamGamesPlayed += howMuchToAdd;
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
