#pragma once
#include "BaseResourceManager.h"
#include <SFML/Graphics.hpp>

enum TextureID {
    Player = 0,
    Enemy,
    Background,
    Kill
};

const std::unordered_map<TextureID, std::string> TextureFileMap = {
    /*{Player, "player.png"},
    {Enemy, "enemy.png"},*/
   /* {Background, "background.png"}*/
     {Kill, "kill.png"}
};

class TextureManager : public BaseResourceManager<sf::Texture, TextureID> {
public:
    static TextureManager& instance();

private:
    TextureManager();
};