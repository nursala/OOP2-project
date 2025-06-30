#pragma once
#include "ResourseInc/BaseResourceManager.h"
#include <SFML/Audio.hpp>
#include <unordered_map>
#include "Constants.h"


const std::unordered_map<Constants::SoundID, std::string> SoundFileMap = {

	  {Constants::SoundID::BACKGROUNDMUSIC, "background_game_play.wav"} , {Constants::SoundID::MENUMUSIC, "menu_music.ogg"}
	, {Constants::SoundID::MATCHMAKINGMUSIC, "matchmaking_music.ogg"}   , {Constants::SoundID::GAMEOVERSOUND, "gameover.wav"}           
	, {Constants::SoundID::RIFLESOUND, "AK47.wav"}                      , {Constants::SoundID::SHOTGUNSOUND, "shotgun_shot.wav"}
	, {Constants::SoundID::PISTOLSOUND, "pistol_shot.ogg"}              , {Constants::SoundID::SNIPERSOUND, "sniper_shot.wav"}
	, {Constants::SoundID::BUTTOUNEVENT, "button_sound.ogg"}            , {Constants::SoundID::HEARTBEAT, "heartbeat_sound.ogg"}
	, {Constants::SoundID::VISIONUPGRADE, "vision_up.ogg"}              , {Constants::SoundID::SHIELDUPGRADE, "shield_sound.ogg"}
	, {Constants::SoundID::HEALTHUPGRADE, "hp_sound.ogg"}			    , {Constants::SoundID::SPEEDUPGRADE, "speedup.wav"}
	, {Constants::SoundID::SPEEDDOWN, "speeddown.wav"}                  , {Constants::SoundID::SPY, "spy.wav"}
	, {Constants::SoundID::GAMEBEGIN, "game_begin.ogg"}                 , {Constants::SoundID::ENEMYDEATH, "enemy_death.ogg"}
	, {Constants::SoundID::PLAYERDEATH, "playerdown.wav"}               , {Constants::SoundID::GAMEWINSOUND, "gamewin.wav"}
	, {Constants::SoundID::COINS, "coins-handling.wav"}                 , {Constants::SoundID::FOOTSTEP, "footsteps.wav"}
};

class SoundManger : public BaseResourceManager<sf::SoundBuffer, Constants::SoundID> {
public:
    static SoundManger& instance();

    void play(Constants::SoundID id);
    void pause(Constants::SoundID id);
    void setVolume(Constants::SoundID id, float volume);
    bool isPlaying(Constants::SoundID id) const;
	sf::Sound& getSound(Constants::SoundID id);
	void stop(Constants::SoundID id);
	void mute();    
	void unmute();  
private:
    SoundManger();
	bool m_muted = false;
    std::unordered_map<Constants::SoundID, sf::Sound> m_sounds;
};
