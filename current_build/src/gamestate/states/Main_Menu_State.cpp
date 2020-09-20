#include "Main_Menu_State.hpp"

using namespace std;

Main_Menu_State::Main_Menu_State(Imagehandler& imagehandler){
	gui_layer_buttons.push_back(std::make_unique<Text_Button>(Text_Button("tower", 608, 400, Data_Packet("set_state",MANAGER,{"tower_state"}),-1,-1,1,-1)));
	gui_layer_buttons.push_back(std::make_unique<Text_Button>(Text_Button("options", 608, 450, Data_Packet("set_state",MANAGER,{"options_menu"}),-1,0,2,-1)));
	gui_layer_buttons.push_back(std::make_unique<Text_Button>(Text_Button("close", 608, 500, Data_Packet("close",WINDOW),-1,1,-1,-1)));
	load_sprites(imagehandler);
	state_name="main_menu";
	//gui_layer.setCenter(300,400);
}

void Main_Menu_State::load_sprites(Imagehandler& imagehandler){
	for(unsigned int i=0;i<gui_layer_buttons.size();i++){
		imagehandler.load_button(gui_layer_buttons[i].get());
	}
	imagehandler.load_sprite(background,"main_menu_background");

	imagehandler.load_sf_text(title);
	title.setCharacterSize(70);
	title.setFillColor(sf::Color::Red);
	title.setOutlineColor(sf::Color::Black);
	title.setOutlineThickness(3.0f);
	title.setString("Main Menu");
	title.setPosition(683-(int)(title.getLocalBounds().width/2),50);
}


void Main_Menu_State::update(Mousey& mouse,Keyblade& keyboard, Gamepad& gamepad){
	Duration_Check::start("-MM update");
	Gamestate::update(mouse,keyboard,gamepad);
	Duration_Check::stop("-MM update");
}

void Main_Menu_State::render(sf::RenderWindow& window){
	Duration_Check::start("-MM render");
	Gamestate::render(window);
	Duration_Check::stop("-MM render");
}

void Main_Menu_State:: execute_data(Data_Packet data){

}
