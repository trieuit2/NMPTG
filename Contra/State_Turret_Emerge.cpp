#include "State_Turret_Emerge.h"
#include "Game_Character.h"
#include "Contra_GET_ANI.h"

void State_Turret_Emerge::Render()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	CAnimations* animations = CAnimations::GetInstance();
	float x, y, ox, oy;
	obj->GetCenterPoint(x, y);
	obj->GetSpriteOffset(StateId(), ox, oy);
	x += ox;
	y += oy;
	if (obj->IsFaceLeft())
		_currentActID = ACT_EMERGE_LEFT;
	else
		_currentActID = ACT_EMERGE_RIGHT;
	obj->_Render(Get_CharANI_ID(obj->CharID(), _currentActID), x, y);

}

void State_Turret_Emerge::Update(DWORD dt)
{
	if (_nextState != -1)
		return;
	Game_Character* obj = (Game_Character*)_srcObj;

	int curAni;
	if (obj->IsFaceLeft())
		curAni=Get_CharANI_ID(obj->CharID(), ACT_EMERGE_LEFT);
	else
		curAni = Get_CharANI_ID(obj->CharID(), ACT_EMERGE_RIGHT);
	if (obj->atFinalFrame(curAni))
	{
		if (waitForChange > dt)
		{
			waitForChange -= dt;
		}
		else
		{
			_nextState = STATE_ACTIVE;
		}
	}
}