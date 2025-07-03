#pragma once

#include "ResourseInc/BaseResourceManager.h"
#include <SFML/Audio.hpp>
#include <unordered_map>
#include "Constants.h"

// Global mapping of sound IDs to file names
const std::unordered_map<Constants::SoundID, std::string> SoundFileMap = {
    {Constants::SoundID::BACKGROUNDMUSIC, "background_game_play.ogg"},
    {Constants::SoundID::MENUMUSIC, "menu_music.ogg"},
    {Constants::SoundID::MATCHMAKINGMUSIC, "matchmaking_music.ogg"},
    {Constants::SoundID::GAMEOVERSOUND, "gameover.ogg"},
    {Constants::SoundID::RIFLESOUND, "AK47.ogg"},
    {Constants::SoundID::SHOTGUNSOUND, "shotgun_shot.ogg"},
    {Constants::SoundID::PISTOLSOUND, "pistol_shot.ogg"},
    {Constants::SoundID::SNIPERSOUND, "sniper_shot.ogg"},
    {Constants::SoundID::BUTTOUNEVENT, "button_sound.ogg"},
    {Constants::SoundID::HEARTBEAT, "heartbeat_sound.ogg"},
    {Constants::SoundID::VISIONUPGRADE, "vision_up.ogg"},
    {Constants::SoundID::SHIELDUPGRADE, "shield_sound.ogg"},
    {Constants::SoundID::HEALTHUPGRADE, "hp_sound.ogg"},
    {Constants::SoundID::SPEEDUPGRADE, "speedup.ogg"},
    {Constants::SoundID::SPEEDDOWN, "speeddown.ogg"},
    {Constants::SoundID::SPY, "spy.ogg"},
    {Constants::SoundID::GAMEBEGIN, "game_begin.ogg"},
    {Constants::SoundID::ENEMYDEATH, "charcter_death.ogg"},
    {Constants::SoundID::PLAYERDEATH, "charcter_death.ogg"},
    {Constants::SoundID::GAMEWINSOUND, "gamewin.ogg"},
    {Constants::SoundID::COINS, "coins-handling.ogg"},
    {Constants::SoundID::FOOTSTEP, "footsteps.ogg"},
    {Constants::SoundID::SCENARIO, "senario.ogg"}
};

// Singleton sound manager that plays, stops, and controls game sounds
class SoundManger : public BaseResourceManager<sf::SoundBuffer, Constants::SoundID> {
public:
    static SoundManger& instance();

    void play(Constants::SoundID id);
	void loop(Constants::SoundID id, bool loop);
	void pause(Constants::SoundID id);
    void setVolume(Constants::SoundID id, float volume);
    bool isPlaying(Constants::SoundID id) const;
	sf::Sound& getSound(Constants::SoundID id);
	void stop(Constants::SoundID id);
	void mute(bool mute, bool pause);    
	void unmute(bool mute, bool pause);

	sf::Time getPlayingOffset(Constants::SoundID id);

private:
    SoundManger();
	bool m_muted = false;
	bool m_paused = false;
    std::unordered_map<Constants::SoundID, sf::Sound> m_sounds;
};
