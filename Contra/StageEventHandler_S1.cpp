#include "StageEventHandler_S1.h"
#include "Scene_Battle.h"
#include "ScreenManager.h"
#include "Enemy_Infary.h"
#include "GameManager.h"
#include "Game_TestBox.h"

void StageEventHandler_S1::Update(DWORD dt)
{
	StageEventHandler_Base::Update(dt);
	
	// STAGE CLEAR
	GameManager* gm = GameManager::GetInstance();
	if (gm->Test_IfPassStage() == CAN_PASS_STAGE)
	{
		return;
	}

	//-----------------------------------------------------

	Game_Screen* screen = ScreenManager::GetInstance()->Screen();

	// Fix camera position
	Game_SweeperBlock* sweeper = GetSweeper();
	float px, py;
	_srcScene->p1()->GetCenterPoint(px, py);

	if (px > _maxMovedLength && _maxMovedLength < MAX_MOVEABLE_LENGTH_STAGE_1)
	{
		_maxMovedLength = px;
	}
	else if (_maxMovedLength > BOSS_TRIGGER_RANGE_STAGE_1
		&& _maxMovedLength < MAX_MOVEABLE_LENGTH_STAGE_1)
	{
		_maxMovedLength += SWEEPER_TRIGGERED_SPEED_S1 * dt;
		_maxMovedLength = min(MAX_MOVEABLE_LENGTH_STAGE_1, _maxMovedLength);
	}
	else if (_maxMovedLength >= MAX_MOVEABLE_LENGTH_STAGE_1)
	{
		_maxMovedLength = MAX_MOVEABLE_LENGTH_STAGE_1;
		// start boss fight
		if (GameManager::GetInstance()->Get_StagePasscardRemain() > 4)
		{
			GameManager::GetInstance()->Set_StagePasscardAmount(4);
		}
	}
	
	if (!_toggleFreeCam)
	{
		screen->SetPosition(_maxMovedLength - screen->width() / 2.0f, screen->height());
		if (screen->x() <= 0)
			screen->SetPosition(0 , screen->height());
		else if (screen->x() + screen->width() > _srcScene->MapWidth())
			screen->SetPosition(_srcScene->MapWidth() - screen->width(), screen->height());
	}

	// Update sweeper
	sweeper->SetPosition(_maxMovedLength - screen->width() / 2.0f - sweeper->width() + 2, screen->height());
	float l, t, b, r;
	sweeper->GetBoundingBox(l, t, r, b);
	_srcScene->spatial->update(_sweeperID,(int) l,(int) b,(int) r,(int) t);
	
	// fix player position
	Game_Player* player = _srcScene->p1();
	if (player->x() < r)
	{
		player->SetPosition(r + 1, player->y());
		// re-update spatial
		float pl, pt, pb, pr;
		player->GetBoundingBox(pl, pt, pr, pb);
		_srcScene->spatial->update(_sweeperID, (int)pl, (int)pb, (int)pr, (int)pt);
	}
}

void StageEventHandler_S1::SpecificUpdate(DWORD dt, Game_ObjectBase* obj)
{
	if (dynamic_cast<Game_Bridge_S1*>(obj))
	{
		Game_Bridge_S1* bridge = (Game_Bridge_S1*)obj;
		Game_Player* p1 = _srcScene->p1();
		if (p1->x() >= 752 && p1->x() <= 896)
		{
			bridge->TriggerExplosion(1);
		}
		else if (p1->x() >= 1040 && p1->x() <= 1184)
		{
			bridge->TriggerExplosion(2);
		}
	}
}

void StageEventHandler_S1::Load()
{
	_srcScene->SetMapSize(3328, GAMESCREEN_HEIGHT);

	SoundSystem* SS = SoundSystem::getInstance();
	SS->playBGM(BGM_JUNGLE);

	// Parse map
	_srcScene->init_spatial();
	_srcScene->parseMap("textures\\MAP1");

	// Add sweeper block
	unique_ptr<Game_SweeperBlock> sweeper(new Game_SweeperBlock(-32, GAMESCREEN_HEIGHT, Z_INDEX_TERRAIN, 32, GAMESCREEN_HEIGHT));
	_sweeperID =  _srcScene->add_object(move(sweeper));

	// setOther game params
	GameManager::GetInstance()->Set_StagePasscardAmount(5);

	// default load
	StageEventHandler_Base::Load();
}

