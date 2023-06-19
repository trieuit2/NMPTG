#include "Game_SweeperBlock.h"
#include "Game_Enemy.h"
#include "Obj_FlyingUpgradeBox.h"

bool Game_SweeperBlock::BlockingCondition(DWORD dt, PCOLLISIONEVENT e)
{
	if (dynamic_cast<Game_Enemy*>(e->src_obj))
	{
		if (!dynamic_cast<Obj_FlyingUpgradeBox*>(e->src_obj) && !e->src_obj->NeedRender())
			e->src_obj->DeleteThis();
		return false;
	}
	return true;
}