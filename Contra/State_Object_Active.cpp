#include "State_Object_Active.h"
#include "Game_Character.h"

void State_Object_Active::Render()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	CAnimations* animations = CAnimations::GetInstance();
	float x, y, ox, oy;
	obj->GetCenterPoint(x, y);
	obj->GetSpriteOffset(StateId(), ox, oy);
	x += ox;
	y += oy;

	if (obj->IsFaceLeft())
		_currentActID = ACT_ACTIVE_LEFT;
	else
		_currentActID = ACT_ACTIVE_RIGHT;
	obj->_Render(Get_CharANI_ID(obj->CharID(), _currentActID), x, y);
}

void State_Object_Active::KeyPressed_Hide()
{
	if (_nextState == -1)
		_nextState = STATE_OBJ_HIDE;
}