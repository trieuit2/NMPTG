#include "Enemy_Sniper.h"
#include "Scene_Battle.h"
#include "Contra_GET_ANI.h"
#include "State_Contra_Base.h"

int Enemy_Sniper::CharID()
{
	return SNIPER;
}

void Enemy_Sniper::Execute_DieAction()
{
	Game_StationEnemy::Execute_DieAction();
	jump();
}

void Enemy_Sniper::Execute_BeforeDelete()
{
	if (_die)
	{
		CreateDieAnimation(ANI_EXPLOSION_ARMY);
	}
}

void Enemy_Sniper::UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	Game_Player* player = scene->p1();

	if (_ActionQueue.size() > 0)
		return;

	switch (_lockDir)
	{
	case DIR_LEFT:
		AddAction(DIK_NUMPAD4);
		break;
	case DIR_RIGHT:
		AddAction(DIK_NUMPAD6);
		break;
	case DIR_BOTTOM:
		AddAction(DIK_NUMPAD2);
		break;
	case DIR_TOP:
		AddAction(DIK_NUMPAD8);
		break;
	case DIR_BOTTOM_LEFT:
		AddAction(DIK_NUMPAD1);
		break;
	case DIR_BOTTOM_RIGHT:
		AddAction(DIK_NUMPAD3);
		break;
	case DIR_TOP_LEFT:
		AddAction(DIK_NUMPAD7);
		break;
	case DIR_TOP_RIGHT:
		AddAction(DIK_NUMPAD9);
		break;
	default:
		break;
	}

	if (!_needRender || !player->NeedRender())
		return;

	if (_GunReloadInterval > 0)
		return;

	// already locked target, perform shoot
	if (_state->StateId() == STATE_WALK && _ActionQueue.size() > 0)
		AddAction(DIK_O);

	// idle (Sniper will look around)
	if (abs(player->x() - _x) > SNIPER_ACTIVE_RANGE_X
		&& abs(player->x() - _x) > SNIPER_ACTIVE_RANGE_Y)
	{
		if (_idle > 0)
		{
			if (_idle >= dt)
				_idle -= dt;
			else
				_idle = 0;
		}
		else
		{
			_idle = 120;
			if (_faceLeft)
				_lockDir = DIR_RIGHT;
			else
				_lockDir = DIR_LEFT;
		}
		return;
	}
	_idle = 0;

	// lock target
	float pcx, pcy, cx, cy;
	player->GetCenterPoint(pcx, pcy);
	GetCenterPoint(cx, cy);
	_lockDir = Detect_Dir(cx, cy, pcx, pcy);
	if (_lockDir == DIR_TOP || _lockDir == DIR_BOTTOM)
	{
		if (pcx < cx)
			_faceLeft = true;
		else
			_faceLeft = false;
	}
}

void Enemy_Sniper::GetCustomSize(int state, int& width, int& height)
{
	switch (state)
	{
	case STATE_IDLE:
		width = SNIPER_HIDE_WIDTH;
		height = SNIPER_HIDE_HEIGHT;
		break;
	case STATE_WALK:
		width = SNIPER_BASE_WIDTH;
		height = SNIPER_BASE_HEIGHT;
		break;
	case STATE_DIE:
		width = SNIPER_BASE_WIDTH;
		height = SNIPER_BASE_HEIGHT;
		break;
	default:
		break;
	}
}

void Enemy_Sniper::Shoot(int DIR)
{
	if (_weapon == NULL || _GunReloadInterval > 0)
		return;
	float x, y;
	GetCenterPoint(x, y);
	BULLETHELPER::getSpawnCor(x, y, CharID(), Sprite_ActID(), DIR);

	_GunReloadInterval = _weapon->FireRate();

	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	Game_Player* player = scene->p1();
	
	if (DIR == DIR_TOP || DIR == DIR_BOTTOM)
	{
		_weapon->Fire(x, y, DIR);
		return;
	}

	float tarX, tarY;
	player->GetCenterPoint(tarX, tarY);
	_weapon->Fire(x, y, tarX, tarY, B_SPAWN_MODE_TARGETPOS);
}