#pragma once
#include <map> 
#include <vector>
#include <string>
#include "raylib.h"

struct TextureData {
	std::string name, path;
};

class AssetsManager {
private:
	std::map<std::string, Texture*> m_textures;

public:
	AssetsManager(std::vector<TextureData> texturesData) {
		for (auto path : texturesData) {
			Texture* texture = new Texture();
			*texture = LoadTexture(path.path.c_str());
			m_textures.insert(
				{ path.name, texture }
			);
		}
	}

	Texture* getTexture(std::string name) {
		return m_textures[name];
	}

	void unloadTextures() {
		for (auto texture : m_textures) {
			UnloadTexture(*texture.second);
			delete texture.second;
		}
	}
};