#include "worldcup23a1.h"

world_cup_t::world_cup_t():all_players_top_scorer(nullptr),all_players_by_id(nullptr),teams_avl(nullptr),valid_teams(nullptr)
{}

world_cup_t::~world_cup_t()
{
    all_players_top_scorer.deleteAVL();
    all_players_by_id.deleteAVL();
    teams_avl.deleteAVL();
    valid_teams.deleteAVL();
}


StatusType world_cup_t::add_team(int teamId, int points)
{
	if(teamId<=0 || points<0){
		return StatusType::INVALID_INPUT;
	}
	Node<int,Team>* t = teams_avl.findNode(teamId);
	if (t == nullptr){
		Team* new_team = new Team(teamId,points);
		t->m_data.setTeamId(teamId);
		t->m_data.setPoints(points);
		t->m_key = teamId;
		teams_avl.insertNode(t);
	}
	return StatusType::FAILURE;
}

StatusType world_cup_t::remove_team(int teamId)
{
    if(teamId<=0){
        return StatusType::INVALID_INPUT;
    }
    Node<int,Team>* t = teams_avl.findNode(teamId);
	if (t == nullptr || t->m_data.getNumOfPlayers() != 0){
	    return StatusType::FAILURE;
	}
	teams_avl.deleteNode(t);
	return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
    if(playerId<=0 || teamId<=0 || gamesPlayed<0 || goals<0 || cards<0){
        return StatusType::INVALID_INPUT;
    }
    if(gamesPlayed == 0 && (goals>0 || cards>0)){
        return StatusType::INVALID_INPUT;
    }
    Node<int,Player>* p = all_players_by_id.findNode(playerId);
    if (p != nullptr){
        return StatusType::FAILURE;
    }
    Node<int,Team>* t = teams_avl.findNode(teamId);
    if (t == nullptr){
        return StatusType::FAILURE;
    }
    Player* pl = new Player(playerId,teamId,gamesPlayed,goals,cards,goalKeeper);
    Node<Player,Player> np(pl,pl);
    all_players_by_id.insertNode(p);
    all_players_top_scorer.insertNode(np);
    // add player to teams_avl and if needed update valid_tems tree
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
	Node<int,Player>* p = all_players_by_id.findNode(playerId);
	if(p !=nullptr){
		p->m_data.setCards(p->m_data.getCards()+cardsReceived);
		p->m_data.setGamesPlayed(p->m_data.getGamesPlayed()+gamesPlayed);
		p->m_data.setGoals(p->m_data.getGoals()+scoredGoals);
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
	Node<int,Player> *p = all_players_by_id.findNode(playerId);
	if(p !=nullptr){
		return p->m_data.getGamesPlayed();
	}
	return StatusType::FAILURE;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	output_t<int> out;
	if (teamId <= 0){
		return StatusType::INVALID_INPUT;
	}
	Node<int,Team>* team = teams_avl.findNode(teamId);
	if(team !=nullptr){
		return team->m_data.getTeamPoints();
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
	    Node<Player,Player>* p = all_players_top_scorer.getRoot();
	    return p->m_data.getTotalPlayers();
	}
	//if (teamId > 0){
	Node<int,Team>* n = teams_avl.findNode(teamId);
	if(n !=nullptr){
		return n->m_data.getNumOfPlayers();
	}
	return StatusType::FAILURE;
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

