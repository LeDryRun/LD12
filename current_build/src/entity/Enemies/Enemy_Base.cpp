#include "Enemy_Base.hpp"


Enemy_Base::Enemy_Base()
{
    move_type = EMT_NONE;
    combat_type = ECT_NONE;

    max_HP = 1;
    HP = max_HP;

    dmg = 0;
    spd = 0;

    enemy_awake = false;
}

Enemy_Base::Enemy_Base(Point p)
{
    //printf("Hitbox exists @ %p", &hitbox);
    /*
    utility_layer = get_utility layer_from_tower_state
    move_type = EMT_NONE;
    combat_type = ECT_NONE;

    max_HP = 1;
    HP = max_HP;

    dmg = 0;
    spd = 0;

    enemy_awake = false;
    */
}

Enemy_Base::Enemy_Base(const Enemy_Base &original)
{
    move_type = original.move_type;
    combat_type = original.combat_type;

    max_HP = original.max_HP;
    HP = original.HP;

    dmg = original.dmg;
    spd = original.spd;

    enemy_awake = original.enemy_awake;
}