#pragma once
#include "debug.h"

class Scene_Battle;
class Game_ObjectBase;

#define STAGE_DEBUG_ALLOW true
#define WAIT_ENDGAME_MAXVALUE 1000000
#define ENDGAME_INTERVAL 1600
#define WAIT_STAGECLEAR_MAXVALUE 1000000

class StageEventHandler_Base
{
	protected:
		Scene_Battle* _srcScene=NULL;
		bool _toggleFreeCam = false;
		DWORD _WaitForEndGame = WAIT_ENDGAME_MAXVALUE;
		DWORD _WaitForClearStage = WAIT_STAGECLEAR_MAXVALUE;
		void Set_Camera_Focus_Player();
		void Debug_KeyDownEventHandler(int KeyCode);
		virtual void Perform_StageClearEvent(DWORD dt) {}
	public:
		StageEventHandler_Base(Scene_Battle* src);

		virtual void Update(DWORD dt);
		virtual void SpecificUpdate(DWORD dt, Game_ObjectBase* obj) {}
		virtual void RenderHUD() {}
		virtual void Load();
		virtual void CompleteStage();
		virtual void GameOver();
		virtual void KeyDownEventHandler(int KeyCode);

		virtual void HelpGetRevivePoint(float &posX, float &posY) { }
};

