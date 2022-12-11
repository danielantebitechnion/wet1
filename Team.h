#ifndef TEAM_H
#define TEAM_H

#include "Player.h"
#include "AVL.h"

class Team{
  public:
  //C'tor
  Team(int teamId,int points);
  //D'tor
  ~Team() = default;
  //Copy C'tor
  Team(const Team& ); // add
  //getters and setters
  int getTeamId() const;
  int getTeamPoints() const;
  int getTeamTotalCards() const;
  int getTeamTotalGoals() const;
  int getNumOfPlayers() const;
  int getNumOfGoalKeepers() const;
  bool getValidity() const;
  int getTeamGamesPlayed () const;
  int getTeamTopScorer() const;
  AVL<Player,Player>* getTeamPlayers();
  void setTeamId(int new_teamId);
  void addCardsNum(int num);
  void addGoalsNum(int num);
  void addPlayersNum(int num);
  void addGoalKeepersNum(int num);
  void validitySetter(bool validity);
  void addToPoints (int howMuchToAdd);
  void addToTeamGamesPlayed (int howMuchToAdd);
  void setTeamTopScorer(int id);
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
  AVL<Player,Player> teamPlayers;
  bool isValidTeam; // 11 players and at least 1 goalkeeper
  int teamGamesPlayed;
  int team_top_scorer;
 
};
bool operator==(const Team&, const Team&);
bool operator!=(const Team&, const Team&);
bool operator<(const Team&, const Team&);
bool operator>(const Team&, const Team&);

#endif /* TEAM_H */
