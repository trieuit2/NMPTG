#pragma once

using namespace std; 
#include <Windows.h>
#include "ScreenManager.h"
#include "Game_ObjectBase.h"

class Game_KeyInput
{
	private:
		static Game_KeyInput* __instance;
		vector<Game_ObjectBase*> _objects;
		Scene_Base* _scene;
	public:
		Game_KeyInput() {}
		static Game_KeyInput* GetInstance();

		void AddObjectControl(Game_ObjectBase* obj);
		void AddSceneControl(Scene_Base* scene);
		void ClearObjects();
		void ClearScene();
		void ClearAll();

		void KeyState(BYTE* state);
		void OnKeyDown(int KeyCode);
		void OnKeyUp(int KeyCode);
};

