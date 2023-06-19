#include "State_Contra_Die.h"
#include "Game_Character.h"
#include "Contra_GET_ANI.h"
void State_Contra_Die::Render()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	CAnimations* animations = CAnimations::GetInstance();
	float x, y, ox, oy;
	obj->GetCenterPoint(x, y);
	obj->GetSpriteOffset(StateId(), ox, oy);
	x += ox;
	y += oy;
	if (obj->IsFaceLeft())
	{
		if (obj->IsAffectedByGravity() && !_isOnGround)
			_currentActID = ACT_DIE_JUMPING_LEFT;
		else 
			_currentActID = ACT_DIE_LEFT;
	}
	else
	{
		if (obj->IsAffectedByGravity() && !_isOnGround)
			_currentActID = ACT_DIE_JUMPING_RIGHT;
		else
			_currentActID = ACT_DIE_RIGHT;
	}
	obj->_Render(Get_CharANI_ID(obj->CharID(), _currentActID), x, y);
}

void State_Contra_Die::Update(DWORD dt)
{
	Game_Character* obj = (Game_Character*)_srcObj;
	_isOnGround = obj->IsOnGround();

	if (_trigger)
	{
		obj->Execute_DieAction();
		int width, height;
		obj->GetCustomSize(StateId(), width, height);
		obj->SetHeight(height, 2);
		_trigger = false;
	}

	if (_delayDelete >= INFINITE_DELAY)
		return;
	else if (_delayDelete >= dt)
	{
		_delayDelete -= dt;
		return;
	}
	else if (_delayDelete > 0)
	{
		_delayDelete = 0;
		return;
	}

	obj->DeleteThis();
}