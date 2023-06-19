#pragma once
#include "Game_Bullet.h"

#define ENEMYBULLET_BOMB_WIDTH 8
#define ENEMYBULLET_BOMB_HEIGHT 8
#define ENEMYBULLET_BOMB_RANGE_X 200
#define ENEMYBULLET_BOMB_RANGE_Y 32

class Obj_EnemyBullet_Bomb : public Game_Bullet
{
	protected:
		bool _explodeFlag = false;
		void Init()
		{
			_moveSpd = 0.08f;
			_OwnerID = B_OWNER_ENEMY;
			_Damage = 1;
			_SpriteId = CONTRA_BULLET_ANI_BULLET_M;
			_gravity = true;
		}

		void Create_ExplodeAnimation();
	public:
		// If type = true, use point (x,y) instead of vx, vy
		// vx, vy will be caculated so that bullet can move toward that point. 

		Obj_EnemyBullet_Bomb(float x, float y, int z) : Game_Bullet(x, y, z, ENEMYBULLET_BOMB_WIDTH, ENEMYBULLET_BOMB_HEIGHT)
		{
			Init();
			_needScanCollision = true;
			_ForceX = -ENEMYBULLET_BOMB_RANGE_X;
			_ForceY = ENEMYBULLET_BOMB_RANGE_Y;
		}

		~Obj_EnemyBullet_Bomb()
		{
			Cleaning();
		}

		void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override;
		bool CollideBlockerCondition(DWORD dt, PCOLLISIONEVENT e) override;
		void OnCollisionWith(PCOLLISIONEVENT e) override;
		void OnNoCollision(DWORD dt) override { Game_Bullet::OnNoCollision(dt); }
		bool IgnoreBlocking() override { return false; }
		bool IsExplosive() override { return true; }
		void Execute_BeforeDelete() override;
		void Execute_ExplodingEffect() override;
};

