#ifndef NOISEMAKER_HPP
#define NOISEMAKER_HPP

class Audiohandler;
#include "Audiokey.hpp"
#include <string>
#include <vector>
#include <memory>

class Noise_Maker{
protected:
	std::vector<std::shared_ptr<Audiokey>> sounds;
	std::string state_of_origin="error";
public:
	Noise_Maker(){}
	virtual void load_sounds(Audiohandler&);
	virtual void play_sound(std::string);
	virtual void pause_sound(std::string);
	virtual void stop_sound(std::string);
	virtual void add_sound(std::string, sound_category::CATEGORY);
	virtual void loop_sound(std::string,bool);

	Audiokey get_key(std::string);
	bool is_sound_playing(std::string);
	int get_sound_int(std::string);
	void set_state_of_origin(std::string soo_p){state_of_origin=soo_p;}

};

#endif