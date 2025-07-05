#include "ResourseInc/SoundManager.h"

// Constructor: load and assign buffers to sound objects
SoundManager::SoundManager() {
    for (const auto& [id, path] : SoundFileMap) {
        load(id, path);
        m_sounds[id].setBuffer(*get(id));
    }
}

// Singleton access method
SoundManager& SoundManager::instance() {
    static SoundManager inst;
    return inst;
}

// Play a sound by ID (if not muted)
void SoundManager::play(Constants::SoundID id) {
	if (!m_muted || m_paused)
		m_sounds.at(id).play();
}

// Stop a sound if it's currently playing
void SoundManager::stop(Constants::SoundID id) {
    if (isPlaying(id))
        m_sounds.at(id).stop();
}

void SoundManager::unmute(bool mute, bool pause)
{
	m_muted = mute ? false : true;
	m_paused = pause ? false : true;
	for (auto& [id, sound] : m_sounds)
	{
		if (sound.getStatus() == sf::Sound::Paused)
		{
			sound.play();
		}
	}
}

void SoundManager::mute(bool mute, bool pause)
{
	m_muted = mute ? true : false;
	m_paused = pause ? true : false;
	for (auto& [id, sound] : m_sounds)
	{
		if (sound.getStatus() == sf::Sound::Playing)
		{
			sound.pause();
		}
	}
}

// Loop a specific sound on/off
void SoundManager::loop(Constants::SoundID id, bool loop) {
    m_sounds.at(id).setLoop(loop);
}

// Pause a specific sound
void SoundManager::pause(Constants::SoundID id) {
    m_sounds.at(id).pause();
}

// Set volume for a specific sound
void SoundManager::setVolume(Constants::SoundID id, float volume) {
    m_sounds.at(id).setVolume(volume);
}

// Check if a specific sound is currently playing
bool SoundManager::isPlaying(Constants::SoundID id) const {
    auto it = m_sounds.find(id);
    return it != m_sounds.end() && it->second.getStatus() == sf::Sound::Playing;
}

// Get the current playing time offset of a sound
sf::Time SoundManager::getPlayingOffset(Constants::SoundID id) {
    auto it = m_sounds.find(id);
    return (it != m_sounds.end()) ? it->second.getPlayingOffset() : sf::Time();
}

// Get direct access to an sf::Sound object
sf::Sound& SoundManager::getSound(Constants::SoundID id) {
    return m_sounds.at(id);
}
