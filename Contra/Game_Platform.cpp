#include "Game_Platform.h"
#include "Game_MovableObject.h"
#include "Game_Character.h"

bool Game_Platform::BlockingCondition(DWORD dt, PCOLLISIONEVENT e)
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