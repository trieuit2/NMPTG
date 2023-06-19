#pragma once
#include "debug.h"
#include "StageEventHandler_S1.h"
#include "StageEventHandler_S3.h"
#include "Scene_LoadingStage.h"
#include "ScreenManager.h"
#include "Textures.h"

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	10

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2
#define ASSETS_SECTION_DICT 3

#define MAX_SCENE_LINE 1024

enum STAGE
{
	FILTER_STAGE,
	SIG_PLAY_INTRO,
	SIG_PlAY_END_GAME,
	SIG_PLAY_CREDIT,
	SIG_PLAY_GAME_OVER,
	SIG_PLAY_STAGE_1,
	SIG_PLAY_STAGE_2,
	SIG_PLAY_STAGE_3,
	SIG_PLAY_STAGE_4,
	SIG_LOADING_STAGE_1,
	SIG_LOADING_STAGE_2,
	SIG_LOADING_STAGE_3,
	SIG_LOADING_STAGE_4,
	SCENE_BLANK_SCREEN,
	SCENE_STAGE_1,
	SCENE_STAGE_2,
	SCENE_STAGE_3,
	SCENE_STAGE_4
};

#define CAN_PASS_STAGE 1
#define CANT_PASS_STAGE 0
#define PASSCARD_NOT_INIT -1

typedef unsigned int UINT;

class GameManager
{
	private:
		static GameManager* __instance;

		// signal
		
		int _signal = -1;
		Scene_Base* _signalSender = NULL;
		void SignalHandler();

		// stage
		int _currentStage = -1;
		UINT _coin = 0;
		UINT _P1_score = 0;
		//UINT _P2_score = 0;
		int _stagePasscard = -1;
		int _saved_P1_Gun = GUN_N;
		int _saved_P1_Life = 0;
		void InitGame();
		void InitNewLife();
		

		// scene
		void Create_Start_Screen();
		void Create_GAME_OVER_Screen();
		void Create_Stage_1();
		void Create_Stage_3();
		void Create_LoadingStage(int stageID);
		void _ParseSection_SPRITES(string line);
		void _ParseSection_ANIMATIONS(string line);

		

		void _ParseSection_TEXTURES(string line);

		void _ParseSection_ASSETS(string line);
		void LoadAssets(LPCWSTR assetFile);
	public:
		void Load(LPCWSTR gameFile);
		static GameManager* GetInstance();
		GameManager() {}

		void Update(DWORD dt);

		// Scene control

		void ReceiveSignal(int signal, Scene_Base* sender);
		void StartApplication();

		// Game control
		void ResetScore_P1() { _P1_score = 0; }
		void GainScore_P1(UINT score) { _P1_score += score; }
		//void GainScore_P2(UINT score) { _P2_score += score; }
		void UseCoin() 
		{
			if (_coin > 0)
			{
				_coin--;
				InitNewLife();
			}
		}
		void SaveGun_P1(int gunID) { _saved_P1_Gun = gunID; }
		void SaveLife_P1(int hp) { _saved_P1_Life = hp; }

		UINT GetScore_P1() { return _P1_score; }
		//UINT GetScore_P2() { return _P2_score; }
		UINT GetCoin() { return _coin; }
		int GetSavedGun_P1() { return _saved_P1_Gun; }
		int GetSavedLife_P1() { return _saved_P1_Life; }
		int GetCurrentStage() { return _currentStage; }
		int Get_StagePasscardRemain() { return _stagePasscard; }
		void Set_StagePasscardAmount(int amount) { _stagePasscard = amount; }
		int Test_IfPassStage() 
		{
			if (_stagePasscard == 0)
				return CAN_PASS_STAGE;
			else if (_stagePasscard < 0)
				return CANT_PASS_STAGE;
			return PASSCARD_NOT_INIT;
		}

		void Gain_StagePasscard() { _stagePasscard --; }
		StageEventHandler_Base* Get_StageEventHandler(int stage, Scene_Battle* scene);


		//SPEED upgrade
		float _Speed_Upgrade = 1;
public:
	void reset_Speed_Upgrade();
	void add_Speed_Upgrade();
	float& Speed_Upgrade();
	void reset_player_parameter();
};

