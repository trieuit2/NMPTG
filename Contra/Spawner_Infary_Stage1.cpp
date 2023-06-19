#include "Spawner_Infary_Stage1.h"
#include "Enemy_Infary.h"
#include "Scene_Battle.h"

void Spawner_Infary_Stage1::Update(DWORD dt)
{
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	
	if (_needRender || scene->p1()->x() > _x)
	{
		return;
	}
	
	if (ProcessTimer(dt))
	{
		unique_ptr <Enemy_Infary> infary(new Enemy_Infary(_x, _y, Z_INDEX_ENEMY));
		scene->add_object(move(infary));
	}
}