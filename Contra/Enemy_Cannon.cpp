#include "Enemy_Cannon.h"
#include "Scene_Battle.h"
#include "Contra_GET_ANI.h"
#include "State_Contra_Base.h"
#include "State_Turret_Active.h"
#include "State_Turret_Hide.h"

int Enemy_Cannon::CharID()
{
	return CANNON;
}

void Enemy_Cannon::Execute_DieAction()
{
	Game_StationEnemy::Execute_DieAction();
}

void Enemy_Cannon::Execute_BeforeDelete()
{
	if (_die)
	{
		CreateDieAnimation(ANI_EXPLOSION_CONSTRUCT);
	}
}

void Enemy_Cannon::UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	Game_Player* player = scene->p1();

	if (_ActionQueue.size() > 0)
		return;

	if (_needRender == false)
		return;

	// EMERGE MODE
	if (_state->StateId() == STATE_EMERGE)
	{
		return;
	}

	// HIDING MODE
	if (_state->StateId() == STATE_HIDE)
	{
		// in active range
		if (abs(player->x() - _x) <= TURRET_TRIGGER_RANGE_X
			&& abs(player->y() - _y) <= TURRET_TRIGGER_RANGE_Y)
		{
			AddAction(DIK_O);
			return;
		}
		return;
	}

	// ACTIVE MODE
	State_Turret_Active* state = (State_Turret_Active*)(_state.get());

	// out of active range
	if (abs(player->x() - _x) > CANNON_TRIGGER_RANGE_X
		|| abs(player->y() - _y) > CANNON_TRIGGER_RANGE_Y)
	{
		// Do nothing
		return;
	}

	if (_state->StateId() != STATE_ACTIVE)
	{
		return;
	}

	if (_rotate_CD > dt)
	{
		_rotate_CD -= dt;
	}
	else
	{
		_rotate_CD = TURRET_ROTATE_CD - (dt - _rotate_CD);
		// try moving clockwise
		bool rotateLeft = true;

		int shiftValue = _lockDir - state->CurrentAngle();

		if (shiftValue != 0)
		{
			// fix value if _lockDir is smaller than currentAngle (ex: 8h->2h)
			if (shiftValue < 0)
				shiftValue = 12 + shiftValue;

			// if value > 6 mean moving counterclockwise is faster
			if (shiftValue > 6)
				rotateLeft = false;

			if (rotateLeft)
				AddAction(DIK_LEFT);
			else
				AddAction(DIK_RIGHT);
		}
	}

	// already locked target, perform shoot
	if (_GunReloadInterval == 0 && state->CurrentAngle() == _lockDir)
		AddAction(DIK_O);

	// lock target
	float pcx, pcy, cx, cy;
	player->GetCenterPoint(pcx, pcy);
	GetCenterPoint(cx, cy);
	_lockDir = Detect_Dir12(cx, cy, pcx, pcy);

	if (_faceLeft)
	{
		// FaceLeft Cannon can only angle 9h->11h
		if (_lockDir > DIR_11_OCLOCK || _lockDir <= DIR_4_OCLOCK)
			_lockDir = DIR_11_OCLOCK;
		else if (_lockDir < DIR_9_OCLOCK)
			_lockDir = DIR_9_OCLOCK;
	}
	else
	{
		// FaceRight Cannon can only angle 1h->3h
		if (_lockDir >= DIR_9_OCLOCK)
			_lockDir = DIR_1_OCLOCK;
		else if (_lockDir > DIR_3_OCLOCK)
			_lockDir = DIR_3_OCLOCK;
	}
}

void Enemy_Cannon::GetCustomSize(int state, int& width, int& height)
{
	width = CANNON_BASE_WIDTH;
	height = CANNON_BASE_HEIGHT;
}

void Enemy_Cannon::Shoot(int DIR)
{
	if (_weapon == NULL || _GunReloadInterval > 0)
		return;
	float x, y;
	GetCenterPoint(x, y);
	BULLETHELPER::getSpawnCor(x, y, CharID(), Sprite_ActID(), DIR);

	_GunReloadInterval = _weapon->FireRate();

	_weapon->Fire(x, y, DIR);
	return;
}

void Enemy_Cannon::UpdateState()
{
	if (_state == NULL)
	{
		if (_faceLeft)
			_state.reset(new State_Turret_Hide(this, DIR_9_OCLOCK));
		else 
			_state.reset(new State_Turret_Hide(this, DIR_3_OCLOCK));
	}
	
	Game_StationEnemy::UpdateState();
}