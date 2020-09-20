#include "Crawler_Enemy.hpp"

Crawler_Enemy::Crawler_Enemy()
{
    // Center position in relation to hitbox
    position.set_x(position.get_x() + hitbox.get_center_x());
    position.set_y(position.get_y() + hitbox.get_center_y());

    // Initialize members
    utilities = &UtilityMap();

    move_type = EMT_CLIMBER_CRAWLER;
    combat_type = ECT_STABBER;

    max_HP = 100;
    HP = max_HP;

    dmg = 2;
    spd = 25;

    enemy_awake = true;

    state = SPAWN;
    scan_range = 128;
    strike_range = 4;
}

Crawler_Enemy::Crawler_Enemy(const Crawler_Enemy &original)
{
    // Initialize members
    utilities = original.utilities;

    move_type = original.move_type;
    combat_type = original.combat_type;

    max_HP = original.max_HP;
    HP = original.HP;

    dmg = original.dmg;
    spd = original.spd;

    enemy_awake = original.enemy_awake;

    state = original.state;
    scan_range = original.scan_range;
    strike_range = original.strike_range;
}

Crawler_Enemy::Crawler_Enemy(UtilityMap &utilities_ref, Point leggy)
{
    // Center position in relation to hitbox
    position.set_x(position.get_x() + hitbox.get_center_x());
    position.set_y(position.get_y() + hitbox.get_center_y());

    // Initialize members
    utilities = &utilities_ref;

    move_type = EMT_CLIMBER_CRAWLER;
    combat_type = ECT_STABBER;

    max_HP = 100;
    HP = max_HP;

    dmg = 2;
    spd = 25;

    enemy_awake = true;

    state = SPAWN;
    scan_range = 128;
    strike_range = 4;

    target = leggy;
}

void Crawler_Enemy::update()
{
    if (!enemy_awake)
        return;

    // Always donw if awake
    // add time to cooldown timer, or reset

    // Specific AI actions
    switch (state)
    {
    case SPAWN:
        //target = Point(1216, 640); // Set target to leg x-position
        if (move_to_target())
        {
            state = CLIMB;
            break;
        }
        break;
    case CLIMB:
        spd = 35;
        if (move_to_target())
        {
            spd = 25;
            state = UTILITY_SEARCH;
            break;
        }
    case UTILITY_SEARCH:
        if (scan_for_player())
        {
            state = ATTACK_PLAYER;
            break;
        }
        else if (scan_for_utility())
        {
            // Set targeted utility
            state = ATTACK_UTILITY;
            break;
        }
        else
        {
            state = ATTACK_TOWER;
            break;
        }
        break;
    case ATTACK_UTILITY:
        /*
        if utility no longer exists, change to UTILITY_SEARCH
        else if, distance is > strike_range, move to utility
        if strike_cooldown available, strike at utility
        */
    case ATTACK_PLAYER:
        /*
        If distance to player is > scan_range, change to UTILITY_SEARCH
        if distance to player is > strike_range, move to player
        if strike cooldown is available, strike at player
        */
    case ATTACK_TOWER:
        /*
        if strike cooldown available, strike at tower
        */
    case DEAD:
        /*
        resource cleanup and create dead enemy object
        */

    default: return;
    }
}

bool Crawler_Enemy::scan_for_player()
{
    /*
    Get player position
    find distance between, then compare to range
    return true if in range
    else return false
    */
    return false;
}

bool Crawler_Enemy::scan_for_utility()
{
    /*
    search utility tilemap for nearest utility
    if in scan_range, set utility as target
    else return null
    */
    return false;
}

bool Crawler_Enemy::move_to_target()
{
    movement = target - position;
    float xx = abs(movement.get_x());
    float yy = abs(movement.get_y());
    
    if (xx > 0)
    {
        movement.set_y(0);
        if (xx < spd)
        {
            movement.set_x(copysign(spd, movement.get_x()));
        }
    }
    else if (yy > 0)
    {
        if (yy < spd)
        {
            movement.set_x(copysign(spd, movement.get_y()));
        }
    }
    else
    {
        return true; // reached target!
    }

    move();

    return false; // did no such thing
}

void Crawler_Enemy::kill()
{
    state = DEAD;
    Enemy_Base::kill();
}