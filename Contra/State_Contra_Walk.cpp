#include "State_Contra_Walk.h"
#include "Game_Character.h"
#include "Animations.h"
#include "Contra_GET_ANI.h"

void State_Contra_Walk::Render()
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
		if (HoldKeyUp)
			_currentActID = ACT_WALK_LEFT_LOOK_UP;
		else if (HoldKeyDown)
			_currentActID = ACT_WALK_LEFT_LOOK_DOWN;
		else if (HoldKeyShoot)
			_currentActID = ACT_SHOOT_WALK_LEFT;
		else
			_currentActID = ACT_WALK_LEFT;
	}
	else
	{
		if (HoldKeyUp)
			_currentActID = ACT_WALK_RIGHT_LOOK_UP;
		else if (HoldKeyDown)
			_currentActID = ACT_WALK_RIGHT_LOOK_DOWN;
		else if (HoldKeyShoot)
			_currentActID = ACT_SHOOT_WALK_RIGHT;
		else
			_currentActID = ACT_WALK_RIGHT;
	}
	obj->_Render(Get_CharANI_ID(obj->CharID(), _currentActID), x, y);
}

void State_Contra_Walk::Update(DWORD dt)
{
	if (_nextState != -1)
		return;
	Game_Character* obj = (Game_Character*)_srcObj;

	int width, height;
	obj->GetCustomSize(StateId(), width, height);
	if (obj->height() != height)
	{
		obj->SetHeight(height, 2);
	}

	if (obj->LockFace())
	{
		obj->SetLockFace(false);
		if (HoldKeyLeft)
			obj->SetFaceLeft(true);
		else if (HoldKeyRight)
			obj->SetFaceLeft(false);
	}


	if (!HoldKeyLeft && !HoldKeyRight)
	{
		if (_nextState == -1)
		{
			_nextState = STATE_IDLE;
		}
	}

	if (_nextState != STATE_JUMP && !obj->IsOnGround())
	{
		_nextState = STATE_FALL;
	}
}

void State_Contra_Walk::KeyHold_Left()
{
	State_Contra_Base::KeyHold_Left();
	Game_Character* obj = (Game_Character*)_srcObj;
	obj->moveLeft();
}

void State_Contra_Walk::KeyHold_Right()
{
	State_Contra_Base::KeyHold_Right();
	Game_Character* obj = (Game_Character*)_srcObj;
	obj->moveRight();
}

int press = 0;

void State_Contra_Walk ::KeyPressed_Jump()
{
	press++;
	//
	DebugOut(L"[INFO] WALK Jump key is pressed %d\n", press);
	//
	Game_Character* obj = (Game_Character*)_srcObj;
	
	if (obj->IsJumping())
		return;

	if (_nextState == -1)
	{
		obj->jump();
		obj->SetLockFace(true);
		_nextState = STATE_JUMP;
	}
}

void State_Contra_Walk::KeyPressed_Shoot()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	if (!obj->IsFullAutomaticGun())
	{
		if (HoldKeyDown)
		{
			if (obj->IsFaceLeft())
				obj->Shoot(DIR_BOTTOM_LEFT);
			else
				obj->Shoot(DIR_BOTTOM_RIGHT);
		}
		else if (HoldKeyUp)
		{
			if (obj->IsFaceLeft())
				obj->Shoot(DIR_TOP_LEFT);
			else
				obj->Shoot(DIR_TOP_RIGHT);
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

void State_Contra_Walk::KeyHold_Shoot()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	if (obj->IsFullAutomaticGun())
	{
		if (HoldKeyDown)
		{
			if (obj->IsFaceLeft())
				obj->Shoot(DIR_BOTTOM_LEFT);
			else
				obj->Shoot(DIR_BOTTOM_RIGHT);
		}
		else if (HoldKeyUp)
		{
			if (obj->IsFaceLeft())
				obj->Shoot(DIR_TOP_LEFT);
			else
				obj->Shoot(DIR_TOP_RIGHT);
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