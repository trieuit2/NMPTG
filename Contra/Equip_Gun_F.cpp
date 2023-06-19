#include "Equip_Gun_F.h"
#include "ScreenManager.h"
#include "Game_Character.h"

void Equip_Gun_F::Fire(float& x, float& y, float& vx, float& vy, bool type)
{
	DebugOut(L"[INFO] Gun_N only has DIR MODE.\n");

}

void Equip_Gun_F::Fire(float &x, float &y, int DIR)
{
	float vx, vy;
	bool dir = BULLET_F_DIR_CLOCKWISE;
	switch (DIR)
	{
	case DIR_TOP:
		vx = 0.0f;
		vy = 1.0f;
		break;
	case DIR_BOTTOM:
		vx = 0.0f;
		vy = -1.0f;
		break;
	case DIR_LEFT:
		vx = -1.0f;
		vy = 0.0f;
		dir = BULLET_F_DIR_COUNTER_CLOCKWISE;
		break;
	case DIR_RIGHT:
		vx = 1.0f;
		vy = 0.0f;
		break;
	case DIR_TOP_LEFT:
		vx = -1.0f;
		vy = 1.0f;
		dir = BULLET_F_DIR_COUNTER_CLOCKWISE;
		break;
	case DIR_TOP_RIGHT:
		vx = 1.0f;
		vy = 1.0f;
		break;
	case DIR_BOTTOM_LEFT:
		vx = -1.0f;
		vy = -1.0f;
		dir = BULLET_F_DIR_COUNTER_CLOCKWISE;
		break;
	case DIR_BOTTOM_RIGHT:
		vx = 1.0f;
		vy = -1.0f;
		break;
	default:
		break;
	}
	unique_ptr<Obj_Bullet_F> bullet(new Obj_Bullet_F(dir, x, y, Z_INDEX_BULLET, vx, vy, B_SPAWN_MODE_SETSPEED));
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	scene->add_object(move(bullet));

}