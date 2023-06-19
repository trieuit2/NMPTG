#include "Equip_EnemyGun_Turret.h"
#include "Obj_EnemyBullet_N.h"
#include "Game_Character.h"
#include "ScreenManager.h"

void Equip_EnemyGun_Turret::Fire(float& x, float& y, int DIR)
{
	unique_ptr<Obj_EnemyBullet_N> bullet;
	float angle = 0;
	switch (DIR)
	{
	case DIR_1_OCLOCK:
		angle = 60.0f;
		break;
	case DIR_2_OCLOCK:
		angle = 30.0f;
		break;
	case DIR_3_OCLOCK:
		angle = 0.0f;
		break;
	case DIR_4_OCLOCK:
		angle = 330.0f;
		break;
	case DIR_5_OCLOCK:
		angle = 300.0f;
		break;
	case DIR_6_OCLOCK:
		angle = 270.0f;
		break;
	case DIR_7_OCLOCK:
		angle = 240.0f;
		break;
	case DIR_8_OCLOCK:
		angle = 210.0f;
		break;
	case DIR_9_OCLOCK:
		angle = 180.0f;
		break;
	case DIR_10_OCLOCK:
		angle = 150.0f;
		break;
	case DIR_11_OCLOCK:
		angle = 120.0f;
		break;
	case DIR_12_OCLOCK:
		angle = 90.0f;
		break;
	default:
		break;
	}
	bullet = unique_ptr<Obj_EnemyBullet_N>(new Obj_EnemyBullet_N(x, y, Z_INDEX_BULLET, angle));
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());

	scene->add_object(move(bullet));
}