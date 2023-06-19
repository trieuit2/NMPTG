#pragma once

#include <vector>

using namespace std;

//#include "Game_Player.h"
//#include "Game_Terrain.h"
//#include "BattleManager.h"
#include "Game_Screen.h"
#include "Scene_Battle.h"

class GameManager;

class ScreenManager
{
private:
	static ScreenManager* __instance;
	vector<Game_ObjectBase*> _drawCollection;
	Game_Screen* _screen = NULL;
	Scene_Base* _scene = NULL;

	// Test
	void Create_Scene_Demo() {}
	void Unload_Scene();
public:
	static ScreenManager* GetInstance();
	ScreenManager();
	Game_Screen* Screen() { return _screen; }
	Scene_Base* Scene() { return _scene; }
	void Render();
	void Update(DWORD dt);
	//void Load(LPCWSTR gameFile);

	void Create_Scene_Battle();
	void Create_Scene_LoadingStage(int stageID);
	void Create_Scene_Start();
	void Create_Scene_GAME_OVER();
};

