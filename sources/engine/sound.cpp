#include "raylib.h"
#include "headers/sound.hpp"

SoundManager::SoundManager(std::vector<SoundData> soundsData) {
	InitAudioDevice();
	for (auto path : soundsData) {
		Sound* sound = new Sound();
		*sound = LoadSound(path.path.c_str());
		m_sounds.insert(
			{ path.name, sound }
		);
	}
}

SoundManager::~SoundManager() {
	unloadSounds();
	CloseAudioDevice();
}

void SoundManager::playSound(std::string name) {
	PlaySound(*m_sounds[name]);
}

void SoundManager::unloadSounds() {
	for (auto sound : m_sounds) {
		UnloadSound(*sound.second);
		delete sound.second;
	}
}