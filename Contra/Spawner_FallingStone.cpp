#include "Spawner_FallingStone.h"
#include "Obj_FallingStone.h"
#include "Scene_Battle.h"

void Spawner_FallingStone::Update(DWORD dt)
{
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());

	if (!_needRender || !scene->p1()->NeedRender())
	{
		return;
	}

	if (ProcessTimer(dt))
	{
		unique_ptr <Obj_FallingStone> obj(new Obj_FallingStone(_x, _y, Z_INDEX_ENEMY));
		scene->add_object(move(obj));
	}
}