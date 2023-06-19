#include "State_Contra_Dive.h"
#include "Game_Character.h"
#include "Animations.h"
#include "Contra_GET_ANI.h"

void State_Contra_Dive::Render()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	CAnimations* animations = CAnimations::GetInstance();
	float x, y, ox, oy;
	obj->GetCenterPoint(x, y);
	obj->GetSpriteOffset(StateId(), ox, oy);
	x += ox;
	y += oy;
	_currentActID = ACT_DIVE;
	obj->_Render(Get_CharANI_ID(obj->CharID(), _currentActID),x,y);
}

void State_Contra_Dive::Update(DWORD dt)
{
	if (_nextState != -1)
		return;

	Game_Character* obj = (Game_Character*)_srcObj;

	if (!obj->IsGhost())
		obj->SetGhost(true);

	if (_diveTime > dt)
	{
		_diveTime = dt;
		return;
	}
	else if (_diveTime > 0)
		_diveTime = 0;

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
			_nextState = STATE_SWIM;
			return;
		}
	}
}