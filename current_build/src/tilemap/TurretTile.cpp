#include "TurretTile.hpp"
#include <math.h>
#include <iostream>


TurretTile::TurretTile() : bullet("Effects_Attack")
{
	m_turret_texture = sf::Texture();
	m_turret = sf::Sprite();

	m_turret_texture.loadFromFile("../assets/image/animations/Util_Attack.png", sf::IntRect(0, 0, 128, 128));
	m_turret.setTexture(m_turret_texture);

	m_turret.setScale(0.5f, 0.5f);

	m_turret.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y);

	m_turret.setOrigin(m_turret_texture.getSize().x / 2, m_turret_texture.getSize().y / 2);

	tile_type = kTurret;

	m_target = nullptr;


}

TurretTile::~TurretTile()
{

}

void TurretTile::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
	target.draw(m_turret, states);
	//target.draw(bullet.get_current_frame());
}

void TurretTile::update(std::vector<Enemy_Base*> enemies)
{
	m_is_firing = false;
	Point p = Point(100000, 100000);
	Point pos = Point(m_turret.getPosition().x, m_turret.getPosition().y);
	int p_rss = sqrt(pow(p.get_x() - pos.get_x(),2) + pow(p.get_y() - pos.get_y(),2));

	for (int i = 0; i < enemies.size(); i++)
	{
		Point p_enemy = enemies.at(i)->get_center();
		int new_rss = sqrt(pow(p_enemy.get_x() - pos.get_x(),2) + pow(p_enemy.get_y() - pos.get_y(),2));

		if (new_rss < p_rss)
		{
			if (m_target == nullptr)
			{
				p = p_enemy;
				m_target = enemies.at(i);
			}
			else if (m_target->get_HP() <= 0)
			{
				p = p_enemy;
				m_target = enemies.at(i);
			}
		}
	}
	if (m_target != nullptr) {
		Point target_pos = m_target->get_position();
		float bulletv_x = target_pos.get_x() - pos.get_x();
		float bulletv_y = target_pos.get_y() - pos.get_y();
		float target_rss = sqrt(pow(bulletv_x,2) + pow(bulletv_y,2));
		m_bulletv_x = bulletv_x / target_rss;
		m_bulletv_y = bulletv_y / target_rss;

		if (m_bullet_cooldown_timer <= 0) {
			m_is_firing = true;
			m_bullet_cooldown_timer = m_bullet_cooldown_timer_max;
		}
	}
	if (m_bullet_cooldown_timer <= 0)
		m_bullet_cooldown_timer = m_bullet_cooldown_timer_max;
	m_bullet_cooldown_timer--;

}

bool TurretTile::is_firing_bullet()
{
	return m_is_firing;
}

Point TurretTile::get_bullet_position()
{
	return Point(m_turret.getPosition().x - 12 / 2, m_turret.getPosition().y - 12 - 12/2);
}

float TurretTile::get_bulletv_x()
{
	return m_bulletv_x;
}

float TurretTile::get_bulletv_y()
{
	return m_bulletv_y;
}

UtilityTileType TurretTile::get_tile_type()
{
	return tile_type;
}

void TurretTile::set_position(int x, int y)
{
	m_sprite.setPosition(x, y);
	m_turret.setPosition(x + m_sprite.getTextureRect().width/2, y + m_sprite.getTextureRect().height/2);
	m_map_x = x;
	m_map_y = y;
}
