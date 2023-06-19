#include "State_Contra_Jump.h"
#include "Game_Character.h"
#include "Contra_GET_ANI.h"

void State_Contra_Jump::Render()
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
		_currentActID = ACT_JUMP_LEFT;
	}
	else
	{
		_currentActID = ACT_JUMP_RIGHT;
	}
	obj->_Render(Get_CharANI_ID(obj->CharID(), _currentActID), x, y);
}

void State_Contra_Jump::Update(DWORD dt)
{
	if (_nextState != -1)
		return;

	Game_Character* obj = (Game_Character*)_srcObj;
	int width, height;
	obj->GetCustomSize(StateId(), width, height);
	if (obj->height() != height)
	{
		obj->SetHeight(height, 1);
	}

	if (obj->IsJumping())
		return;

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

void State_Contra_Jump::KeyHold_Left()
{
	State_Contra_Base::KeyHold_Left();
	Game_Character* obj = (Game_Character*)_srcObj;
	obj->moveLeft();
	_saveLastFace = -1;
}

void State_Contra_Jump::KeyHold_Right()
{
	State_Contra_Base::KeyHold_Right();
	Game_Character* obj = (Game_Character*)_srcObj;
	obj->moveRight();
	_saveLastFace = 1;
}

void State_Contra_Jump::KeyPressed_Shoot()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	if (!obj->IsFullAutomaticGun())
	{
		if (HoldKeyDown)
		{
			if (HoldKeyLeft)
				obj->Shoot(DIR_BOTTOM_LEFT);
			else if (HoldKeyRight)
				obj->Shoot(DIR_BOTTOM_RIGHT);
			else
				obj->Shoot(DIR_BOTTOM);
		}
		else if (HoldKeyUp)
		{
			if (HoldKeyLeft)
				obj->Shoot(DIR_TOP_LEFT);
			else if (HoldKeyRight)
				obj->Shoot(DIR_TOP_RIGHT);
			else
				obj->Shoot(DIR_TOP);
		}
		else
		{
			if (HoldKeyLeft)
				obj->Shoot(DIR_LEFT);
			else if (HoldKeyRight)
				obj->Shoot(DIR_RIGHT);
			else if (obj->IsFaceLeft())
				obj->Shoot(DIR_LEFT);
			else
				obj->Shoot(DIR_RIGHT);
		}
	}
}

void State_Contra_Jump::KeyHold_Shoot()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	if (obj->IsFullAutomaticGun())
	{
		if (HoldKeyDown)
		{
			if (HoldKeyLeft)
				obj->Shoot(DIR_BOTTOM_LEFT);
			else if (HoldKeyRight)
				obj->Shoot(DIR_BOTTOM_RIGHT);
			else
				obj->Shoot(DIR_BOTTOM);
		}
		else if (HoldKeyUp)
		{
			if (HoldKeyLeft)
				obj->Shoot(DIR_TOP_LEFT);
			else if (HoldKeyRight)
				obj->Shoot(DIR_TOP_RIGHT);
			else
				obj->Shoot(DIR_TOP);
		}
		else
		{
			if (HoldKeyLeft)
				obj->Shoot(DIR_LEFT);
			else if (HoldKeyRight)
				obj->Shoot(DIR_RIGHT);
			else if (obj->IsFaceLeft())
				obj->Shoot(DIR_LEFT);
			else
				obj->Shoot(DIR_RIGHT);
		}
	}
}