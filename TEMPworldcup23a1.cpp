#include "TEMPworldcup23a1.h"
#include "wet1util.h"
#include "Team.cpp" // do not delete
#include "Player.cpp" // do not delete
#include "AddressKeeper.cpp" // do not delete
#include <iostream>
using std::cout;
using std::endl;

world_cup_t::world_cup_t()
    :
    m_teams(nullptr),
    m_players_id(nullptr),
    m_players_score(nullptr),
    m_valid_teams(nullptr),
    m_addresses(nullptr),
    m_top_scorer(0),
    m_num_of_players(0)
    {}

world_cup_t::~world_cup_t() {
    m_teams.deleteAVL();
    m_players_id.deleteAVL();
    m_players_score.deleteAVL();
    m_valid_teams.deleteAVL();
    m_addresses.deleteAVL();
}

StatusType world_cup_t::add_team(int teamId, int points) {
    if (teamId<=0 || points<0) { // invalid parameters
        return StatusType::INVALID_INPUT;
    }
    if (m_teams.findNode(teamId) != nullptr) { // already exists
        return StatusType::FAILURE;
    }
    try {
        Team* team = new Team(teamId, points);
        Node<int, Team>* node = new Node<int, Team>(teamId,*team);
        m_teams.insertNode(node);
    } catch(std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId) {
    if (teamId<=0) {
        return StatusType::INVALID_INPUT;
    }
    if (m_teams.findNode(teamId) == nullptr ||
    m_teams.findNode(teamId)->m_data.getNumOfPlayers() > 0) {
    // does not exist or is not empty
        return StatusType::FAILURE;
    }
    m_teams.deleteNode(teamId);
    if (m_teams.findNode(teamId) != nullptr) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper) {
    if (playerId<=0 || teamId<=0 || gamesPlayed<0 || goals<0 || cards<0
    || (gamesPlayed=0 && (goals>0 || cards>0))) {
        return StatusType::INVALID_INPUT;
    }
    if (m_players_id.findNode(playerId) != nullptr || m_teams.findNode(teamId) == nullptr) {
        return StatusType::FAILURE;
    }
    try {
        m_num_of_players++;
        bool validityAtBeginning = m_teams.findNode(teamId)->m_data.getValidity();
        int PlaysOnArrival = m_teams.findNode(teamId)->m_data.getTeamGamesPlayed();
        Player* player0 = new Player(playerId, teamId, gamesPlayed, goals, cards, goalKeeper);
        Player* player1 = new Player(playerId, teamId, gamesPlayed, goals, cards, goalKeeper);
        Player* player2 = new Player(playerId, teamId, gamesPlayed, goals, cards, goalKeeper);
        player0->setTeamGamesPlayedOnArrival(PlaysOnArrival);
        player1->setTeamGamesPlayedOnArrival(PlaysOnArrival);
        player2->setTeamGamesPlayedOnArrival(PlaysOnArrival);
        Node<int, Player>* IDNode = new Node<int, Player>(playerId,*player0);
        Node<Player, Player>* playerPlayerNode1 = new Node<Player, Player>(*player1, *player1);
        Node<Player, Player>* playerPlayerNode2 = new Node<Player, Player>(*player2, *player2);
        // add players to trees
        m_players_id.insertNode(IDNode);
        m_players_score.insertNode(playerPlayerNode1);
        m_teams.findNode(teamId)->m_data.getTeamPlayers()->insertNode(playerPlayerNode2);
        // create AddressesKeeper and assignement
        AddressKeeper* addresses = new AddressKeeper;
        // player by id tree
        addresses->m_players_id_avl = &m_players_id;
        addresses->m_players_id_address = IDNode;
        // player by score tree
        addresses->m_players_score_avl = &m_players_score;
        addresses->m_players_score_address = playerPlayerNode1;
        // teams tree
        addresses->m_teams_avl = &m_teams;
        addresses->m_teams_address = m_teams.findNode(teamId);
        // update teams stats
        m_teams.findNode(teamId)->m_data.addCardsNum(cards);
        m_teams.findNode(teamId)->m_data.addGoalsNum(goals);
        m_teams.findNode(teamId)->m_data.addPlayersNum(1);
        if (goalKeeper == true) {
            m_teams.findNode(teamId)->m_data.addGoalKeepersNum(1);
        }
        if (m_teams.findNode(teamId)->m_data.getNumOfPlayers() >= VALID_PLAYERS_NUM
        && m_teams.findNode(teamId)->m_data.getNumOfGoalKeepers() >= 1) {
            m_teams.findNode(teamId)->m_data.validitySetter(true);
        }
        // check team validity
        bool validityAfterAddition = m_teams.findNode(teamId)->m_data.getValidity();
        // if team was valid before
        if (validityAtBeginning == true && validityAfterAddition == true) {
            int topScorerID = m_teams.findNode(teamId)->m_data.getTeamTopScorer();
            Player* player3 = new Player(playerId, teamId, gamesPlayed, goals, cards, goalKeeper);
            player3->setTeamGamesPlayedOnArrival(PlaysOnArrival);
            Node<Player, Player>* playerPlayerNode3 = new Node<Player, Player>(*player3, *player3);
            m_valid_teams.findNode(teamId)->m_data.getTeamPlayers()->insertNode(playerPlayerNode3);
            addresses->m_valid_teams_avl = &m_valid_teams;
            addresses->m_valid_teams_address = m_valid_teams.findNode(teamId);;
            m_valid_teams.findNode(teamId)->m_data.addCardsNum(cards);
            m_valid_teams.findNode(teamId)->m_data.addGoalsNum(goals);
            m_valid_teams.findNode(teamId)->m_data.addPlayersNum(1);
            if (goalKeeper == true) {
                m_valid_teams.findNode(teamId)->m_data.addGoalKeepersNum(1);
            }
            m_valid_teams.findNode(teamId)->m_data.setTeamTopScorer(topScorerID);
            // team change from invalid to valid
        } else if (validityAtBeginning == false && validityAfterAddition == true) {
            Node<int, Team>* intTeamNode = new Node<int, Team>(teamId, m_teams.findNode(teamId)->m_data);
            m_valid_teams.insertNode(intTeamNode);
            addresses->m_valid_teams_avl = &m_valid_teams;
            addresses->m_valid_teams_address = m_valid_teams.findNode(teamId);
        }
        Node<int, AddressKeeper>* addressesNode = new Node<int, AddressKeeper>(playerId, *addresses);
        m_addresses.insertNode(addressesNode);
        // update turnament top scorer
        m_top_scorer = m_players_score.findNode(*player0)->m_data.getPlayerId();
        // update Team top scorer
        m_teams.findNode(teamId)->m_data.setTeamTopScorer(m_teams.findNode(teamId)->m_data.getTeamPlayers()->biggestNode()->m_data.getPlayerId());
    } catch(std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId) {
    if (playerId<=0) {
        return StatusType::INVALID_INPUT;
    }
    if (m_players_id.findNode(playerId) == nullptr) {
        return StatusType::FAILURE;
    }
    try {
        m_num_of_players--;
        Player player = m_players_id.findNode(playerId)->m_data;
        int teamId = m_addresses.findNode(playerId)->m_data.m_players_id_address->m_data.getTeamId();
        int cards = m_addresses.findNode(playerId)->m_data.m_players_id_address->m_data.getCards();
        int goals = m_addresses.findNode(playerId)->m_data.m_players_id_address->m_data.getGoals();
        bool goalKeeper = m_addresses.findNode(playerId)->m_data.m_players_id_address->m_data.getIsGoalKeeper();
        bool validityAtBeginning = m_addresses.findNode(playerId)->m_data.m_teams_address->m_data.getValidity();
        // delete from player by id tree
        m_players_id.deleteNode(playerId);
        // delete from player by score tree
        m_players_score.deleteNode(player);
        // delete from teams tree
        m_addresses.findNode(playerId)->m_data.m_teams_address->m_data.getTeamPlayers()->deleteNode(player);
        // update teams stats
        m_addresses.findNode(playerId)->m_data.m_teams_address->m_data.addCardsNum(-cards);
        m_addresses.findNode(playerId)->m_data.m_teams_address->m_data.addGoalsNum(-goals);
        m_addresses.findNode(playerId)->m_data.m_teams_address->m_data.addPlayersNum(-1);
        if (goalKeeper == true) {
            m_addresses.findNode(playerId)->m_data.m_teams_address->m_data.addGoalKeepersNum(-1);
        }
        // check if team is still valid
        if (m_addresses.findNode(playerId)->m_data.m_teams_address->m_data.getNumOfPlayers() < VALID_PLAYERS_NUM
        && m_addresses.findNode(playerId)->m_data.m_teams_address->m_data.getNumOfGoalKeepers() < 1) {
            m_teams.findNode(teamId)->m_data.validitySetter(false);
        }
        bool validityAfterDeletion = m_addresses.findNode(playerId)->m_data.m_teams_address->m_data.getValidity();
        if (validityAtBeginning == true && validityAfterDeletion == true) {
            // delete from valid teams tree
            m_addresses.findNode(playerId)->m_data.m_valid_teams_address->m_data.getTeamPlayers()->deleteNode(player);
            // update valid teams stats
            m_addresses.findNode(playerId)->m_data.m_valid_teams_address->m_data.addCardsNum(-cards);
            m_addresses.findNode(playerId)->m_data.m_valid_teams_address->m_data.addGoalsNum(-goals);
            m_addresses.findNode(playerId)->m_data.m_valid_teams_address->m_data.addPlayersNum(-1);
            if (goalKeeper == true) {
                m_addresses.findNode(playerId)->m_data.m_valid_teams_address->m_data.addGoalKeepersNum(-1);
            }
        } else if (validityAtBeginning == true && validityAfterDeletion == false) {
            m_addresses.findNode(playerId)->m_data.m_valid_teams_address->m_data.getTeamPlayers()->deleteAVL();
            m_addresses.findNode(playerId)->m_data.m_valid_teams_avl->deleteNode(teamId);
        }
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    // update turnament top scorer
    if(m_num_of_players != 0){
        m_top_scorer = m_players_score.biggestNode()->m_data.getPlayerId();
    }
    else{
        m_top_scorer = 0;
    }
    // update team top scorer
    if(m_addresses.findNode(playerId)->m_data.m_teams_address->m_data.getNumOfPlayers() != 0){
        m_addresses.findNode(playerId)->m_data.m_teams_address->m_data.setTeamTopScorer(m_addresses.findNode(playerId)->m_data.m_teams_address->m_data.getTeamPlayers()->biggestNode()->m_data.getPlayerId());
    }
    else{
        m_addresses.findNode(playerId)->m_data.m_teams_address->m_data.setTeamTopScorer(0);
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed, int scoredGoals, int cardsReceived) { // have to finish
    if (playerId<=0 || gamesPlayed<0 || scoredGoals<0 || cardsReceived<0) {
        return StatusType::INVALID_INPUT;
    }
    if (m_addresses.findNode(playerId) == nullptr) {
        StatusType::FAILURE;
    }
    try {
        // create player with updated stats
        Player p = m_players_id.findNode(playerId)->m_data;
        p.setGamesPlayed(p.getGamesPlayed()+gamesPlayed);
        p.setCards(p.getCards()+cardsReceived);
        p.setGoals(p.getGoals()+scoredGoals);
        // update players id tree
        // delete old player and insert updated player
        m_players_id.deleteNode(playerId);
        Node<int,Player>* p_node = new Node<int,Player>(playerId,p);
        m_players_id.insertNode(p_node);
        // update players score tree
        // delete old player and insert updated player
        m_players_score.deleteNode(p);
        Node<Player,Player>* p_node_score = new Node<Player,Player>(p,p);
        m_players_score.insertNode(p_node_score);
        // update teams tree
        m_addresses.findNode(playerId)->m_data.m_teams_address->m_data.getTeamPlayers()->deleteNode(p);
        m_addresses.findNode(playerId)->m_data.m_teams_address->m_data.getTeamPlayers()->insertNode(p_node_score);
        // update valid teams tree (if needed)
        // check if team is valid
        if(m_addresses.findNode(playerId)->m_data.m_teams_address->m_data.getValidity()){
            m_addresses.findNode(playerId)->m_data.m_valid_teams_address->m_data.getTeamPlayers()->deleteNode(p);
            m_addresses.findNode(playerId)->m_data.m_valid_teams_address->m_data.getTeamPlayers()->insertNode(p_node_score);
        }
        // update general top scorer update
        m_top_scorer = m_players_score.biggestNode()->m_data.getPlayerId();
        // update team top scorer
        m_addresses.findNode(playerId)->m_data.m_teams_address->m_data.getTeamPlayers()->biggestNode()->m_data.getPlayerId();
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2) {
    if (teamId1<=0 || teamId2<=0 || teamId2 == teamId1) {
        return StatusType::INVALID_INPUT;
    }
    if (m_valid_teams.findNode(teamId1) == nullptr || m_valid_teams.findNode(teamId2) == nullptr) {
        return StatusType::FAILURE;
    }
    try {
        // update games played for both teams
        // valid teams tree
        m_valid_teams.findNode(teamId1)->m_data.addToTeamGamesPlayed(1);
        m_valid_teams.findNode(teamId2)->m_data.addToTeamGamesPlayed(1);
        // teams tree
        m_teams.findNode(teamId1)->m_data.addToTeamGamesPlayed(1);
        m_teams.findNode(teamId2)->m_data.addToTeamGamesPlayed(1);
        // check which team won
        int resTeam1 = m_valid_teams.findNode(teamId1)->m_data.getTeamPoints() + m_valid_teams.findNode(teamId1)->m_data.getTeamTotalGoals() - m_valid_teams.findNode(teamId1)->m_data.getTeamTotalCards();
        int resTeam2 = m_valid_teams.findNode(teamId2)->m_data.getTeamPoints() + m_valid_teams.findNode(teamId2)->m_data.getTeamTotalGoals() - m_valid_teams.findNode(teamId2)->m_data.getTeamTotalCards();
        if (resTeam1 > resTeam2) {
            m_teams.findNode(teamId1)->m_data.addToPoints(SCORE_AFTER_WINNING);
            m_valid_teams.findNode(teamId1)->m_data.addToPoints(SCORE_AFTER_WINNING);
        } else if (resTeam1 < resTeam2) {
            m_teams.findNode(teamId2)->m_data.addToPoints(SCORE_AFTER_WINNING);
            m_valid_teams.findNode(teamId2)->m_data.addToPoints(SCORE_AFTER_WINNING);
        } else { // if (resTeam1 == resTeam2)
            m_teams.findNode(teamId1)->m_data.addToPoints(1);
            m_teams.findNode(teamId2)->m_data.addToPoints(1);
            m_valid_teams.findNode(teamId1)->m_data.addToPoints(1);
            m_valid_teams.findNode(teamId2)->m_data.addToPoints(1);
        }
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
    if(playerId<= 0){
        return StatusType::INVALID_INPUT;
    }
    if(m_players_id.findNode(playerId) == nullptr){
        return StatusType::FAILURE;
    }
    int games_of_team = m_addresses.findNode(playerId)->m_data.m_teams_address->m_data.getTeamGamesPlayed();
    int games_of_player_without_team = m_players_id.findNode(playerId)->m_data.getGamesPlayed();
    int game_of_team_before_joining = m_players_id.findNode(playerId)->m_data.getTeamGamesPlayedOnArrival();
    return games_of_player_without_team+games_of_team-game_of_team_before_joining;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    if(teamId<=0){
        return StatusType::INVALID_INPUT;
    }
    if(m_teams.findNode(teamId) == nullptr){
        return StatusType::FAILURE;
    }
    return m_teams.findNode(teamId)->m_data.getTeamPoints();
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
    if(newTeamId <=0 || teamId1<=0 || teamId2<= 0 || teamId1==teamId2){
        return StatusType::INVALID_INPUT;
    }
    if(m_teams.findNode(teamId1) == nullptr || m_teams.findNode(teamId2) == nullptr){
        return StatusType::FAILURE;
    }
    if(newTeamId != teamId1 && newTeamId != teamId2){
        if(m_teams.findNode(newTeamId) != nullptr){
            return StatusType::FAILURE;
        }
    }
    

}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
    if(teamId == 0){
        return StatusType::INVALID_INPUT;
    }
    if(teamId < 0 ){
        if (m_top_scorer == 0){// no players in turnament
            return StatusType::FAILURE;
        }
        else{
            return m_top_scorer;
        }
    }
    if (m_teams.findNode(teamId) == nullptr){
        return StatusType::FAILURE;
    }
    if(m_teams.findNode(teamId)->m_data.getNumOfPlayers() == 0){
        return StatusType::FAILURE;
    }
    return m_teams.findNode(teamId)->m_data.getTeamTopScorer();
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
    if(teamId == 0){
        return StatusType::INVALID_INPUT;
    }
    if(teamId < 0 ){
        return m_num_of_players;
    }
    if (m_teams.findNode(teamId) == nullptr){
        return StatusType::FAILURE;
    }
    return m_teams.findNode(teamId)->m_data.getNumOfPlayers();
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

int main()
{
    // add team root
    cout << "add team root:" << endl;
    world_cup_t world;
    if (world.add_team(1234, 100) == StatusType::SUCCESS) {
        cout << "The addition of (1234) succeeded in the Team trees" << endl;
        cout << "The root's key of Team is: (" <<
        world.getWorldTeamsAVL().getRoot()->m_key << ")" << endl;
        cout << "teamPointsCounter = " << world.getWorldTeamsAVL().getRoot()->m_data.getTeamPoints() << endl;
        cout << "teamCardsCounter = " << world.getWorldTeamsAVL().getRoot()->m_data.getTeamTotalCards() << endl;
        cout << "teamGoalsCounter = " << world.getWorldTeamsAVL().getRoot()->m_data.getTeamTotalGoals() << endl;
        cout << "numOfPlayersCounter = " << world.getWorldTeamsAVL().getRoot()->m_data.getNumOfPlayers() << endl;
        cout << "goalKeeperCounter = " << world.getWorldTeamsAVL().getRoot()->m_data.getNumOfGoalKeepers() << endl;
        cout << "isValidTeam = " << world.getWorldTeamsAVL().getRoot()->m_data.getValidity() << endl;
        cout << "teamGamesPlayed = " << world.getWorldTeamsAVL().getRoot()->m_data.getTeamGamesPlayed() << endl;
        cout << "team_top_scorer = " << world.getWorldTeamsAVL().getRoot()->m_data.getTeamTopScorer() << endl;
    }
    cout << endl;

    // add team left son
    cout << "add team left son:" << endl;
    if (world.add_team(1111, 100) == StatusType::SUCCESS) {
        cout << "The addition of (1111) succeeded in the Team trees" << endl;
    }
    cout << "The left node's key of Team is: (";
    if (world.getWorldTeamsAVL().getRoot()->m_left == nullptr) {
        cout << "nullptr";
    } else {
        cout << world.getWorldTeamsAVL().getRoot()->m_left->m_key;
    }
    cout << ")" << endl;
    cout << endl;

    // delete team left son
    cout << "delete team left son:" << endl;
    if (world.remove_team(1111) == StatusType::SUCCESS) {
        cout << "The deletion of (1111) succeeded in the Team trees" << endl;
    }
    cout << "Now the left node's key of Team is: (";
    if (world.getWorldTeamsAVL().getRoot()->m_left == nullptr) {
        cout << "nullptr";
    } else {
        cout << world.getWorldTeamsAVL().getRoot()->m_left->m_key;
    }
    cout << ")" << endl;
    cout << endl;

    // add player root
    cout << "add player root:" << endl;
    if (world.add_player(10,1234,30,40,50,true) == StatusType::SUCCESS) {
        cout << "The addition of (10) succeeded in the Player trees" << endl;
        cout << "The root's key of ID tree is: (" <<
        world.getWorldPlayersId().getRoot()->m_key <<
        "), and the root's key of Score tree is: (";
        if (world.getWorldPlayersScore().getRoot() == nullptr) {
            cout << "nullpte";
        } else {
            cout << world.getWorldPlayersScore().getRoot()->m_key.getPlayerId();
        }
        cout << ")" << endl;
        cout << "teamPointsCounter = " << world.getWorldTeamsAVL().getRoot()->m_data.getTeamPoints() << endl;
        cout << "teamCardsCounter = " << world.getWorldTeamsAVL().getRoot()->m_data.getTeamTotalCards() << endl;
        cout << "teamGoalsCounter = " << world.getWorldTeamsAVL().getRoot()->m_data.getTeamTotalGoals() << endl;
        cout << "numOfPlayersCounter = " << world.getWorldTeamsAVL().getRoot()->m_data.getNumOfPlayers() << endl;
        cout << "goalKeeperCounter = " << world.getWorldTeamsAVL().getRoot()->m_data.getNumOfGoalKeepers() << endl;
        cout << "isValidTeam = " << world.getWorldTeamsAVL().getRoot()->m_data.getValidity() << endl;
    }
    cout << endl;

    // add player left son
    cout << "add player left son:" << endl;
    if (world.add_player(1,1234,3,4,5,true) == StatusType::SUCCESS) {
        cout << "The addition of (1) succeeded in the Player trees" << endl;
        cout << "The left node's key of Player is: (";
        if (world.getWorldPlayersId().getRoot()->m_left == nullptr) {
            cout << "nullptr";
        } else {
            cout << world.getWorldPlayersId().getRoot()->m_left->m_key <<
            "), and the root's key of Score tree is: (";
            if (world.getWorldPlayersScore().getRoot() == nullptr) {
                cout << "nullptr";
            } else {
                cout << world.getWorldPlayersScore().getRoot()->m_left->m_key.getPlayerId();
            }
        }
        cout << ")" << endl;
        cout << "teamPointsCounter = " << world.getWorldTeamsAVL().getRoot()->m_data.getTeamPoints() << endl;
        cout << "teamCardsCounter = " << world.getWorldTeamsAVL().getRoot()->m_data.getTeamTotalCards() << endl;
        cout << "teamGoalsCounter = " << world.getWorldTeamsAVL().getRoot()->m_data.getTeamTotalGoals() << endl;
        cout << "numOfPlayersCounter = " << world.getWorldTeamsAVL().getRoot()->m_data.getNumOfPlayers() << endl;
        cout << "goalKeeperCounter = " << world.getWorldTeamsAVL().getRoot()->m_data.getNumOfGoalKeepers() << endl;
        cout << "isValidTeam = " << world.getWorldTeamsAVL().getRoot()->m_data.getValidity() << endl;
    }
    cout << endl;

    // addresses verification
    cout << "addresses verification:" << endl;
    cout << "The addresses' root is: (";
    if (world.getAddresses().getRoot() == nullptr) {
        cout << "nullptr";
    } else {
        cout << world.getAddresses().getRoot()->m_key;
    }
    cout << ")" << endl;
    cout << endl;

    // remove left son
    cout << "remove left son:" << endl;
    if (world.remove_player(1) == StatusType::SUCCESS) {
        cout << "The removal of (1) succeeded in the Player trees" << endl;
        cout << "The left node's key of Player is: (";
        if (world.getWorldPlayersId().getRoot()->m_left == nullptr) {
            cout << "nullptr), and the root's key of Score tree is: (";
            if (world.getWorldPlayersScore().getRoot()->m_left == nullptr) {
                cout << "nullptr";
            } else {
                cout << world.getWorldPlayersScore().getRoot()->m_left->m_key.getPlayerId();
            }
        } else {
            cout << world.getWorldPlayersId().getRoot()->m_left->m_key <<
            "), and the root's key of Score tree is: (";
            if (world.getWorldPlayersScore().getRoot() == nullptr) {
                cout << "nullptr";
            } else {
                cout << world.getWorldPlayersScore().getRoot()->m_left->m_key.getPlayerId();
            }
        }
        cout << ")" << endl;
        cout << "teamPointsCounter = " << world.getWorldTeamsAVL().getRoot()->m_data.getTeamPoints() << endl;
        cout << "teamCardsCounter = " << world.getWorldTeamsAVL().getRoot()->m_data.getTeamTotalCards() << endl;
        cout << "teamGoalsCounter = " << world.getWorldTeamsAVL().getRoot()->m_data.getTeamTotalGoals() << endl;
        cout << "numOfPlayersCounter = " << world.getWorldTeamsAVL().getRoot()->m_data.getNumOfPlayers() << endl;
        cout << "goalKeeperCounter = " << world.getWorldTeamsAVL().getRoot()->m_data.getNumOfGoalKeepers() << endl;
        cout << "isValidTeam = " << world.getWorldTeamsAVL().getRoot()->m_data.getValidity() << endl;
    }
    cout << endl;

    // update stats
    cout << "update stats:" << endl;
    cout << "current stats of (10) are:" << endl;
    int currGamesPlayed = world.getAddresses().findNode(10)->m_data.m_players_id_address->m_data.getGamesPlayed();
    cout << "GamesPlayed: " << currGamesPlayed << endl;
    int currGoals = world.getAddresses().findNode(10)->m_data.m_players_id_address->m_data.getGoals();
    cout << "Goals: " << currGoals << endl;
    int currCards = world.getAddresses().findNode(10)->m_data.m_players_id_address->m_data.getCards();
    cout << "Cards: " << currCards << endl;
    if (world.update_player_stats(10, 1,1,1) == StatusType::SUCCESS) {
        cout << "The updating succeeded! Now the stats are:" << endl;
        int newGamesPlayed = world.getAddresses().findNode(10)->m_data.m_players_id_address->m_data.getGamesPlayed();
        cout << "GamesPlayed: " << newGamesPlayed << endl;
        int newGoals = world.getAddresses().findNode(10)->m_data.m_players_id_address->m_data.getGoals();
        cout << "Goals: " << newGoals << endl;
        int newCards = world.getAddresses().findNode(10)->m_data.m_players_id_address->m_data.getCards();
        cout << "Cards: " << newCards << endl;
    }
    cout << endl;

    // // play match


    return 0;
}