void StageEventHandler_S1::CompleteStage()
{
	StageEventHandler_Base::CompleteStage();
	GameManager::GetInstance()->ReceiveSignal(SIG_LOADING_STAGE_3, _srcScene);
	_srcScene->PAUSE();
}

Game_SweeperBlock* StageEventHandler_S1::GetSweeper()
{
	return (Game_SweeperBlock*)(_srcScene->getObjectByID(_sweeperID));
}

// ===================================================================
// EVENTS


void StageEventHandler_S1::HelpGetRevivePoint(float& posX, float& posY)
{
	Game_SweeperBlock* sweeper = GetSweeper();
	unique_ptr<Game_TestBox>testbox(new Game_TestBox(0, 0, 0, PLAYER_BASE_WIDTH, PLAYER_BASE_HEIGHT, 0, 0));

	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());

	vector<int> id_list = ScreenManager::GetInstance()->Screen()->Get_ObjectsID_InsideScreen(scene->spatial.get(), GET_OBJECTS_RANGE);
	vector<PGAMEOBJECT>* coObjects = scene->getObjectById(id_list);

	Game_Screen* screen = ScreenManager::GetInstance()->Screen();

	float adding = -8;

	testbox->SetPosition(screen->x(), screen->y() - 16);

	bool canSpawn = false;
	while (!canSpawn && testbox->x() + testbox->width() < _srcScene->MapWidth())
	{
		adding += 32;
		posX = sweeper->x() + sweeper->width() + adding;
		posY = screen->y() - 16;
		testbox->SetPosition(posX, posY);

		// Make testbox move down
		testbox->SetSpeed(0, -scene->MapWidth());
		testbox->Update(1, coObjects);
		// Get Collisions and handle them.
		vector<PCOLLISIONEVENT>* coEvents = testbox->GetCollisionList();
		for (int i = 0; i < coEvents->size(); i++)
		{
			PCOLLISIONEVENT e = coEvents->at(i);
			// Check if under player have any terrain
			if (dynamic_cast<Game_DeadlyBlock*>(e->obj))
			{
				canSpawn = false;
				break;
			}

			if (dynamic_cast<Game_Terrain*>(e->obj))
			{
				canSpawn = true;
				break;
			}
		}
	}

	if (!canSpawn)
	{
		posX = sweeper->x() + sweeper->width() + 16;
		posY = _srcScene->MapHeight() - 16;
	}
}

void StageEventHandler_S1::Perform_StageClearEvent(DWORD dt)
{
	Game_Player* player = _srcScene->p1();
	player->SetAuto(true);
	//player->SetImmortal(true);
	// SCENE: boss die
	if (!S1_BossDie)
	{
		S1_BossDie = true;
		_srcScene->MassKilling();
		_WaitForBossDie = S1_WAIT_FOR_BOSS_DIE;
	}

	if (_WaitForBossDie > dt)
	{
		_WaitForBossDie -= dt;
		return;
	}

	// SCENE: player move to base 
	if (player->x() < 3218)
	{
		if (!player->Test_IfHaveAction())
			player->AddAction(DIK_RIGHT);
	}
	else if (player->x() <= 3290)
	{
		if (!player->Test_IfHaveAction())
		{
			if (!S1_firstJump && !player->IsOnGround())
			{
				// do nothing, wait to player stand on ground
			}
			if (!S1_firstJump && player->IsOnGround())
			{
				player->AddAction(DIK_P);
				S1_firstJump = true;
			}
			else
				player->AddAction(DIK_RIGHT);
		}
	}
	else
	{
		player->teleport(_srcScene->MapWidth() + 100, _srcScene->MapHeight());
		if (_WaitForClearStage >= WAIT_STAGECLEAR_MAXVALUE)
		{
			_WaitForClearStage = 1000;
		}
	}

}