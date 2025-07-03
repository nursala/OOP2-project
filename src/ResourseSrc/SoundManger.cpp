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
	if (!m_muted || m_paused)
		m_sounds.at(id).play();
}

void SoundManger::stop(Constants::SoundID id) {
	if (!isPlaying(id)) return; // Check if sound is playing before stopping
		m_sounds.at(id).stop();
}

void SoundManger::unmute(bool mute, bool pause)
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

sf::Time SoundManger::getPlayingOffset(Constants::SoundID id)
{
	auto it = m_sounds.find(id);
	if (it != m_sounds.end()) {
		return it->second.getPlayingOffset(); // ? ??? ?? ??????? ??????
	}
	return sf::Time(); // ?? ??? ?? ??? ????? ?????
}

void SoundManger::mute(bool mute, bool pause)
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

void SoundManger::loop(Constants::SoundID id, bool loop) {
	m_sounds.at(id).setLoop(loop);
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

sf::Sound& SoundManger::getSound(Constants::SoundID id) {
    return m_sounds.at(id);
}
