#include "Scene_LoadingStage.h"
#include "GameManager.h"
#include "Contra_ANI_ID.h"
#include "Word.h"
#include "Game_Picture_Static.h"
void Scene_LoadingStage::Update(DWORD dt)
{
	if (_finishLoading)
		return;

	if (_waitingTick > dt)
	{
		_waitingTick -= dt;
	}
	else
	{
		Finish_Loading();
		return;
	}

	for (auto& pic : _images)
	{
		Game_Picture* obj = pic.second.get();
		if (obj != NULL)
			obj->Update(dt);
	}
}

void Scene_LoadingStage::Render()
{
	vector<Game_Picture*> RenderQueue;
	
	for (auto& pic : _images)
	{
		Game_Picture* obj = pic.second.get();

		if (obj == NULL)
			continue;

		if (RenderQueue.size() == 0)
		{
			RenderQueue.push_back(obj);
			continue;
		}
		int j = int(RenderQueue.size());
		while (j > 0 && obj->z() < RenderQueue[j - 1]->z())
		{
			j--;
		}
		std::vector<Game_Picture*>::iterator it = RenderQueue.begin();
		RenderQueue.insert(it + j, obj);
	}
	float BG_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	CGame::GetInstance()->GetDirect3DDevice()->ClearRenderTargetView(CGame::GetInstance()->GetRenderTargetView(), BG_color);
	float x, y;
	ScreenManager::GetInstance()->Screen()->GetCenterPoint(x, y);
	for (int i = 0; i < RenderQueue.size(); i++)
	{
		RenderQueue[i]->Render();
	}
}

void Scene_LoadingStage::Load()
{
	SoundSystem* SS = SoundSystem::getInstance();
	SS->stopBGM();

	switch (_StageID)
	{
	case SCENE_STAGE_1:
		Init_Stage1();
		break;
	case SCENE_STAGE_3:
		Init_Stage3();
		break;
	}

	_waitingTick = SCENE_LOADING_STAGE_WAIT_INTERVAL;
}

void Scene_LoadingStage::Unload()
{
	_images.clear();
}
void Scene_LoadingStage::Init_Stage(int& id, int stage, const wchar_t* str)
{

	int height;
	int start_dis;
	start_dis = 10;
	height = 30;
	AddText(start_dis, height, L"1P", id, 2.0f, RENDER_MODE_CENTER);
	start_dis = 80;
	AddNumber(start_dis, height, GameManager::GetInstance()->GetScore_P1(), id, 2, RENDER_MODE_CENTER);
	AddBlinkingDarkEffect(160.0f, 30.0f, 160, 10, id);
	start_dis = 10;
	height = 45;
	AddText(start_dis, height, L"REST 3", id, 2, RENDER_MODE_CENTER);

	start_dis = 80;
	height = 60;
	AddText(start_dis, height, L"HI 00000", id, 2, RENDER_MODE_CENTER);
	AddBlinkingDarkEffect(150.0f, 60.0f, 80, 10, id);
	start_dis = 80;
	height = 120;
	wstring stage_name = L"STAGE " + to_wstring(stage);
	AddText(start_dis, height,stage_name.c_str(), id, 2, RENDER_MODE_CENTER);

	start_dis = 80;
	height = 135;
	AddText(start_dis, height,str, id, 2, RENDER_MODE_CENTER);
}
void Scene_LoadingStage::Init_Stage1()
{
	int id = 1;
	Init_Stage(id, 1, L"Jungle");
	int x = 0, y = 0;
	//
//	AddText(start_dis, height, L"LOADING ", id, 2, RENDER_MODE_CENTER);
//	AddNumber(start_dis, height, 1, id, 2, RENDER_MODE_CENTER);
}

void Scene_LoadingStage::Init_Stage3()
{
	int id = 1;
	Init_Stage(id, 3, L"WATERFALL");
	//AddImage(GAMESCREEN_WIDTH / 2, GAMESCREEN_HEIGHT / 2, 1, CONTRA_ANI_WALK_LEFT, RENDER_MODE_CENTER);
}

void Scene_LoadingStage::Finish_Loading()
{
	switch (_StageID)
	{
	case SCENE_STAGE_1:
		GameManager::GetInstance()->ReceiveSignal(SIG_PLAY_STAGE_1, this);
		break;
	case SCENE_STAGE_3:
		GameManager::GetInstance()->ReceiveSignal(SIG_PLAY_STAGE_3, this);
		break;
	}
	_finishLoading = true;
}