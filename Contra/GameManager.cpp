#include "GameManager.h"
#include "ScreenManager.h"
#include "CAnimation_OneLoop.h"
#define GAME_FILE_SECTION_UNKNOWN 0
#define MAX_GAME_LINE 100
#define GAME_FILE_SECTION_SETTINGS 1
#define GAME_FILE_SECTION_TEXTURES 2
#define GAME_FILE_SECTION_ASSESTS 3
GameManager* GameManager::__instance = NULL;
void GameManager::Load(LPCWSTR gameFile)
{
	DebugOut(L"[INFO] Start loading game file : %s\n", gameFile);

	ifstream f;
	f.open(gameFile);
	char str[MAX_GAME_LINE];

	// current resource section flag
	int section = GAME_FILE_SECTION_UNKNOWN;

	while (f.getline(str, MAX_GAME_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SETTINGS]") { section = GAME_FILE_SECTION_SETTINGS; continue; }
		if (line == "[TEXTURES]") { section = GAME_FILE_SECTION_TEXTURES; continue; }
		if (line == "[ASSETS]") { section = GAME_FILE_SECTION_ASSESTS; continue; }
		if (line[0] == '[')
		{
			section = GAME_FILE_SECTION_UNKNOWN;
			DebugOut(L"[ERROR] Unknown section: %s\n", ToLPCWSTR(line));
			continue;
		}

		//
		// data section
		//
		switch (section)
		{
		//case GAME_FILE_SECTION_SETTINGS: _ParseSection_SETTINGS(line); break;
		case GAME_FILE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case GAME_FILE_SECTION_ASSESTS: _ParseSection_ASSETS(line); break;
		
		}
	}
	f.close();

	DebugOut(L"[INFO] Loading game file : %s has been loaded successfully\n", gameFile);
}


void GameManager::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);

	CTextures::GetInstance()->Add(texID, path.c_str());
}

void GameManager::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}
void GameManager::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }


		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}
void GameManager::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}



void GameManager::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());
	int size = tokens.size();
	LPANIMATION ani;
	if (size % 2 == 0)
	{
		if (atoi(tokens[size - 1].c_str()) == 1)
			ani = new CAnimation_OneLoop;
		else
			ani = new CAnimation;
		size--;
	}
	else
	{
		ani = new CAnimation;
	}


	

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < size; i += 2)	// why i+=2 ?  sprite_id | frame_time
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

//======================================================================================================
// PROCESSOR

GameManager* GameManager::GetInstance()
{
	if (__instance == NULL) __instance = new GameManager();
	return __instance;
}


void GameManager::Update(DWORD dt)
{
	SignalHandler();
}

void GameManager::SignalHandler()
{
	switch (_signal)
	{
	case SIG_PLAY_INTRO:
		Create_Start_Screen();
		break;
	case SIG_PlAY_END_GAME:
		break;
	case SIG_PLAY_CREDIT:
		break;
	case SIG_PLAY_STAGE_1:
		Create_Stage_1();
		break;
	case SIG_PLAY_STAGE_3:
		Create_Stage_3();
		break;
	case SIG_LOADING_STAGE_1:
		Create_LoadingStage(SCENE_STAGE_1);
		break;
	case SIG_LOADING_STAGE_3:
		Create_LoadingStage(SCENE_STAGE_3);
		break;
	case SIG_PLAY_GAME_OVER:
		Create_GAME_OVER_Screen();
	default:
		break;
	}
	_signal = 0;
	_signalSender = NULL;
}

void GameManager::ReceiveSignal(int signal, Scene_Base* sender)
{
	_signal = signal;
	_signalSender = sender;
}

StageEventHandler_Base* GameManager::Get_StageEventHandler(int stage, Scene_Battle* scene)
{
	StageEventHandler_Base* handler;
	switch (stage)
	{
	case SCENE_STAGE_1:
		handler = new StageEventHandler_S1(scene);
		return handler;
		break;
	case SCENE_STAGE_3:
		handler = new StageEventHandler_S3(scene);
		return handler;
		break;
	default:
		DebugOut(L"[ERROR] Unknown Stage id. Get StageEventHandler failed.\n");
		return NULL;
	}
}

void GameManager::reset_Speed_Upgrade()
{
	_Speed_Upgrade = 1;
}

void GameManager::add_Speed_Upgrade()
{
	_Speed_Upgrade+=0.15;
}

float& GameManager::Speed_Upgrade()
{
	return _Speed_Upgrade;
}

void GameManager::reset_player_parameter()
{
	ResetScore_P1();
	reset_Speed_Upgrade();
}

void GameManager::InitGame()
{
	_coin = 3;
	_P1_score = 0;
	//_P2_score = 0;
	InitNewLife();
}

void GameManager::InitNewLife()
{
	_saved_P1_Gun = GUN_N;
	_saved_P1_Life = 3;
}

void GameManager::StartApplication()
{
	ScreenManager* screenManager = ScreenManager::GetInstance();
	Create_Start_Screen();
}

//======================================================================================
// CREATE SCENE
void GameManager::Create_Start_Screen()
{
	InitGame();

	ScreenManager* screenManager = ScreenManager::GetInstance();
	screenManager->Create_Scene_Start();

	screenManager->Scene()->Load();
}
void GameManager::Create_GAME_OVER_Screen()
{
	ScreenManager* screenManager = ScreenManager::GetInstance();
	screenManager->Create_Scene_GAME_OVER();

	screenManager->Scene()->Load();
}
void GameManager::Create_Stage_1()
{
	ScreenManager* screenManager = ScreenManager::GetInstance();
	screenManager->Create_Scene_Battle();
	Scene_Battle* scene = (Scene_Battle*)(screenManager->Scene());

	scene->SetStageEventHandler(Get_StageEventHandler(SCENE_STAGE_1, scene));

	_currentStage = SCENE_STAGE_1;
	_stagePasscard = -1;

	scene->Load();
}

void GameManager::Create_Stage_3()
{
	ScreenManager* screenManager = ScreenManager::GetInstance();
	screenManager->Create_Scene_Battle();
	Scene_Battle* scene = (Scene_Battle*)(screenManager->Scene());

	_currentStage = SCENE_STAGE_3;
	_stagePasscard = -1;

	scene->SetStageEventHandler(Get_StageEventHandler(SCENE_STAGE_3, scene));

	scene->Load();
}

void GameManager::Create_LoadingStage(int stageID)
{
	ScreenManager* screenManager = ScreenManager::GetInstance();
	screenManager->Create_Scene_LoadingStage(stageID);
	Scene_LoadingStage* scene = (Scene_LoadingStage*)(screenManager->Scene());

	scene->Load();
}