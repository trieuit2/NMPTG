#include "Equip_Gun_M.h"
#include "ScreenManager.h"
#include "Game_Character.h"
#include "Obj_Bullet_M.h"

void Equip_Gun_M::Fire(float& x, float& y, float& vx, float& vy, bool type)
{
	DebugOut(L"[INFO] Gun_N only has DIR MODE.\n");

}

void Equip_Gun_M::Fire(float& x, float& y, int DIR)
{
	unique_ptr<Obj_Bullet_M> bullet;
	switch (DIR)
	{
	case DIR_TOP:
		bullet = unique_ptr<Obj_Bullet_M>(new Obj_Bullet_M(x, y, Z_INDEX_BULLET, 0, 1));
		break;
	case DIR_BOTTOM:
		bullet = unique_ptr<Obj_Bullet_M>(new Obj_Bullet_M(x, y, Z_INDEX_BULLET, 0, -1));
		break;
	case DIR_LEFT:
		bullet = unique_ptr<Obj_Bullet_M>(new Obj_Bullet_M(x, y, Z_INDEX_BULLET, -1, 0));
		break;
	case DIR_RIGHT:
		bullet = unique_ptr<Obj_Bullet_M>(new Obj_Bullet_M(x, y, Z_INDEX_BULLET, 1, 0));
		break;
	case DIR_TOP_LEFT:
		bullet = unique_ptr<Obj_Bullet_M>(new Obj_Bullet_M(x, y, Z_INDEX_BULLET, -1, 1));
		break;
	case DIR_TOP_RIGHT:
		bullet = unique_ptr<Obj_Bullet_M>(new Obj_Bullet_M(x, y, Z_INDEX_BULLET, 1, 1));
		break;
	case DIR_BOTTOM_LEFT:
		bullet = unique_ptr<Obj_Bullet_M>(new Obj_Bullet_M(x, y, Z_INDEX_BULLET, -1, -1));
		break;
	case DIR_BOTTOM_RIGHT:
		bullet = unique_ptr<Obj_Bullet_M>(new Obj_Bullet_M(x, y, Z_INDEX_BULLET, 1, -1));
		break;
	default:
		break;
	}

	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());

	scene->add_object(move(bullet));
}