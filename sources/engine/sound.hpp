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
	SoundManager(std::vector<SoundData> soundsData) {
		InitAudioDevice();
		for (auto path : soundsData) {
			Sound* sound = new Sound();
			*sound = LoadSound(path.path.c_str());
			m_sounds.insert(
				{ path.name, sound }
			);
		}
	}

	~SoundManager() {
		unloadSounds();
		CloseAudioDevice();
	}

	void playSound(std::string name) {
		PlaySound(*m_sounds[name]);
	}

	void unloadSounds() {
		for (auto sound : m_sounds) {
			UnloadSound(*sound.second);
			delete sound.second;
		}
	}
};