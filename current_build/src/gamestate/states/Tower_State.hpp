#ifndef TOWER_STATE
#define TOWER_STATE

#include "../Gamestate.hpp"
#include "../../entity/Tower_Player.hpp"
#include "../../tilemap/Tilemap.hpp"
#include "../../audio/Audiohandler.hpp"
#include "../../entity/Bullet.hpp"
#include "../../tilemap/UtilityMap.hpp"
#include "../../entity/Enemies/Enemy_Base.hpp"
#include "../../entity/Enemies/Flier_Enemy.hpp"


class Tower_State: public Gamestate{
private:
	Layer tower_layer;

	UtilityMap utility_map;
	Tilemap platform_map;

	Tower_Player player;

	std::vector<Bullet> bullets;
	std::vector<Enemy_Base*> enemies;

	std::vector<Point> spawn_locations;

	Flier_Enemy flier;
	Bullet b;

	sf::Sprite lizerd;

	sf::Sprite hotbar;

	int wave_timer=0;
	int wave_timer_max=10000;
	int difficulty_level=1;

	bool zoom=true;

public:
	void update(Mousey&,Keyblade&,Gamepad&)override;
	void render(sf::RenderWindow& window)override;
	void load_sprites(Imagehandler& imagehandler)override;
	void execute_data(Data_Packet)override;
	void check_keyboard(Keyblade&);
	void check_gamepad(Gamepad&);


	void update_layer_resolutions()override;

	Tower_State(Imagehandler& imagehandler,Audiohandler& audiohandler);
	~Tower_State(){}
};

#endif