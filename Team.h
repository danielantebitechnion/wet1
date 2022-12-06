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
  //Team(const Team& );
  //getters and setters
  int getTeamId() const;
  int getTeamPoints() const;
  int getTeamTotalCards() const;
  int getTeamTotalGoals() const;
  int getNumOfPlayers() const;
  int getNumOfGoalKeepers() const;
  void setTeamId(int new_teamId);
  void setPoints(int points);
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
 
};
bool operator==(const Team&, const Team&);
bool operator!=(const Team&, const Team&);
bool operator<(const Team&, const Team&);
bool operator>(const Team&, const Team&);

#endif /* TEAM_H */
