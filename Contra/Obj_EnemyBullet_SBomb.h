#pragma once
#include "Game_Bullet.h"

#define ENEMYBULLET_SBOMB_WIDTH 8
#define ENEMYBULLET_SBOMB_HEIGHT 8
#define SBOMB_MAX_TRAVEL_DISTANCE 250
#define SBOMB_SPREAD_X 200
#define SBOMB_SPREAD_Y 32

class Obj_EnemyBullet_SBomb : public Game_Bullet
{
	protected:
		float _travelled_Distance = 0;
		int _bypassPlatformID = -1;
		bool _explodeFlag = false;
		void Init()
		{
			_moveSpd = 0.2f;
			_OwnerID = B_OWNER_ENEMY;
			_Damage = 1;
			_SpriteId = CONTRA_BULLET_ANI_BULLET_S;
			_gravity = false;
		}

		void Create_ExplodeAnimation();
	public:
		// If type = true, use point (x,y) instead of vx, vy
		// vx, vy will be caculated so that bullet can move toward that point. 

		Obj_EnemyBullet_SBomb(float x, float y, int z) : Game_Bullet(x, y, z, ENEMYBULLET_SBOMB_WIDTH, ENEMYBULLET_SBOMB_HEIGHT)
		{
			Init();
			_vy = _moveSpd;
			_needScanCollision = true;
		}

		~Obj_EnemyBullet_SBomb()
		{
			Cleaning();
		}

		void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override;
		bool CollideBlockerCondition(DWORD dt, PCOLLISIONEVENT e) override;
		void OnNoCollision(DWORD dt) override { Game_Bullet::OnNoCollision(dt); }
		bool IgnoreBlocking() override { return false; }
		bool IsExplosive() override { return true; }
		void Execute_BeforeDelete() override;
		void Execute_ExplodingEffect() override;
};

class Obj_EnemyBullet_SBomb_Phase2 : public Obj_EnemyBullet_SBomb
{
	private:
		int _firstBypassPlatform = -1;
		void Init()
		{
			_moveSpd = 0.06f;
			_OwnerID = B_OWNER_ENEMY;
			_Damage = 1;
			_SpriteId = CONTRA_BULLET_ANI_BULLET_M;
			_gravity = true;
		}
	public:
		Obj_EnemyBullet_SBomb_Phase2(float x, float y, int z, int firstBypassPlatform, float ForceX, float ForceY) : Obj_EnemyBullet_SBomb(x, y, z)
		{
			Init();
			_vy = _moveSpd;
			_ForceX = ForceX;
			_ForceY = ForceY;
			_needScanCollision = true;
			_firstBypassPlatform = firstBypassPlatform;
		}

		~Obj_EnemyBullet_SBomb_Phase2()
		{
			Cleaning();
		}

		bool CollideBlockerCondition(DWORD dt, PCOLLISIONEVENT e) override;
		void Execute_BeforeDelete() override;
};

