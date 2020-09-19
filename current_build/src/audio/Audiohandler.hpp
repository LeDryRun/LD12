#ifndef AUDIOHANDLER_HPP
#define AUDIOHANDLER_HPP

#include "Audiokey.hpp"
#include <memory>
#include <vector>
#include "Sound_Texture.hpp"

class Audiohandler{
private:

	static std::shared_ptr<Audiokey> other_player[];
	static const int other_size;
	static float other_volume;
	static void request_other(std::shared_ptr<Audiokey>);

	static std::shared_ptr<Audiokey> sfx_player[];
	static const int sfx_size;
	static float sfx_volume;
	static void request_sfx(std::shared_ptr<Audiokey>);

	static std::shared_ptr<Audiokey> dialogue_player[];
	static const int dialogue_size;
	static float dialogue_volume;
	static void request_dialogue(std::shared_ptr<Audiokey>);
	
	static bool volume_update;

	float global_volume_scale=1.0f;
	float music_volume=100.0f;
	sf::Music background_music;

	std::string current_state;

	std::vector<std::shared_ptr<Audiokey>> paused_by_manager;

	std::vector<std::unique_ptr<Sound_Texture>> buffers;

	sf::SoundBuffer error_sound;

public:
	Audiohandler(){load();};
	void load();
	void load_audiokey(Audiokey&);
	void add_buffer(std::string,std::string);
	void set_background_music(std::string);
	void update();
	void change_gamestate(std::string);

	static void instantiate_player();
	static void add_sound_request(std::shared_ptr<Audiokey>);
	static void set_volume(float, sound_category::CATEGORY);
};

#endif