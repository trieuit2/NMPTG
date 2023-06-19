#include "Equip_EnemyGun_Bomber.h"
#include "Obj_EnemyBullet_Bomb.h"
#include "Scene_Battle.h"

void Equip_EnemyGun_Bomber::Fire(float& x, float& y, int DIR)
{
	unique_ptr<Obj_EnemyBullet_Bomb> bullet = unique_ptr<Obj_EnemyBullet_Bomb>(new Obj_EnemyBullet_Bomb(x, y, Z_INDEX_BULLET));
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	scene->add_object(move(bullet));
}