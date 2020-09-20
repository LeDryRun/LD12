#include "Flier_Enemy.hpp"

Flier_Enemy::Flier_Enemy()
{
    // Center position in relation to hitbox
    position.set_x(position.get_x() + hitbox.get_center_x());
    position.set_y(position.get_y() + hitbox.get_center_y());

    // Initialize members
    move_type = EMT_FLIER;
    combat_type = ECT_SHOOTER;

    max_HP = 100;
    HP = max_HP;

    dmg = 5;
    spd = 10;

    enemy_awake = true;

    state = SPAWN;
    scan_range = 128;
    leash_range = 64;
}

Flier_Enemy::Flier_Enemy(const Flier_Enemy &original)
{
    // Initialize members
    move_type = original.move_type;
    combat_type = original.combat_type;

    max_HP = original.max_HP;
    HP = original.HP;

    dmg = original.dmg;
    spd = original.spd;

    enemy_awake = original.enemy_awake;

    state = original.state;
    scan_range = original.scan_range;
    leash_range = original.leash_range;
}

void Flier_Enemy::update() 
{
    if (!enemy_awake)
        return;

    // Always donw if awake
    // add time to cooldown timer, or reset

    // Specific AI actions
    switch (state) 
    {
        case SPAWN:
            target = Point(640, 360);
            if (scan_for_player())
            {
                state = ATTACK_PLAYER;
                break;
            }
            if (scan_for_utility())
            {
                // Set targeted utility
                state = ATTACK_UTILITY;
                break;
            }
            if (move_to_target())
            {
                state = UTILITY_SEARCH;
                break;
            }
            break;
        case UTILITY_SEARCH:
            if (scan_for_player())
            {
                state = ATTACK_PLAYER;
                break;
            }
            if (scan_for_utility())
            {
                // Set targeted utility
                state = ATTACK_UTILITY;
                break;
            }
            move_in_circle();
            break;
        case ATTACK_UTILITY:
            /*
            if utility no longer exists, change to UTILITY_SEARCH
            else if, distance is > leash_range, move to utility
            if shoot_cooldown available, shoot at utility
            */
        case ATTACK_PLAYER:
            /*
            if distance to player is > scan_range, change to UTILITY_SEARCH
            if distance to player is > leash_range, move to player
            if shoot cooldown is available, shoot at player
            */
        case ATTACK_TOWER:
            /*
            if shoot cooldown available, shoot at tower
            */
        case DEAD:
            /*
            resource cleanup and create dead enemy object
            */
            
        default: return;
    }
}

bool Flier_Enemy::scan_for_player()
{
    /*
    Get player position
    find distance between, then compare to range
    return true if in range
    else return false
    */
    return false;
}

bool Flier_Enemy::scan_for_utility()
{
    /*
    search utility tilemap for nearest utility
    if in scan_range, set utility as target
    else return null
    */
    return false;
}

bool Flier_Enemy::move_to_target()
{
    movement = target - position;
    float mag = sqrt(movement.get_x()*movement.get_x() + movement.get_y()*movement.get_y());

    if (mag < 1)
    {
        return true; // reached target!
    }

    movement.set_x(movement.get_x() * spd / mag);
    movement.set_y(movement.get_y() * spd / mag);
    move();

    return false;
}

void Flier_Enemy::move_in_circle() 
{

}

void Flier_Enemy::shoot_at(Point target)
{
    // Should have acces to Projectile
    /*
    Point target_vector = target - position;
    float target_mag = sqrt(target_vector.x*target_vector.x + target_vector.y*target_vector.y);
    target_vector.x /= target_mag;
    target_vector.y /= target_mag;
    projectile_spawn = position + Point(target_vector.x*hitbox.get_width, target_vector.y*hitbox.get_height());

    tmp = CreateProjectile(projectile_spawn, target_vector);

    tmp.dmg = dmg;
    */
}