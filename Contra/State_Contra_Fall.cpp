#include "State_Contra_Fall.h"
#include "Game_Character.h"
#include "Contra_GET_ANI.h"

void State_Contra_Fall::Render()
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
		_currentActID = ACT_FALL_LEFT;
	}
	else
	{
		_currentActID = ACT_FALL_RIGHT;
	}
	obj->_Render(Get_CharANI_ID(obj->CharID(), _currentActID), x, y);
}

void State_Contra_Fall::Update(DWORD dt)
{
	if (_nextState != -1)
		return;

	Game_Character* obj = (Game_Character*)_srcObj;

	int width, height;
	obj->GetCustomSize(StateId(), width, height);
	if (obj->height() != height)
	{
		obj->SetHeight(height, 0);
	}

	if (obj->IsSwimming() && _nextState == -1)
	{
		_nextState = STATE_SWIM;
		return;
	}

	if (obj->IsOnGround() && _nextState == -1)
	{
		_nextState = STATE_IDLE;
		return;
	}
}

void State_Contra_Fall::KeyHold_Left()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	obj->moveLeft();
}

void State_Contra_Fall::KeyHold_Right()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	obj->moveRight();
}
