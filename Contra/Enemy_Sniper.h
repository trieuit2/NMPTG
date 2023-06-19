#pragma once
#include "Game_StationEnemy.h"
#include "Equip_EnemyGun_Sniper.h"

#define SNIPER_BASE_WIDTH 18
#define SNIPER_BASE_HEIGHT 28
#define SNIPER_HIDE_WIDTH 18
#define SNIPER_HIDE_HEIGHT 28
#define SNIPER_ACTIVE_RANGE_X 256
#define SNIPER_ACTIVE_RANGE_Y 256

class Enemy_Sniper : public Game_StationEnemy
{
	private:
		void UpdateState() override { Game_StationEnemy::UpdateState(); }
		void UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects = NULL) override;
		DWORD _idle = 0;
		int _lockDir = 0;
		void Cleaning() override { Game_StationEnemy::Cleaning(); }
	public:
		Enemy_Sniper(float x, float y, int z) : Game_StationEnemy(x, y, z, SNIPER_BASE_WIDTH, SNIPER_BASE_HEIGHT)
		{
			_weapon = new Equip_EnemyGun_Sniper();
		}
		~Enemy_Sniper() {
			Game_StationEnemy::~Game_StationEnemy();
		};

		void Shoot(int DIR) override;

		void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override { Game_StationEnemy::Update(dt, coObjects); }
		int CharID() override;
		int EnemyType() override { return ENEMY_SOLDIER; }
		// When no collision has been detected (triggered by CCollision::Process)
		void OnNoCollision(DWORD dt) override { Game_StationEnemy::OnNoCollision(dt); }
		// When collision with an object has been detected (triggered by CCollision::Process)
		void OnCollisionWith(PCOLLISIONEVENT e) override { Game_StationEnemy::OnCollisionWith(e); }

		void GetCustomSize(int state, int& width, int& height) override;
		void Execute_DieAction() override;
		void Execute_BeforeDelete() override;
		virtual int RewardScore() override { return 500; };
};

