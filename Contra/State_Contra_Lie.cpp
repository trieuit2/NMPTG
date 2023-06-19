#include "State_Contra_Lie.h"
#include "Game_Character.h"
#include "Animations.h"
#include "Contra_GET_ANI.h"

void State_Contra_Lie::Render()
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
		_currentActID = ACT_LYING_LEFT;
	}
	else
	{
		_currentActID = ACT_LYING_RIGHT;
	}
	obj->_Render(Get_CharANI_ID(obj->CharID(), _currentActID), x, y);
}

void State_Contra_Lie::Update(DWORD dt)
{
	if (_nextState != -1)
		return;
	Game_Character* obj = (Game_Character*)_srcObj;

	int width, height;
	obj->GetCustomSize(StateId(), width, height);
	if (obj->width() != width)
	{
		obj->SetWidth(width, 1);
	}
	if (obj->height() != height)
	{
		obj->SetHeight(height, 2);
	}

	if (obj->LockFace())
		obj->SetLockFace(false);

	if (!HoldKeyDown)
	{
		if (_nextState == -1)
		{
			_nextState = STATE_IDLE;
			return;
		}
	}

	if (_nextState == -1 && !obj->IsOnGround())
	{
		_nextState = STATE_FALL;
	}
}

void State_Contra_Lie::KeyHold_Left()
{
	State_Contra_Base::KeyHold_Left();
	Game_Character* obj = (Game_Character*)_srcObj;
	obj->SetFaceLeft(true);
}

void State_Contra_Lie::KeyHold_Right()
{
	State_Contra_Base::KeyHold_Right();
	Game_Character* obj = (Game_Character*)_srcObj;
	obj->SetFaceLeft(false);
}

void State_Contra_Lie::KeyPressed_Jump()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	obj->jumpDown();
}

void State_Contra_Lie::KeyPressed_Shoot()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	if (!obj->IsFullAutomaticGun())
	{
		if (obj->IsFaceLeft())
			obj->Shoot(DIR_LEFT);
		else
			obj->Shoot(DIR_RIGHT);
	}
}

void State_Contra_Lie::KeyHold_Shoot()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	if (obj->IsFullAutomaticGun())
	{
		if (obj->IsFaceLeft())
			obj->Shoot(DIR_LEFT);
		else
			obj->Shoot(DIR_RIGHT);
	}
}