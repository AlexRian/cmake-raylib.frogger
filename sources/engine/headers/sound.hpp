#pragma once
#include <map> 
#include <vector>
#include <string>
#include "raylib.h"

struct SoundData {
	std::string name, path;
};

class SoundManager {
private:
	std::map<std::string, Sound*> m_sounds;
public:
	SoundManager(std::vector<SoundData> soundsData);
	~SoundManager();

	void playSound(std::string name);
	void unloadSounds();
};