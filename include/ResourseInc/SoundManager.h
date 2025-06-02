#pragma once
#include "ResourseInc/BaseResourceManager.h"
#include <SFML/Audio.hpp>
#include <unordered_map>

enum class SoundID {
   /* Explosion,
    Shoot,*/
    BackgroundMusic,
};

const std::unordered_map<SoundID, std::string> SoundFileMap = {
    {SoundID::BackgroundMusic, "background_music.ogg"}
};

class SoundManager : public BaseResourceManager<sf::SoundBuffer, SoundID> {
public:
    static SoundManager& instance();

    void play(SoundID id);
    void pause(SoundID id);
    void setVolume(SoundID id, float volume);
    bool isPlaying(SoundID id) const;

private:
    SoundManager();
    std::unordered_map<SoundID, sf::Sound> m_sounds;
};
