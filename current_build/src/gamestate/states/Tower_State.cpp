#include "Tower_State.hpp"


Tower_State::Tower_State(Imagehandler& imagehandler,Audiohandler& audiohandler):tower_layer("tower_layer"){
	load_sprites(imagehandler);
	state_name="tower_state";
}


void Tower_State::update_layer_resolutions(){
	Gamestate::update_layer_resolutions();
	tower_layer.resolve_new_resolution();
}



void Tower_State::load_sprites(Imagehandler& imagehandler){
	imagehandler.load_sprite(background,"core_game_background");
}


void Tower_State::update(Mousey& mouse, Keyblade& keyboard, Gamepad& gamepad){
	Duration_Check::start("-Tower update");
	Gamestate::update_gui_layer(mouse,keyboard,gamepad);
	
	mouse.set_layer(tower_layer);


	check_gamepad(gamepad);
	check_keyboard(keyboard);

	/*
		UPDATE TOP LAYER AND DESCEND, RENDER BOTTOM LAYER AND ASCEND

		ALWAYS SET MOUSE TO BACKGROUND LAYER LAST
	*/

	mouse.set_layer(background_layer);

	Duration_Check::stop("-Tower update");
}



void Tower_State::render(sf::RenderWindow& window){
	Duration_Check::start("-Tower render");
	Gamestate::render_background_layer(window);
	window.setView(tower_layer);

	Gamestate::render_gui_layer(window);
	Duration_Check::stop("-Tower render");
}
void Tower_State:: execute_data(Data_Packet data){
}

void Tower_State::check_keyboard(Keyblade& keyboard){
	if(keyboard.get_key('E').was_just_pressed()){
		send_data.push_back(Data_Packet("set_state",MANAGER,{"pause_menu"}));
	}
/*
	if(keyboard.get_key('w').is_pressed()){
		pac_man.set_input_dir(Cardinal::North);
	}else if(keyboard.get_key('s').is_pressed()){
		pac_man.set_input_dir(Cardinal::South);
	}else if(keyboard.get_key('a').is_pressed()){
		pac_man.set_input_dir(Cardinal::West);
	}else if(keyboard.get_key('d').is_pressed()){
		pac_man.set_input_dir(Cardinal::East);
	}*/
}

void Tower_State::check_gamepad(Gamepad& gamepad){
	if(gamepad.was_just_pressed(GAMEPAD_START)){
		send_data.push_back(Data_Packet("set_state",MANAGER,{"pause_menu"}));
	}
/*
	if(gamepad.was_just_pressed(GAMEPAD_A)){
	}
	if(gamepad.get_left_stick_y()>0){
		pac_man.set_input_dir(Cardinal::South);
	}else if(gamepad.get_left_stick_y()<0 ){
		pac_man.set_input_dir(Cardinal::North);
	}else if(gamepad.get_left_stick_x()<0 ){
		pac_man.set_input_dir(Cardinal::West);
	}else if(gamepad.get_left_stick_x()>0 ){
		pac_man.set_input_dir(Cardinal::East);
	}*/
}
