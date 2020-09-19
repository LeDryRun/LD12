#ifndef GAMESTATE_MANAGER_HPP
#define GAMESTATE_MANAGER_HPP


#include "Gamestate.hpp"
#include "states/Main_Menu_State.hpp"
#include "states/Options_Menu_State.hpp"
#include "states/Tower_State.hpp"
#include "states/Pause_Menu_State.hpp"
#include "../audio/Audiohandler.hpp"
#include "../input/Gamepad.hpp"


class Gamestate_Manager{
private:
	Gamestate* current_state;
	Main_Menu_State* main_menu_state;
	Tower_State* tower_state;
	Pause_Menu_State* pause_menu_state;
	Options_Menu_State* options_menu_state;

	Imagehandler imagehandler;
	Audiohandler audiohandler;

	Mousey mouse;
	Keyblade keyboard;
	Gamepad gamepad;

	std::vector<Data_Packet> send_data;

	bool set_state(Data_Packet);

	void receive_data(Data_Packet);

public:

	void render(sf::RenderWindow&);
	void update(sf::RenderWindow&);

	Gamestate_Manager();
	~Gamestate_Manager(){
		delete main_menu_state;
		delete tower_state;
		delete pause_menu_state;
		delete options_menu_state;
	}

	Data_Packet get_send_data(){
		if(send_data.size()>0){
			Data_Packet tmp=send_data.at(0);
			send_data.erase(send_data.begin());
			return tmp;
		}else{
			return Data_Packet();
		}
	}
	bool has_send_data(){
		return(send_data.size()>0);
	}	

	void resolution_error(bool exists_p){
		options_menu_state->resolution_error(exists_p);
	}

	void update_layer_resolutions();


};

#endif