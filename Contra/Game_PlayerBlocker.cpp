#include "Game_PlayerBlocker.h"
#include "Game_Player.h"
#include "GameManager.h"

bool Game_PlayerBlocker::BlockingCondition(DWORD dt, PCOLLISIONEVENT e)
{
	if (dynamic_cast<Game_Player*>(e->src_obj))
	{
		return 1;
	}
	return 0;
}
