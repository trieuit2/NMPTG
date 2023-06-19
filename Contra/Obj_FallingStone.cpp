#include "Obj_FallingStone.h"
#include "Game_Platform.h"
#include "Game_Blocker.h"

int Obj_FallingStone::CharID()
{
	return FALLING_STONE;
}

void Obj_FallingStone::UpdateState()
{
	Game_SpecialObject::UpdateState();
}

void Obj_FallingStone::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	if (_ForceY == 0 && _finishEmerge)
		_external_vy += STONE_FALLING_SPEED;
	Game_SpecialObject::Update(dt, coObjects);
}

void Obj_FallingStone::OnCollisionWith(PCOLLISIONEVENT e)
{
	Game_SpecialObject::OnCollisionWith(e);
	if (dynamic_cast<Game_Platform*>(e->obj)
		|| dynamic_cast<Game_Blocker*>(e->obj))
	{
		_touchList.push_back(e->obj->id());
		_ForceY += STONE_BOUNCE_HEIGHT;
		return;
	}
}

bool Obj_FallingStone::CollideBlockerCondition(DWORD dt, PCOLLISIONEVENT e)
{
	for (int i = 0; i < _touchList.size(); i++)
	{
		if (_touchList[i] == e->obj->id())
		{
			return false;
		}
	}
	return true;
}

void Obj_FallingStone::UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	if (_finishEmerge)
		return;
	//-------------------------------------------------
	// shake effect
	if (_EmergeTick > dt)
	{
		_EmergeTick -= dt;
		// shake
		if (_ForceX == 0)
		{
			_faceLeft = !_faceLeft;
			if (_faceLeft)
				_ForceX = -STONE_SHAKE_RANGE * 2;
			else
				_ForceX = STONE_SHAKE_RANGE * 2;
		}

	}
	else
	{
		_ForceX = 0;
		_finishEmerge = true;
		_EmergeTick = 0;
		SetPosition(_baseX, _y);
		_BodyDamage = true;
		AddAction(DIK_O);
	}
}