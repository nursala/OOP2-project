#include "ResourseInc/SoundManager.h"

SoundManager::SoundManager() {
    for (const auto& [id, path] : SoundFileMap)
    {
        load(id, path);
		m_sounds[id].setBuffer(*get(id));
    }
}

SoundManager& SoundManager::instance() {
    static SoundManager inst;
    return inst;
}

void SoundManager::play(Constants::SoundID id) {
    m_sounds.at(id).play();
}

void SoundManager::pause(Constants::SoundID id) {
    m_sounds.at(id).pause();
}

void SoundManager::setVolume(Constants::SoundID id, float volume) {
    m_sounds.at(id).setVolume(volume);
}

bool SoundManager::isPlaying(Constants::SoundID id) const {
    auto it = m_sounds.find(id);
    return it != m_sounds.end() && it->second.getStatus() == sf::Sound::Playing;
}