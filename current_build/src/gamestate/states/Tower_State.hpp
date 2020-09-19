#ifndef TOWER_STATE
#define TOWER_STATE

#include "../Gamestate.hpp"
#include "../../entity/Entity.hpp"
#include "../../tilemap/Tilemap.hpp"
#include "../../audio/Audiohandler.hpp"


class Tower_State: public Gamestate{
private:
	Layer tower_layer;

	Tilemap utility_map;
	Tilemap platform_map;

	Entity player;
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