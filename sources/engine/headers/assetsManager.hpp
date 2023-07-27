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
	AssetsManager(std::vector<TextureData> texturesData);
	Texture* getTexture(std::string name);
	void unloadTextures();
};