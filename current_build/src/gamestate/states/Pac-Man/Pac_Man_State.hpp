#ifndef Pac_Man_State_HPP
#define Pac_Man_State_HPP

#include "../../Gamestate.hpp"
#include "../../../entity/Pac-Man/Ghost.hpp"
#include "../../../entity/Point.hpp"
#include "../../../entity/Pac-Man/Pac_man.hpp"
#include "../../../tilemap/Tilemap.hpp"
#include "../../../audio/Audiohandler.hpp"



class Pac_Man_State :public Gamestate{
private:
	Layer core_layer;

	std::vector<Ghost> ghosts;
	Point ghost_spawn;
	Point pac_spawn;
	Point warp_1;
	Point warp_2;

	Pac_man pac_man;
	Tilemap tilemap;

	Entity mat;
	bool sound=false;
public:
	void update(Mousey&,Keyblade&,Gamepad&)override;
	void render(sf::RenderWindow& window)override;
	void load_sprites(Imagehandler& imagehandler)override;
	void execute_data(Data_Packet)override;
	void check_keyboard(Keyblade&);
	void check_gamepad(Gamepad&);

	void update_layer_resolutions()override;

	Pac_Man_State(Imagehandler& imagehandler,Audiohandler& audiohandler);
	~Pac_Man_State(){}

};

#endif