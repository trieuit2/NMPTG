#include "Obj_StationUpgradeBox.h"
#include "Obj_Upgrade.h"
#include "Scene_Battle.h"
#include "State_Object_Hide.h"

int Obj_StationUpgradeBox::CharID()
{
	return UP_BOX_STATION;
}

void Obj_StationUpgradeBox::Update(DWORD dt, vector<Game_ObjectBase*>* coObjects)
{
	if (_state != NULL &&
		(_state->StateId() == STATE_OBJ_HIDE || _state->StateId() == STATE_OBJ_EMERGE))
	{
		_ghost = true;
	}
	else if (_state == NULL)
	{
		_ghost = true;
	}
	else
	{
		_ghost = false;
	}
	Game_SpecialObject::Update(dt, coObjects);
}

void Obj_StationUpgradeBox::Execute_BeforeDelete()
{
	if (_die)
	{
		CreateDieAnimation(ANI_EXPLOSION_CONSTRUCT);
		float cx, cy;
		GetCenterPoint(cx, cy);
		UPGRADE::spawnUpgradeIcon(_type, cx, cy, _faceLeft);
	}
}

void Obj_StationUpgradeBox::UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	if (_ActionQueue.size() > 0)
		return;

	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	Game_Player* player = scene->p1();

	if (!_needRender || !player->NeedRender())
		return;

	if (_state->StateId() == STATE_OBJ_EMERGE)
	{
		return;
	}

	// Wait to change state
	if (_waitToChangeState > dt)
	{
		_waitToChangeState -= dt;
	}
	else
	{
		switch (_state->StateId())
		{
		case STATE_OBJ_HIDE:
			// emerge
			AddAction(DIK_O);
			_waitToChangeState = STATION_UP_SHOW_INTERVAL;
			break;
		case STATE_OBJ_ACTIVE:
			AddAction(DIK_P);
			_waitToChangeState = STATION_UP_HIDE_INTERVAL;
			break;
		default:
			break;
		}
	}
}

void Obj_StationUpgradeBox::UpdateState()
{
	// begin with hide state
	if (_state == NULL)
		_state.reset(new State_Object_Hide(this));
	Game_SpecialObject::UpdateState();
}