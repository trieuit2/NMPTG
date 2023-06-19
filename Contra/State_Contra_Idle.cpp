#include "State_Contra_Idle.h"
#include "Game_Player.h"
#include "Animations.h"
#include "Contra_GET_ANI.h"

State_Contra_Idle::State_Contra_Idle(Game_ObjectBase* obj, int forceFace) : State_Contra_Base(obj)
{
	if (forceFace > 0)
		((Game_Character*)_srcObj)->SetFaceLeft(false);
	else if (forceFace < 0)
		((Game_Character*)_srcObj)->SetFaceLeft(true);
}

void State_Contra_Idle::Render()
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
			_currentActID = ACT_LOOK_UP_LEFT;
		else
			_currentActID = ACT_IDLE_LEFT;
	}
	else
	{
		if (HoldKeyUp)
			_currentActID = ACT_LOOK_UP_RIGHT;
		else
			_currentActID = ACT_IDLE_RIGHT;
	}
	obj->_Render(Get_CharANI_ID(obj->CharID(), _currentActID), x, y);
}

void State_Contra_Idle::Update(DWORD dt)
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
	{
		obj->SetLockFace(false);
	}


	if (HoldKeyDown)
	{
		_nextState = STATE_LIE;
		return;
	}

	if (!obj->IsOnGround())
	{
		_nextState = STATE_FALL;
		return;
	}
}

void State_Contra_Idle::KeyHold_Left()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	obj->moveLeft();
	if (_nextState == -1)
		_nextState = STATE_WALK;
}

void State_Contra_Idle::KeyHold_Right()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	obj->moveRight();
	if (_nextState == -1)
		_nextState = STATE_WALK;
}

//void State_Contra_Idle::KeyHold_Down()
//{
//	HoldKeyDown = true;
//}
//
//void State_Contra_Idle::KeyReleased_Down()
//{
//	HoldKeyDown = false;
//}

void State_Contra_Idle::KeyPressed_Jump()
{
	//
	DebugOut(L"[INFO] IDLE Jump key is pressed\n");
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

void State_Contra_Idle::KeyPressed_Shoot()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	if (!obj->IsFullAutomaticGun())
	{
		if (HoldKeyUp)
		{
			obj->Shoot(DIR_TOP);
			return;
		}

		if (obj->IsFaceLeft())
			obj->Shoot(DIR_LEFT);
		else
			obj->Shoot(DIR_RIGHT);
	}
}

void State_Contra_Idle::KeyHold_Shoot()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	if (obj->IsFullAutomaticGun())
	{
		if (HoldKeyUp)
		{
			obj->Shoot(DIR_TOP);
			return;
		}
		if (obj->IsFaceLeft())
			obj->Shoot(DIR_LEFT);
		else
			obj->Shoot(DIR_RIGHT);
	}
}