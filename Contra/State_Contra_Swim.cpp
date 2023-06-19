#include "State_Contra_Swim.h"
#include "Game_Character.h"
#include "Contra_GET_ANI.h"

void State_Contra_Swim::Render()
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
		if (HoldKeyUp && HoldKeyLeft)
			_currentActID = ACT_SWIM_LEFT_LOOK_UP;
		else if (HoldKeyUp)
			_currentActID = ACT_SWIM_LOOK_UP_STAND_LEFT;
		else if (HoldKeyShoot)
			_currentActID = ACT_SWIM_SHOOT_LEFT;
		else
			_currentActID = ACT_SWIM_LEFT;
	}
	else
	{
		if (HoldKeyUp && HoldKeyRight)
			_currentActID = ACT_SWIM_RIGHT_LOOK_UP;
		else if (HoldKeyUp)
			_currentActID = ACT_SWIM_LOOK_UP_STAND_RIGHT;
		else if (HoldKeyShoot)
			_currentActID = ACT_SWIM_SHOOT_RIGHT;
		else
			_currentActID = ACT_SWIM_RIGHT;
	}
	obj->_Render(Get_CharANI_ID(obj->CharID(), _currentActID), x, y);
}

void State_Contra_Swim::Update(DWORD dt)
{
	if (_nextState != -1)
		return;

	Game_Character* obj = (Game_Character*)_srcObj;

	if (obj->IsGhost())
		obj->SetGhost(false);

	int width, height;
	obj->GetCustomSize(StateId(), width, height);
	if (obj->height() != height)
	{
		obj->SetHeight(height, 2);
	}
	
	if (obj->LockFace())
		obj->SetLockFace(false);

	if (!obj->IsSwimming())
	{
		_nextState = STATE_IDLE;
		return;
	}

	if (HoldKeyDown)
	{
		_nextState = STATE_DIVE;
	}
}

void State_Contra_Swim::KeyHold_Left()
{
	State_Contra_Base::KeyHold_Left();
	Game_Character* obj = (Game_Character*)_srcObj;
	obj->moveLeft();
}

void State_Contra_Swim::KeyHold_Right()
{
	State_Contra_Base::KeyHold_Right();
	Game_Character* obj = (Game_Character*)_srcObj;
	obj->moveRight();
}

void State_Contra_Swim::KeyPressed_Shoot()
{
	State_Contra_Base::KeyHold_Shoot();
	Game_Character* obj = (Game_Character*)_srcObj;
	if (!obj->IsFullAutomaticGun())
	{
		if (HoldKeyDown)
		{
			// do nothing
			return;
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
			if (obj->IsFaceLeft())
				obj->Shoot(DIR_LEFT);
			else
				obj->Shoot(DIR_RIGHT);
		}
	}
}

void State_Contra_Swim::KeyHold_Shoot()
{
	State_Contra_Base::KeyHold_Shoot();
	Game_Character* obj = (Game_Character*)_srcObj;
	if (obj->IsFullAutomaticGun())
	{
		if (HoldKeyDown)
		{
			// do nothing
			return;
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
			if (obj->IsFaceLeft())
				obj->Shoot(DIR_LEFT);
			else
				obj->Shoot(DIR_RIGHT);
		}
	}
}
