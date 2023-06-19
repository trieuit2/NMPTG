#pragma once
#include "Scene_Base.h"

#define SCENE_LOADING_STAGE_WAIT_INTERVAL 1500

class Scene_LoadingStage : public Scene_Base
{
	private:
		
		int _StageID;
		void Init_Stage1();
		void Init_Stage3();
		void Finish_Loading();
		DWORD _waitingTick = 0;
		bool _finishLoading = false;
	public:
		Scene_LoadingStage(int stageId) : Scene_Base() { _StageID = stageId; }
		~Scene_LoadingStage() { Unload(); }
		void Update(DWORD dt) override;
		void Render() override;
		void Load() override;
		void Unload() override;

		void Init_Stage(int& id, int stage, const wchar_t* str);

};

