#include "Scene_Start.h"
#include "GameManager.h"


using namespace std;
void Scene_Start::KeyDownEventHandler(int KeyCode)
{
	if (KeyCode == DIK_A)
		if (startTimer == false)
		{
			startTimer = true;
			int id = 1;	
			AddBlinkingDarkEffect(90, 165, 70.0f, 12.0f, id);

		}
}

void Scene_Start::init()
{
	AddImage_Static(GAMESCREEN_WIDTH / 2, GAMESCREEN_HEIGHT / 2, 0, 989900, 1, RENDER_MODE_CENTER);
	AddImage(GAMESCREEN_WIDTH / 2, GAMESCREEN_HEIGHT / 2, 2, 1099060, RENDER_MODE_CENTER);
}

void Scene_Start::Update(DWORD dt)
{
	if (startTimer)
	{
		if (_waitingTick > dt)
		{
			_waitingTick -= dt;
		}
		else
		{
			nextScene();
			return;
		}
	}
	for (auto& pic : _images)
	{
		Game_Picture* obj = pic.second.get();
		if (obj != NULL)
			obj->Update(dt);
	}
}

/*void Scene_Start::Render()
{
	RenderImagePhase();
/}*/

void Scene_Start::Load()
{
	SoundSystem* SS = SoundSystem::getInstance();
	SS->stopBGM();
	SS->playBGM(BGM_TITLE);
	init();
}

void Scene_Start::Unload()
{
	_images.clear();
}

void Scene_Start::nextScene()
{
	_NextScene(SIG_LOADING_STAGE_1);
}


