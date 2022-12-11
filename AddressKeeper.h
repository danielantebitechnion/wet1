#ifndef ADDRESS
#define ADDRESS

#include "Player.h"
#include "Team.h"
#include "AVL.h"

class AddressKeeper {
    public:
        AddressKeeper();
        
        // Player ID
        Node<int,Player>* m_players_id_address;
        AVL<int,Player>* m_players_id_avl;
        // Player by goals
        Node<Player,Player>* m_players_score_address;
        AVL<Player,Player>* m_players_score_avl;
        // Team (all teams)
        Node<int,Team>* m_teams_address;
        AVL<int,Team>* m_teams_avl;
        // Valid Team
        Node<int,Team>* m_valid_teams_address;
        AVL<int,Team>* m_valid_teams_avl;
};

#endif // ADDRESS