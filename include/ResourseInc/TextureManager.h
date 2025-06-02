#pragma once
#include "ResourseInc/BaseResourceManager.h"
#include <SFML/Graphics.hpp>

enum TextureID {
	Kill = 0,
	Player,
};

const std::unordered_map<TextureID, std::string> TextureFileMap = {
	{Player, "heavy_player_face.png"},
	/*{Enemy, "enemy.png"},* /
	/* {Background, "background.png"}*/
	  { Kill, "kill.png" }}; 

class TextureManager : public BaseResourceManager<sf::Texture, TextureID> {
public:
	static TextureManager& instance();

private:
	TextureManager();
};