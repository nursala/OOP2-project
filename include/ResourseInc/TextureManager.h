#pragma once
#include "ResourseInc/BaseResourceManager.h"
#include <SFML/Graphics.hpp>
// TextureManager.h
enum class TextureID {
	Kill = 0,
	Player,
	Enemy,
	Gift,
};

const std::unordered_map<TextureID, std::string> TextureFileMap = {
	{TextureID::Player, "heavy_player_face.png"},
	{TextureID::Enemy, "heavy_player_face.png"},
	{TextureID::Gift , "extra_life_gift.png"},
	/* {Background, "background.png"}*/
	  { TextureID::Kill, "kill.png" }}; 

class TextureManager : public BaseResourceManager<sf::Texture, TextureID> {
public:
	static TextureManager& instance();

private:
	TextureManager();
};