#pragma once
#include "ResourseInc/BaseResourceManager.h"
#include <SFML/Audio.hpp>
#include <unordered_map>
#include "Constants.h"

const std::unordered_map<Constants::SoundID, std::string> SoundFileMap = {
    {Constants::SoundID::BackgroundMusic, "background_music.ogg"}
};

class SoundManager : public BaseResourceManager<sf::SoundBuffer, Constants::SoundID> {
public:
    static SoundManager& instance();

    void play(Constants::SoundID id);
    void pause(Constants::SoundID id);
    void setVolume(Constants::SoundID id, float volume);
    bool isPlaying(Constants::SoundID id) const;

private:
    SoundManager();
    std::unordered_map<Constants::SoundID, sf::Sound> m_sounds;
};
