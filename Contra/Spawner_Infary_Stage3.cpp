#include "Spawner_Infary_Stage3.h"
#include "Enemy_Infary.h"
#include "Scene_Battle.h"

void Spawner_Infary_Stage3::Update(DWORD dt)
{
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	Game_Screen* screen = ScreenManager::GetInstance()->Screen();
	float sx = _x;
	float sy = _y;
	screen->Convert_WorldPos_to_ScreenPos(sx, sy);
	if (_needRender || sy > screen->height() || sy < 0)
	{
		return;
	}

	if (ProcessTimer(dt))
	{
		unique_ptr <Enemy_Infary> infary(new Enemy_Infary(_x, _y, Z_INDEX_ENEMY, _spawnToLeft));
		scene->add_object(move(infary));
	}
}