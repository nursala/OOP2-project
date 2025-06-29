#include "ResourseInc/SoundManger.h"

SoundManger::SoundManger() {
    for (const auto& [id, path] : SoundFileMap)
    {
        load(id, path);
		m_sounds[id].setBuffer(*get(id));
    }
}

SoundManger& SoundManger::instance() {
    static SoundManger inst;
    return inst;
}

void SoundManger::play(Constants::SoundID id) {
    m_sounds.at(id).play();
}

void SoundManger::stop(Constants::SoundID id) {
	if (!isPlaying(id)) return; // Check if sound is playing before stopping
	m_sounds.at(id).stop();
}

void SoundManger::pause(Constants::SoundID id) {
    m_sounds.at(id).pause();
}

void SoundManger::setVolume(Constants::SoundID id, float volume) {
    m_sounds.at(id).setVolume(volume);
}

bool SoundManger::isPlaying(Constants::SoundID id) const {
    auto it = m_sounds.find(id);
    return it != m_sounds.end() && it->second.getStatus() == sf::Sound::Playing;
}