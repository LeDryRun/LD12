#ifndef FLIER_ENEMY
#define FLIER_ENEMY

#include "Enemy_Base.hpp"

class Flier_Enemy : public Enemy_Base 
{
    private:
        enum AI_STATES
        {
            NONE,

            SPAWN,
            UTILITY_SEARCH,
            ATTACK_UTILITY,
            ATTACK_PLAYER,
            ATTACK_TOWER,
            DEAD,

            NUM_STATES
        };

        //Utility target; // In prep for targeting utilities
        Point target;
        int scan_range;
        int leash_range;
        AI_STATES state;

        Point projectile_spawn = Point(hitbox.get_width(),0);
        float projectile_cooldown_duration = 1000;
        float projectile_cooldown = 0;
        //Projectile bullet_type; // In prep for making and shooting a bullet

        bool scan_for_player();
        bool scan_for_utility(); // want to have it return a reference to the utility
        bool move_to_target();
        void move_in_circle();
        void shoot_at(Point target);
    public:
        Flier_Enemy();
        Flier_Enemy(const Flier_Enemy &original);

        void update(); 
};

#endif // !FLIER_ENEMY