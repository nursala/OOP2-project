#include "ResourseInc/SoundManger.h"

// Constructor: load and assign buffers to sound objects
SoundManger::SoundManger() {
    for (const auto& [id, path] : SoundFileMap) {
        load(id, path);
        m_sounds[id].setBuffer(*get(id));
    }
}

// Singleton access method
SoundManger& SoundManger::instance() {
    static SoundManger inst;
    return inst;
}

// Play a sound by ID (if not muted)
void SoundManger::play(Constants::SoundID id) {
    if (!m_muted)
        m_sounds.at(id).play();
}

// Stop a sound if it's currently playing
void SoundManger::stop(Constants::SoundID id) {
    if (isPlaying(id))
        m_sounds.at(id).stop();
}

// Mute all sounds by pausing them
void SoundManger::mute() {
    m_muted = true;
    for (auto& [id, sound] : m_sounds) {
        if (sound.getStatus() == sf::Sound::Playing)
            sound.pause();
    }
}

// Unmute all paused sounds and resume playing
void SoundManger::unmute() {
    m_muted = false;
    for (auto& [id, sound] : m_sounds) {
        if (sound.getStatus() == sf::Sound::Paused)
            sound.play();
    }
}

// Loop a specific sound on/off
void SoundManger::loop(Constants::SoundID id, bool loop) {
    m_sounds.at(id).setLoop(loop);
}

// Pause a specific sound
void SoundManger::pause(Constants::SoundID id) {
    m_sounds.at(id).pause();
}

// Set volume for a specific sound
void SoundManger::setVolume(Constants::SoundID id, float volume) {
    m_sounds.at(id).setVolume(volume);
}

// Check if a specific sound is currently playing
bool SoundManger::isPlaying(Constants::SoundID id) const {
    auto it = m_sounds.find(id);
    return it != m_sounds.end() && it->second.getStatus() == sf::Sound::Playing;
}

// Get the current playing time offset of a sound
sf::Time SoundManger::getPlayingOffset(Constants::SoundID id) {
    auto it = m_sounds.find(id);
    return (it != m_sounds.end()) ? it->second.getPlayingOffset() : sf::Time();
}

// Get direct access to an sf::Sound object
sf::Sound& SoundManger::getSound(Constants::SoundID id) {
    return m_sounds.at(id);
}
