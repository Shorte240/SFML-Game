// Audio Manager
// Maintains lists of Sound and Music for playback in game
#pragma once

#include "Sound.h"
#include "MusicObject.h"
#include "SFML\Audio.hpp"

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	void addSound(std::string filename, std::string lname);
	void playSoundbyName(std::string lname);
	void setSoundVolumebyName(std::string lname, float vol);
	void stopAllSounds();

	void addMusic(std::string filename, std::string lname);
	void playMusicbyName(std::string lname);
	void setMusicVolumebyName(std::string lname, float vol);
	void pauseAllMusic();
	void stopAllMusic();
	bool isMusicPaused() { return isPaused; };

private:
	// List of sounds
	std::vector<Sound> sounds;
	// List of Musics
	std::vector<MusicObject> musics;
	// Single Music object as the stream cannot be copied.
	sf::Music music;
	// Re-useable sound object
	Sound s;
	// Bool isPaused to check against if music is paused.
	bool isPaused = false;
};

