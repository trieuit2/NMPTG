#include "MusicManager.h"
#define MUSIC_PATH "music/"
#define BGM_PATH MUSIC_PATH "bgm/"
#define BGM_JUNGLE_PATH BGM_PATH "2 - Jungle  Hangar (Stages 1  7).mp3"
#define BGM_TITLE_PATH BGM_PATH "1 - Title Screen.mp3"
#define BGM_WATERFALL_PATH BGM_PATH "5 - Waterfall (Stage 3).mp3"
#define BGM_GAMEOVER_PATH BGM_PATH "11 - Game Over.mp3"
#define BGM_ENDING_PATH BGM_PATH "10 - Ending.mp3"

#define SFX_PATH MUSIC_PATH "sfx/"
#define SFX_CONTRA_DEATH_PATH SFX_PATH  "death.mp3"
#define SFX_BOSS_DEFEAT_PATH SFX_PATH  "boss-defeat.mp3"
#define SFX_BASE_EXPLODE_PATH SFX_PATH  "base-explosion.mp3"

#define SFX_CONTRA_DEFAULTGUN_PATH SFX_PATH "enemy-gun.mp3"
#define SFX_CONTRA_RIFLE_PATH SFX_PATH "enemy-gun.mp3"
#define SFX_CONTRA_SPREAD_PATH SFX_PATH "spread.mp3"
#define SFX_CONTRA_FLAME_PATH SFX_PATH "flame.mp3"
#define SFX_CONTRA_LASER_PATH SFX_PATH "laser.mp3"

#define SFX_CONTRA_LAND_PATH SFX_PATH "land.mp3"
#define SFX_CONTRA_ELECTRIC_PATH SFX_PATH "electro.mp3"
#define SFX_CONTRA_UPGRADE_PATH SFX_PATH "1-up.mp3"

#define SFX_ENEMY_SHOOT_1_PATH SFX_PATH "enemy-gun.mp3"
#define SFX_ENEMY_SHOOT_2_PATH SFX_PATH "enemy-gun-2.mp3"

#define SFX_ENEMY_HIT_PATH SFX_PATH "enemy-hit.mp3"
#define SFX_ENEMY_EXPLODE_1_PATH SFX_PATH "flame-gun.mp3"//"explode.mp3"
#define SFX_ENEMY_EXPLODE_2_PATH SFX_PATH "explode-2.mp3"

#define SFX_MAJOR_EXPLODE_PATH SFX_PATH "major-explosion.mp3"

#define SFX_NEXTROUND_PATH SFX_PATH "area-clear.mp3"
#define SFX_GAMEOVER_PATH SFX_PATH "game-over.mp3"
SoundSystem* SoundSystem::instance = nullptr;
SoundSystem::SoundSystem() {
    if(!DEBUG_FMOD_LOG)
    FMOD::Debug_Initialize(FMOD_DEBUG_LEVEL_NONE, FMOD_DEBUG_MODE_TTY, nullptr, nullptr);
    FMOD::System_Create(&system);
    system->init(32, FMOD_INIT_NORMAL, nullptr);
#pragma region INIT SFX
    system->createStream(SFX_CONTRA_DEATH_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_CONTRA_DEATH]);
    system->createStream(SFX_BOSS_DEFEAT_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_BOSS_DEFEAT]);
    system->createStream(SFX_BASE_EXPLODE_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_BASE_EXPLODE]);
    system->createStream(SFX_CONTRA_DEFAULTGUN_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_CONTRA_DEFAULTGUN]);
    system->createStream(SFX_CONTRA_RIFLE_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_CONTRA_RIFLE]);
    system->createStream(SFX_CONTRA_SPREAD_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_CONTRA_SPREAD]);
    system->createStream(SFX_CONTRA_LASER_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_CONTRA_LASER]);
    system->createStream(SFX_CONTRA_LAND_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_CONTRA_LAND]);
    system->createStream(SFX_CONTRA_FLAME_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_CONTRA_FLAME]);
    system->createStream(SFX_CONTRA_ELECTRIC_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_CONTRA_ELECTRIC]);
    system->createStream(SFX_CONTRA_UPGRADE_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_CONTRA_UPGRADE]);
    system->createStream(SFX_ENEMY_SHOOT_1_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_ENEMY_SHOOT_1]);
    system->createStream(SFX_ENEMY_SHOOT_2_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_ENEMY_SHOOT_2]);
    system->createStream(SFX_ENEMY_HIT_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_ENEMY_HIT]);
    system->createStream(SFX_ENEMY_EXPLODE_1_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_ENEMY_EXPLODE_1]);
    system->createStream(SFX_ENEMY_EXPLODE_2_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_ENEMY_EXPLODE_2]);
    system->createStream(SFX_MAJOR_EXPLODE_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_MAJOR_EXPLODE]);
    system->createStream(SFX_NEXTROUND_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_NEXTROUND]);
    system->createStream(SFX_GAMEOVER_PATH, FMOD_DEFAULT, nullptr, &sfx[SFX_GAMEOVER]);
#pragma endregion

    system->createStream(BGM_JUNGLE_PATH, FMOD_LOOP_NORMAL, nullptr, &bgm[BGM_JUNGLE]);
    system->createStream(BGM_TITLE_PATH, FMOD_DEFAULT, nullptr, &bgm[BGM_TITLE]);
    system->createStream(BGM_WATERFALL_PATH, FMOD_LOOP_NORMAL, nullptr, &bgm[BGM_WATERFALL]);
    system->createStream(BGM_GAMEOVER_PATH, FMOD_LOOP_NORMAL, nullptr, &bgm[BGM_GAME_OVER]);
    system->createStream(BGM_ENDING_PATH, FMOD_DEFAULT, nullptr, &bgm[BGM_ENDING]);
    bgmChannel = nullptr;
    sfxChannel_Contra = nullptr;
    sfxChannel_ContraMisc = nullptr;
    sfxChannel_Enemy = nullptr;
    sfxChannel_Env = nullptr;
}
