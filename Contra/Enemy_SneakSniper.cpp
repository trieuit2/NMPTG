#include "Enemy_SneakSniper.h"
#include "Scene_Battle.h"
#include "Contra_GET_ANI.h"
#include "State_Station.h"
#include "GameManager.h"

int Enemy_SneakSniper::CharID()
{
	return SNEAKY_SNIPER;
}

void Enemy_SneakSniper::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	Game_StationEnemy::Update(dt, coObjects);
	if (_state->StateId() == STATE_IDLE)
		_ghost = true;
	else if (_state->StateId() != STATE_DIE)
		_ghost = false;
}

void Enemy_SneakSniper::Execute_DieAction()
{
	Game_StationEnemy::Execute_DieAction();
	jump();
}

void Enemy_SneakSniper::Execute_BeforeDelete()
{
	if (_die)
	{
		CreateDieAnimation(ANI_EXPLOSION_ARMY);
	}
}

void Enemy_SneakSniper::UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	if (_ActionQueue.size() > 0)
		return;

	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	Game_Player* player = scene->p1();

	if (!_needRender || !player->NeedRender())
		return;

	// Wait to change state
	if (_waitToChangeState > dt)
	{
		_waitToChangeState -= dt;
	}
	else
	{
		switch (_currentState)
		{
		case SS_HIDE:
			// emerge
			_waitToChangeState = SNEAKSNIPER_WAIT_TO_SHOOT_INTERVAL - (dt - _waitToChangeState);
			AddAction(DIK_O);
			_currentState = SS_WAIT_TO_SHOOT;
			break;
		case SS_WAIT_TO_SHOOT:
			// Shoot then wait to hide
			_waitToChangeState = SNEAKSNIPER_WAIT_TO_HIDE_INTERVAL - (dt - _waitToChangeState);
			AddAction(DIK_NUMPAD2);
			AddAction(DIK_PAUSE,2);
			AddAction(DIK_O);
			AddAction(DIK_PAUSE,5);
			AddAction(DIK_NUMPAD4);
			_currentState = SS_WAIT_TO_HIDE;
			break;
		case SS_WAIT_TO_HIDE:
			// hiding
			_waitToChangeState = SNEAKSNIPER_HIDING_INTERVAL - (dt - _waitToChangeState);
			AddAction(DIK_P);
			_currentState = SS_HIDE;
			break;
		default:
			break;
		}
	}

}

void Enemy_SneakSniper::GetCustomSize(int state, int& width, int& height)
{
	switch (state)
	{
	case STATE_IDLE:
		width = SNEAKSNIPER_HIDE_WIDTH;
		height = SNEAKSNIPER_HIDE_HEIGHT;
		break;
	case STATE_WALK:
		width = SNEAKSNIPER_BASE_WIDTH;
		height = SNEAKSNIPER_BASE_HEIGHT;
		break;
	case STATE_DIE:
		width = SNEAKSNIPER_BASE_WIDTH;
		height = SNEAKSNIPER_BASE_HEIGHT;
		break;
	default:
		break;
	}
}

void Enemy_SneakSniper::Shoot(int DIR)
{
	if (_weapon == NULL || _GunReloadInterval > 0)
		return;
	float x, y;
	GetCenterPoint(x, y);
	BULLETHELPER::getSpawnCor(x, y, CharID(), Sprite_ActID(), DIR);

	_GunReloadInterval = _weapon->FireRate();

	// SneakSniper only shoot left
	_weapon->Fire(x, y, DIR_LEFT);
}

void Enemy_SneakSniper::UpdateState()
{
	if (_state == NULL)
		_state.reset(new State_Station(this));
	Game_StationEnemy::UpdateState();
}

void Enemy_SneakSniper_Base::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	Game_StationEnemy::Update(dt, coObjects);
		
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	Game_Player* player = scene->p1();

	if (GameManager::GetInstance()->Get_StagePasscardRemain() > 4 || _state->StateId() == STATE_IDLE)
		_ghost = true;
	else if (_state->StateId() != STATE_DIE)
		_ghost = false;
}


void Enemy_SneakSniper_Base::Execute_DieAction()
{
	Game_StationEnemy::Execute_DieAction();
	jump();
	_ForceX = 50;
	GameManager::GetInstance()->Gain_StagePasscard();
}