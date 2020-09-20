#ifndef DEAD_ENEMY
#define DEAD_ENEMY

#include "../Entity.hpp"

// Please delete this object once out of bounds

class Dead_Enemy : public Entity
{
    int grav = 5;

    public:
        Dead_Enemy() {};
        Dead_Enemy(string anim_name, Point spawn)
        {
            add_animation(anim_name);
            // don't forget to load image with imageHandler
            create(spawn);
        };
        ~Dead_Enemy();

        void update()
        {
            movement += Point(0, grav);
        };
}

#endif // !DEAD_ENEMY
