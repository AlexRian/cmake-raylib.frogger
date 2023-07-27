#include "headers/assetsManager.hpp"

AssetsManager::AssetsManager(std::vector<TextureData> texturesData) {
	for (auto path : texturesData) {
		Texture* texture = new Texture();
		*texture = LoadTexture(path.path.c_str());
		m_textures.insert(
			{ path.name, texture }
		);
	}
}

Texture* AssetsManager::getTexture(std::string name) {
	return m_textures[name];
}

void AssetsManager::unloadTextures() {
	for (auto texture : m_textures) {
		UnloadTexture(*texture.second);
		delete texture.second;
	}
}