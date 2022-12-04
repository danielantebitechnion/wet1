#include "worldcup23a1.h"

world_cup_t::world_cup_t()
{
	// TODO: Your code goes here
}

world_cup_t::~world_cup_t()
{
	// TODO: Your code goes here
}


StatusType world_cup_t::add_team(int teamId, int points)
{
	if(teamId<=0 || points<0){
		return StatusType::INVALID_INPUT;
	}
	Team* t(teams_avl.findNode(teamId));
	if (t == NULL){
		t = new Team(teamId,points);
		Node<int,Team*> n(teamId,t);
		teams_avl.insertNode(&n);
	}
	return StatusType::FAILURE;
}

StatusType world_cup_t::remove_team(int teamId)
{
	// TODO: Your code goes here
	return StatusType::FAILURE;
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                        int scoredGoals, int cardsReceived)
{
	if(playerId <= 0 || gamesPlayed<0 || scoredGoals<0 || cardsReceived<0){
		return StatusType::INVALID_INPUT;
	}
	Player *p = all_players_by_id.findNode(playerId);
	if(p !=NULL){
		p->setCards(p->getCards()+cardsReceived);
		p->setGamesPlayed(p->getGamesPlayed()+gamesPlayed);
		p->setGoals(p->getGoals()+scoredGoals);
		return StatusType::SUCCESS;
	}
	return StatusType::FAILURE;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
	if (playerId <= 0){
		return StatusType::INVALID_INPUT;
	}
	Player *p = all_players_by_id.findNode(playerId);
	if(p !=NULL){
		return p->getGamesPlayed();
	}
	return StatusType::FAILURE;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	output_t<int> out;
	if (teamId <= 0){
		return StatusType::INVALID_INPUT;
	}
	Team *team = teams_avl.findNode(teamId);
	if(team !=NULL){
		return team->getTeamPoints();
	}
	return StatusType::FAILURE;
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
	// TODO: Your code goes here
	return 2008;
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
	if (teamId == 0){
		return StatusType::INVALID_INPUT;
	}
	if (teamId < 0){
	//Player root - getnumofplayers;
	}
	if (teamId > 0){
		Team *team = teams_avl.findNode(teamId);
		if(team !=NULL){
			return team->getNumOfPlayers();
		}
		return StatusType::FAILURE;
	}

}

StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
	// TODO: Your code goes here
    output[0] = 4001;
    output[1] = 4002;
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
	// TODO: Your code goes here
	return 1006;
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
	// TODO: Your code goes here
	return 2;
}

