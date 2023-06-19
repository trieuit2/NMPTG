#pragma once
#include "Game_Bullet.h"

#define ENEMYBULLET_N_WIDTH 5
#define ENEMYBULLET_N_HEIGHT 5

class Obj_EnemyBullet_N : public Game_Bullet
{
private:
	void Init()
	{
		_moveSpd = 0.08f;
		_OwnerID = B_OWNER_ENEMY;
		_Damage = 1;
		_SpriteId = CONTRA_BULLET_ANI_BULLET_E_N;
	}

public:
	// If type = true, use point (x,y) instead of vx, vy
	// vx, vy will be caculated so that bullet can move toward that point. 
	Obj_EnemyBullet_N(float x, float y, int z, float vx, float vy, bool type = false) : Game_Bullet(x, y, z, ENEMYBULLET_N_WIDTH, ENEMYBULLET_N_HEIGHT)
	{
		Init();
		if (type)
			SetTargetPos(vx, vy);
		else
			SetVector(vx, vy);

	}

	Obj_EnemyBullet_N(float x, float y, int z, float degree) : Game_Bullet(x, y, z, ENEMYBULLET_N_WIDTH, ENEMYBULLET_N_HEIGHT)
	{
		Init();
		SetAngle(degree);
	}

};

