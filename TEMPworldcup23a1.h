#ifndef TEMP
#define TEMP

#include "AVL.h"
#include "Team.h"
#include "Player.h"
#include "AddressKeeper.h"
#include "wet1util.h"
#include <iostream>

const int VALID_PLAYERS_NUM = 11;
const int SCORE_AFTER_WINNING = 3;

class world_cup_t {
    public:

        world_cup_t ();

        virtual ~world_cup_t();

        StatusType add_team(int teamId, int points);

        StatusType remove_team(int teamId);

        StatusType add_player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper);

        StatusType remove_player(int playerId);

        StatusType update_player_stats(int playerId, int gamesPlayed, int scoredGoals, int cardsReceived);

        StatusType play_match(int teamId1, int teamId2);

        output_t<int> get_num_played_games(int playerId);
	
	    output_t<int> get_team_points(int teamId);
	
	    StatusType unite_teams(int teamId1, int teamId2, int newTeamId);
	
	    output_t<int> get_top_scorer(int teamId);
	
	    output_t<int> get_all_players_count(int teamId);
	
	    StatusType get_all_players(int teamId, int *const output);
	
	    output_t<int> get_closest_player(int playerId, int teamId);
	
	    output_t<int> knockout_winner(int minTeamId, int maxTeamId);


    private:
        AVL<int,Team> m_teams; // tree of all the teams and valid teams location
        AVL<Player,Player*> m_players_score; // players score tree
        AVL<int,AddressKeeper> m_players_id; // pointer to player id team
        AVL<int,int> m_valid_teams; // tree of all the valid teams with their points
        int m_top_scorer;
        int m_all_players_count;
};

#endif // TEMP
