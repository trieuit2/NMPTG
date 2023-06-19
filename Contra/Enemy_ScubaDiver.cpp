#include "Enemy_ScubaDiver.h"
#include "Scene_Battle.h"
#include "Contra_GET_ANI.h"
#include "State_Station_Hide.h"
#include "State_CONST.h"

int Enemy_ScubaDiver::CharID()
{
	return SCUBA_DIVER;
}

void Enemy_ScubaDiver::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	Game_StationEnemy::Update(dt, coObjects);
	if (_state->StateId() == STATE_IDLE)
		_ghost = true;
	else if (_state->StateId() != STATE_DIE)
		_ghost = false;
}

void Enemy_ScubaDiver::Execute_DieAction()
{
	Game_StationEnemy::Execute_DieAction();
	jump();
}

void Enemy_ScubaDiver::Execute_BeforeDelete()
{
	if (_die)
	{
		CreateDieAnimation(ANI_EXPLOSION_ARMY);
	}
}

void Enemy_ScubaDiver::UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects)
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
	else if (player->y() < _y + SCUBADIVER_ATTACK_RANGE)
	{
		// wait for player moving to attack range
		_waitToChangeState = 1;
	}
	else if (_state->StateId() != STATE_WALK)
	{
		AddAction(DIK_O);
		AddAction(DIK_PAUSE, 10);
	}
	else
	{
		// attack
		_waitToChangeState = SCUBADIVER_HIDING_INTERVAL - (dt - _waitToChangeState);
		AddAction(DIK_NUMPAD6);
		AddAction(DIK_PAUSE, 10);
		AddAction(DIK_O);
		AddAction(DIK_PAUSE, 10);
		AddAction(DIK_P);
	}
}

void Enemy_ScubaDiver::GetCustomSize(int state, int& width, int& height)
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

void Enemy_ScubaDiver::Shoot(int DIR)
{
	if (_weapon == NULL || _GunReloadInterval > 0)
		return;
	float x, y;
	GetCenterPoint(x, y);
	BULLETHELPER::getSpawnCor(x, y, CharID(), Sprite_ActID(), DIR);

	_GunReloadInterval = _weapon->FireRate();

	_weapon->Fire(x, y, DIR_TOP);
}

void Enemy_ScubaDiver::UpdateState()
{
	if (_state == NULL)
		_state.reset(new State_Station_Hide(this));
	Game_StationEnemy::UpdateState();
}