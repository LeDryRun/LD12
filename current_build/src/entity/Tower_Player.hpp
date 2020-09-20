#ifndef TOWER_PLAYER_HPP
#define TOWER_PLAYER_HPP

#include "Tilemap_Entity.hpp";
#include "../audio/Noise_Maker.hpp"
class Mousey;
class Keyblade;

class Tower_Player: public Tilemap_Entity, public Noise_Maker{
private:
	float gravity_acceleration=-0.8f;
	int speed=8;

	float falling_speed=0.0f;

	int jump_impulse=10;
	float jump_acceleration=0.2f;

	bool grounded=false;
	bool jumping=false;
	bool anim_wait=false;

	bool wall_slide=false;

	bool facing_left=false;

	bool firing_bullet=false;
	float bullet_vector_x;
	float bullet_vector_y;
	int bullet_cooldown_timer=0;
	int bullet_cooldown_timer_max=20;
	Point bullet_position;

	int e_timer=0;
	int e_max=10;

	int build_timer=0;
	int build_timer_max=30;

	bool placing_valid;
	Animation valid;
	Animation invalid;
	Animation reticule;
	Animation bullet;

	std::string mode="shooting";

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	Tower_Player();

	void update(Tilemap&, Mousey&, Keyblade&);
	void load_animations(Imagehandler&) override;

	bool is_firing_bullet(){return firing_bullet;}
	float get_bulletv_x(){return bullet_vector_x;}
	float get_bulletv_y(){return bullet_vector_y;}
	Point get_bullet_position(){return bullet_position;}
};


#endif