#include "Equip_Gun_S.h"
#include "ScreenManager.h"
#include "Game_Character.h"

void Equip_Gun_S::Fire(float& x, float& y, float& vx, float& vy, bool type)
{
	DebugOut(L"[INFO] Gun_N only has DIR MODE.\n");

}

void Equip_Gun_S::Fire(float& x, float& y, int DIR)
{
	int remain_bullet = CanShoot();
	if (remain_bullet <= 0)
		return;

	vector<unique_ptr<Obj_Bullet_S>> bullets;

	float baseAngle = 0.0f;

	switch (DIR)
	{
	case DIR_TOP:
		baseAngle = 90.0f;
		break;
	case DIR_BOTTOM:
		baseAngle = 270.0f;
		break;
	case DIR_LEFT:
		baseAngle = 180.0f;
		break;
	case DIR_RIGHT:
		baseAngle = 0.0f;
		break;
	case DIR_TOP_LEFT:
		baseAngle = 135.0f;
		break;
	case DIR_TOP_RIGHT:
		baseAngle = 45.0f;
		break;
	case DIR_BOTTOM_LEFT:
		baseAngle = 225.0f;
		break;
	case DIR_BOTTOM_RIGHT:
		baseAngle = 315.0f;
		break;
	default:
		break;
	}

	if (remain_bullet > 0)
	{
		bullets.push_back(unique_ptr<Obj_Bullet_S>(new Obj_Bullet_S(this, x, y, Z_INDEX_BULLET, baseAngle)));
		remain_bullet--;
	}

	if (remain_bullet > 0)
	{
		bullets.push_back(unique_ptr<Obj_Bullet_S>(new Obj_Bullet_S(this, x, y, Z_INDEX_BULLET, baseAngle - 10)));
		remain_bullet--;
	}

	if (remain_bullet > 0)
	{
		bullets.push_back(unique_ptr<Obj_Bullet_S>(new Obj_Bullet_S(this, x, y, Z_INDEX_BULLET, baseAngle + 10)));
		remain_bullet--;
	}

	if (remain_bullet > 0)
	{
		bullets.push_back(unique_ptr<Obj_Bullet_S>(new Obj_Bullet_S(this, x, y, Z_INDEX_BULLET, baseAngle - 20)));
		remain_bullet--;
	}

	if (remain_bullet > 0)
	{
		bullets.push_back(unique_ptr<Obj_Bullet_S>(new Obj_Bullet_S(this, x, y, Z_INDEX_BULLET, baseAngle + 20)));
		remain_bullet--;
	}

	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());

	for (int i = 0; i < bullets.size(); i++)
		scene->add_object(move(bullets[i]));
}