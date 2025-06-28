#pragma once
#include "ResourseInc/BaseResourceManager.h"
#include <SFML/Audio.hpp>
#include <unordered_map>

enum class SoundID {
    SHOOT,BACKGROUNDMUSIC,MENUMUSIC,MATCHMAKINGMUSIC,GAMEOVERSOUND,
	GAMEWINSOUND,RIFLESOUND,SHOTGUNSOUND,PISTOLSOUND,SNIPERSOUND,
	BUTTOUNEVENT,HEARTBEAT,VISIONUPGRADE,SHIELDUPGRADE,HEALTHUPGRADE,
	SPEEDUPGRADE,SPEEDDOWN,SPY,GAMEBEGIN,ENEMYDEATH, PLAYERDEATH,
};

const std::unordered_map<SoundID, std::string> SoundFileMap = {

      {SoundID::BACKGROUNDMUSIC, "background_music.ogg"}    , {SoundID::MENUMUSIC, "menu_music.ogg"}
	, {SoundID::MATCHMAKINGMUSIC, "matchmaking_music.ogg"}  //, {SoundID::GAMEOVERSOUND, "game_over.ogg"}           
	, {SoundID::RIFLESOUND, "AK47.wav"}                     , {SoundID::SHOTGUNSOUND, "shotgun_shot.wav"}
	, {SoundID::PISTOLSOUND, "pistol_shot.ogg"}             , {SoundID::SNIPERSOUND, "sniper_shot.wav"}
	, {SoundID::BUTTOUNEVENT, "button_sound.ogg"}           , {SoundID::HEARTBEAT, "heartbeat_sound.ogg"}
	, {SoundID::VISIONUPGRADE, "vision_up.ogg"}             , {SoundID::SHIELDUPGRADE, "shield_sound.ogg"}
	, {SoundID::HEALTHUPGRADE, "hp_sound.ogg"}			  //, {SoundID::SPEEDUPGRADE, "speed_upgrade.ogg"}
	//, {SoundID::SPEEDDOWN, "speed_down.ogg"}                , {SoundID::SPY, "spy.ogg"}
	//, {SoundID::GAMEBEGIN, "game_begin.ogg"}                
	, {SoundID::ENEMYDEATH, "enemy_death.ogg"}
	, {SoundID::PLAYERDEATH, "player_death.ogg"}            , {SoundID::GAMEWINSOUND, "win_sound.ogg"}

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
