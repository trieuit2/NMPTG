#include "ScreenManager.h"
#include "GameManager.h"
#include "Game_KeyInput.h"
#include "Scene_Start.h"
#include "Scene_GameOver.h"
ScreenManager* ScreenManager::__instance = NULL;

ScreenManager* ScreenManager::GetInstance()
{
	if (__instance == NULL) __instance = new ScreenManager();
	return __instance;
}

ScreenManager::ScreenManager()
{
	_screen = new Game_Screen(0, 0);
}


void ScreenManager::Update(DWORD dt)
{
	if (_scene != NULL)
		_scene->Update(dt);
	// Camera Update
	//if (dynamic_cast<Scene_Battle*>(_scene))
	//	_screen->Update(dt, ((Scene_Battle*)_scene)->objects());
}

void ScreenManager::Render()
{
	if (_scene != NULL)
		_scene->Render();
}

//void ScreenManager::Load(LPCWSTR gameFile)
//{
//
//}


// CREATE SCENE
void ScreenManager::Unload_Scene()
{
	if (_scene != NULL)
	{
		_scene->Unload();
		delete _scene;

	}Game_KeyInput::GetInstance()->ClearAll();
}

void ScreenManager::Create_Scene_Battle()
{
	Unload_Scene();
	//Scene_Battle* scene = Scene_Battle::GenInstance();
	Scene_Battle* scene = new Scene_Battle();
	//scene->Create_Stage_Demo();
	_scene = scene;
	Game_KeyInput::GetInstance()->AddSceneControl(_scene);
}

void ScreenManager::Create_Scene_LoadingStage(int stageID)
{
	Unload_Scene();
	Scene_LoadingStage* scene = new Scene_LoadingStage(stageID);
	_scene = scene;
}
void ScreenManager::Create_Scene_Start()
{
	Unload_Scene();
	Scene_Base* scene = new Scene_Start();
	_scene = scene;
	Game_KeyInput::GetInstance()->AddSceneControl(_scene);
}
void ScreenManager::Create_Scene_GAME_OVER()
{
	Unload_Scene();
	Scene_Base* scene = new Scene_GameOver();
	_scene = scene;
	Game_KeyInput::GetInstance()->AddSceneControl(_scene);
}