#include "State_Station_Hide.h"
#include "Game_Enemy.h"
#include "Contra_GET_ANI.h"

void State_Station_Hide::Render()
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
		_currentActID = ACT_IDLE_LEFT;
	}
	else
	{
		_currentActID = ACT_IDLE_RIGHT;
	}
	obj->_Render(Get_CharANI_ID(obj->CharID(), _currentActID), x, y);
}

void State_Station_Hide::Update(DWORD dt)
{
	if (_nextState != -1)
		return;

	Game_Character* obj = (Game_Character*)_srcObj;

	// do something
}

void State_Station_Hide::KeyPressed_Left()
{
	State_Contra_Base::KeyHold_Left();
	Game_Character* obj = (Game_Character*)_srcObj;
	obj->moveLeft();
}

void State_Station_Hide::KeyPressed_Right()
{
	State_Contra_Base::KeyHold_Right();
	Game_Character* obj = (Game_Character*)_srcObj;
	obj->moveRight();
}

void State_Station_Hide::KeyPressed_Shoot()
{
	_nextState = STATE_WALK;
}