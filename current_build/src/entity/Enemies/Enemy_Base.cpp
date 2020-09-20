#include "Enemy_Base.hpp"


Enemy_Base::Enemy_Base()
{
    utilities = &UtilityMap();

    move_type = EMT_NONE;
    combat_type = ECT_NONE;

    max_HP = 1;
    HP = max_HP;

    dmg = 0;
    spd = 0;

    enemy_awake = false;
}

Enemy_Base::Enemy_Base(UtilityMap &utilities_ref)
{
    utilities = &utilities_ref;

    move_type = EMT_NONE;
    combat_type = ECT_NONE;

    max_HP = 1;
    HP = max_HP;

    dmg = 0;
    spd = 0;

    enemy_awake = false;
}

Enemy_Base::Enemy_Base(const Enemy_Base &original)
{
    utilities = original.utilities;

    move_type = original.move_type;
    combat_type = original.combat_type;

    max_HP = original.max_HP;
    HP = original.HP;

    dmg = original.dmg;
    spd = original.spd;

    enemy_awake = original.enemy_awake;
}

void Enemy_Base::kill()
{
    // Do dead body object and resource cleanup
}