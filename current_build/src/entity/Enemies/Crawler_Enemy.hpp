#ifndef CRAWLER_ENEMY
#define CRAWLER_ENEMY

#include "Enemy_Base.hpp"

class Crawler_Enemy : public Enemy_Base
{
    private:
        enum AI_STATES
        {
            NONE,

            SPAWN,
            CLIMB,
            UTILITY_SEARCH,
            ATTACK_UTILITY,
            ATTACK_PLAYER,
            ATTACK_TOWER,
            SPOOKED,
            DEAD,

            NUM_STATES
        };

        //Utility target; // In prep for targeting utilities
        Point target;
        int scan_range;
        int strike_range;
        AI_STATES state;

        float strike_cooldown_duration = 100;
        float strike_cooldown = 0;

        bool scan_for_player();
        bool scan_for_utility(); // want to have it return a reference to the utility
        bool move_to_target();

    public:
        Crawler_Enemy();
        Crawler_Enemy(const Crawler_Enemy &original);
        Crawler_Enemy(UtilityMap &utilities_ref, Point leggy);

        void update();
        void kill();
};

#endif // !CRAWLER_ENEMY
