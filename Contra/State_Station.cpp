#include "State_Station.h"
#include "Game_Enemy.h"
#include "Contra_GET_ANI.h"

void State_Station::Render()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	CAnimations* animations = CAnimations::GetInstance();
	float x, y, ox, oy;
	obj->GetCenterPoint(x, y);
	obj->GetSpriteOffset(StateId(), ox, oy);
	x += ox;
	y += oy;
	switch (_DIR)
	{
	case DIR_TOP:
		{
			if (obj->IsFaceLeft())
				_currentActID = ACT_LOOK_UP_LEFT;
			else
				_currentActID = ACT_LOOK_UP_RIGHT;
			break;
		}
	case DIR_BOTTOM:
		{
			if (obj->IsFaceLeft())
				_currentActID = ACT_LOOK_DOWN_LEFT;
			else
				_currentActID = ACT_LOOK_DOWN_RIGHT;
			break;
		}
	case DIR_LEFT:
		{
			_currentActID = ACT_WALK_LEFT;
			break;
		}
	case DIR_RIGHT:
		{
			_currentActID = ACT_WALK_RIGHT;
			break;
		}
	case DIR_TOP_LEFT:
		{
			_currentActID = ACT_WALK_LEFT_LOOK_UP;
			break;
		}
	case DIR_TOP_RIGHT:
		{
			_currentActID = ACT_WALK_RIGHT_LOOK_UP;
			break;
		}
	case DIR_BOTTOM_LEFT:
		{
			_currentActID = ACT_WALK_LEFT_LOOK_DOWN;
			break;
		}
	case DIR_BOTTOM_RIGHT:
		{
			_currentActID = ACT_WALK_RIGHT_LOOK_DOWN;
			break;
		}
	default:
		{
			if (obj->IsFaceLeft())
				_currentActID = ACT_WALK_LEFT;
			else
				_currentActID = ACT_WALK_RIGHT;
		}
	}
	obj->_Render(Get_CharANI_ID(obj->CharID(), _currentActID), x, y);
}

void State_Station::Update(DWORD dt)
{
	if (_nextState != -1)
		return;

	Game_Character* obj = (Game_Character*)_srcObj;

	// do something
}

void State_Station::KeyPressed_Left()
{
	State_Contra_Base::KeyHold_Left();
	Game_Character* obj = (Game_Character*)_srcObj;
	obj->moveLeft();
}

void State_Station::KeyPressed_Right()
{
	State_Contra_Base::KeyHold_Right();
	Game_Character* obj = (Game_Character*)_srcObj;
	obj->moveRight();
}

void State_Station::KeyPressed_Jump()
{
	_nextState = STATE_IDLE;
}

void State_Station::KeyPressed_Shoot()
{
	Game_Character* obj = (Game_Character*)_srcObj;

	switch (_DIR)
	{
	case DIR_TOP:
		obj->Shoot(DIR_TOP);
		break;
	case DIR_BOTTOM:
		obj->Shoot(DIR_BOTTOM);
		break;
	case DIR_LEFT:
		obj->Shoot(DIR_LEFT);
		break;
	case DIR_RIGHT:
		obj->Shoot(DIR_RIGHT);
		break;
	case DIR_TOP_LEFT:
		obj->Shoot(DIR_TOP_LEFT);
		break;
	case DIR_TOP_RIGHT:
		obj->Shoot(DIR_TOP_RIGHT);
		break;
	case DIR_BOTTOM_LEFT:
		obj->Shoot(DIR_BOTTOM_LEFT);
		break;
	case DIR_BOTTOM_RIGHT:
		obj->Shoot(DIR_BOTTOM_RIGHT);
		break;
	}
}

void State_Station::KeyPressed_FaceUp()
{
	_DIR = DIR_TOP;
}

void State_Station::KeyPressed_FaceDown()
{
	_DIR = DIR_BOTTOM;
}

void State_Station::KeyPressed_FaceLeft()
{
	_DIR = DIR_LEFT;
}

void State_Station::KeyPressed_FaceRight()
{
	_DIR = DIR_RIGHT;
}

void State_Station::KeyPressed_FaceUpLeft()
{
	_DIR = DIR_TOP_LEFT;
}

void State_Station::KeyPressed_FaceUpRight()
{
	_DIR = DIR_TOP_RIGHT;
}

void State_Station::KeyPressed_FaceDownLeft()
{
	_DIR = DIR_BOTTOM_LEFT;
}

void State_Station::KeyPressed_FaceDownRight()
{
	_DIR = DIR_BOTTOM_RIGHT;
}