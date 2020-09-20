#ifndef TURRETTILE_HPP
#define TURRETTILE_HPP

#include "UtilityTile.hpp"
#include "../image/Animation.hpp"

class TurretTile : public UtilityTile
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Texture m_turret_texture;
	sf::Sprite m_turret;

	int m_bullet_cooldown_timer = 0;
	int m_bullet_cooldown_timer_max = 20;

	bool m_is_firing;
	float m_bulletv_x;
	float m_bulletv_y;

	Enemy_Base *m_target;

	Animation bullet;

public:
	TurretTile();
	UtilityTileType get_tile_type();
	void set_position(int x, int y);
	~TurretTile();
	void update(std::vector<Enemy_Base*> enemies);

	bool is_firing_bullet();
	Point get_bullet_position();
	float get_bulletv_x();
	float get_bulletv_y();

};

#endif //TURRETTILE_HPP