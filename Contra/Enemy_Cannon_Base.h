#pragma once
#include "Game_StationEnemy.h"
#include "Equip_EnemyGun_Bomber.h"

#define CANNONBASE_WIDTH 20
#define CANNONBASE_HEIGHT 8

class Enemy_Cannon_Base : public Game_StationEnemy
{
	protected:
		void UpdateState() override;
		void UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects = NULL) override;
		void Cleaning() override { Game_StationEnemy::Cleaning(); }
		bool _IsTurretLeft;
	public:
		Enemy_Cannon_Base(float x, float y, int z, bool IsTurretLeft) : Game_StationEnemy(x, y, z, CANNONBASE_WIDTH, CANNONBASE_HEIGHT)
		{
			_weapon = new Equip_EnemyGun_Bomber();
			_gravity = false;
			_faceLeft = true;
			_IsTurretLeft = IsTurretLeft;
			if (!_IsTurretLeft)
				z++;
			_HardBody = true;
			_hp = 30;
		}
		~Enemy_Cannon_Base() {
			Game_StationEnemy::~Game_StationEnemy();
			Cleaning();
		};

		void Shoot(int DIR) override;

		void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override;
		int CharID() override;
		int EnemyType() override { return ENEMY_CONSTRUCTION; }
		// When no collision has been detected (triggered by CCollision::Process)
		void OnNoCollision(DWORD dt) override { Game_StationEnemy::OnNoCollision(dt); }
		// When collision with an object has been detected (triggered by CCollision::Process)
		void OnCollisionWith(PCOLLISIONEVENT e) override { Game_StationEnemy::OnCollisionWith(e); }

		void Execute_DieAction() override;
		void Execute_BeforeDelete() override;
		virtual int RewardScore() override { return 500; };
};

