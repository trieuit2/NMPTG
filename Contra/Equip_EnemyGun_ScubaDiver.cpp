#include "Equip_EnemyGun_ScubaDiver.h"
#include "Obj_EnemyBullet_SBomb.h"
#include "Scene_Battle.h"

void Equip_EnemyGun_ScubaDiver::Fire(float& x, float& y, int DIR)
{
	unique_ptr<Obj_EnemyBullet_SBomb> bullet = unique_ptr<Obj_EnemyBullet_SBomb>(new Obj_EnemyBullet_SBomb(x, y, Z_INDEX_BULLET));
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	scene->add_object(move(bullet));
}