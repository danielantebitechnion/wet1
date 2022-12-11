#ifndef ADDRESS
#define ADDRESS

#include "Player.h"
#include "Team.h"
#include "AVL.h"

class AddressKeeper {
    public:
        AddressKeeper();
        // Team (all teams)
        Node<int,Team>* m_teams_address;
        // Valid Team
        Node<int,Team>* m_valid_teams_address;
};

#endif // ADDRESS