#ifndef ENEMY_BASE
#define ENEMY_BASE

#include "../Tilemap_Entity.hpp"
#include "../Entity.hpp"


enum ENEMY_MOVEMENT_TYPE {
    EMT_NONE,

    EMT_CLIMBER,
    EMT_CLIMBER_CRAWLER,
    EMT_FLIER,

    EMT_NUM_STATES
};

enum ENEMY_COMBAT_TYPE {
    ECT_NONE,

    ECT_SHOOTER,
    ECT_RAMMER,

    ECT_NUM_STATES
};

class Enemy_Base : public Entity
{
    protected:
        //Tilemap &utility_layer; // In preparation for Andrew's work

        ENEMY_MOVEMENT_TYPE move_type;
        ENEMY_COMBAT_TYPE combat_type;
        int max_HP;
        int HP;
        int dmg;
        int spd;

        bool enemy_awake;
       
    public:
        Enemy_Base();
        Enemy_Base(Point p);
        Enemy_Base(const Enemy_Base &original);

        ENEMY_MOVEMENT_TYPE get_movement_type() { return move_type; };
        void set_movement_type(ENEMY_MOVEMENT_TYPE type) { move_type = type; };
        ENEMY_COMBAT_TYPE get_combat_type() { return combat_type; };
        void set_combat_type(ENEMY_COMBAT_TYPE type) { combat_type = type; };
        int get_max_HP() { return max_HP; };
        void set_max_HP(int new_max_HP) { max_HP = abs(new_max_HP); }; // NEgative max HP has no meaning
        int get_HP() { return HP; };
        void set_HP(int new_HP) { HP = new_HP; }; // Does not validate if HP falls within [0, max_HP]
        int get_dmg() { return dmg; };
        void set_dmg(int new_dmg) { HP = new_dmg; };
        int get_spd() { return spd; };
        void set_spd(int new_spd) { HP = new_spd; };
        bool is_awake() { return enemy_awake; };
        void set_awake(bool is_awake) { enemy_awake = is_awake; };
        void toggle_awake() { enemy_awake != enemy_awake; };

        virtual void update() {};
        virtual void kill() {};
};

#endif // !ENEMY_BASE