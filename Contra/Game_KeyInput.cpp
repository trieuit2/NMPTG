#include "Game_KeyInput.h"

Game_KeyInput* Game_KeyInput::__instance = NULL;

Game_KeyInput* Game_KeyInput::GetInstance()
{
	if (__instance == NULL) __instance = new Game_KeyInput();
	return __instance;
}

void Game_KeyInput::AddObjectControl(Game_ObjectBase* obj)
{
	_objects.push_back(obj);
}

void Game_KeyInput::AddSceneControl(Scene_Base* scene)
{
	_scene = scene;
}

void Game_KeyInput::ClearObjects()
{
	_objects.clear();
}

void Game_KeyInput::ClearScene()
{
	_scene = NULL;
}

void Game_KeyInput::ClearAll()
{
	ClearObjects();
	ClearScene();
}

void Game_KeyInput::OnKeyDown(int KeyCode)
{
	for (int i = 0; i < _objects.size(); i++)
	{
		if (dynamic_cast<Game_Player*>(_objects[i]))
		{
			Game_Player* player = (Game_Player*)_objects[i];
			if (!player->IsAuto())
				_objects[i]->KeyDownEventHandler(KeyCode);
		}
		else
			_objects[i]->KeyDownEventHandler(KeyCode);
	}
	if (_scene != NULL)
		_scene->KeyDownEventHandler(KeyCode);
}

void Game_KeyInput::OnKeyUp(int KeyCode)
{
	for (int i = 0; i < _objects.size(); i++)
	{
		if (dynamic_cast<Game_Player*>(_objects[i]))
		{
			Game_Player* player = (Game_Player*)_objects[i];
			if (!player->IsAuto())
				_objects[i]->KeyUpEventHandler(KeyCode);
		}
		else 
			_objects[i]->KeyUpEventHandler(KeyCode);
	}
	if (_scene != NULL)
		_scene->KeyUpEventHandler(KeyCode);
}

void Game_KeyInput::KeyState(BYTE* state)
{
	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->KeyStateHandler(state);
	}
}