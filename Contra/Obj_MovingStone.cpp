#include "Obj_MovingStone.h"
#include "Game_Character.h"

void Obj_MovingStone::Update(DWORD dt)
{
	if (_moveToLeft)
	{
		if (_x > _maxRangeL)
			moveLeft();
		else
			_moveToLeft = false;
	}
	else
	{
		if (_x < _maxRangeR)
			moveRight();
		else
			_moveToLeft = true;
	}

	Game_MovableObject::Update(dt);

	_x += _vx * dt;
	_y += _vy * dt;
}

bool Obj_MovingStone::BlockingCondition(DWORD dt, PCOLLISIONEVENT e)
{
	if (dynamic_cast<Game_MovableObject*>(e->src_obj))
	{

		Game_MovableObject* SrcObj = (Game_MovableObject*)e->src_obj;
		if (e->ny > 0 && SrcObj->footerY() >= _y)
		{
			if (dynamic_cast<Game_Character*>(SrcObj))
			{
				Game_Character* Char = (Game_Character*)SrcObj;
				if (!Char->IsJumpDown())
					return 1;
				else
				{
					Char->SetJumpDown(0);
					return 0;
				}
			}

			return 1;
		}

	}
	return 0;
}