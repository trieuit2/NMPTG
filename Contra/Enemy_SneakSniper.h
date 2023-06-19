#pragma once
#include "Game_StationEnemy.h"
#include "Equip_EnemyGun_SneakSniper.h"

#define SNEAKSNIPER_BASE_WIDTH 16
#define SNEAKSNIPER_BASE_HEIGHT 16
#define SNEAKSNIPER_HIDE_WIDTH 16
#define SNEAKSNIPER_HIDE_HEIGHT 10
#define SNEAKSNIPER_HIDING_INTERVAL 2000
#define SNEAKSNIPER_WAIT_TO_SHOOT_INTERVAL 1000
#define SNEAKSNIPER_WAIT_TO_HIDE_INTERVAL 1200
#define SS_HIDE 0
#define SS_WAIT_TO_SHOOT 1
#define SS_WAIT_TO_HIDE 2

class Enemy_SneakSniper : public Game_StationEnemy
{
	protected:
		void UpdateState() override;
		void UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects = NULL) override;
		DWORD _waitToChangeState = SNEAKSNIPER_HIDING_INTERVAL;
		// 0 = hide
		// 1 = wait to shoot
		// 2 = wait to hide
		int _currentState = SS_HIDE;
		void Cleaning() override { Game_StationEnemy::Cleaning(); }
	public:
		Enemy_SneakSniper(float x, float y, int z) : Game_StationEnemy(x, y, z, SNEAKSNIPER_BASE_WIDTH, SNEAKSNIPER_BASE_HEIGHT)
		{
			_weapon = new Equip_EnemyGun_SneakSniper();
			_gravity = false;
			_faceLeft = true;
		}
		~Enemy_SneakSniper() {
			Game_StationEnemy::~Game_StationEnemy();
			Cleaning();
		};

		void Shoot(int DIR) override;

		void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override;
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


class Enemy_SneakSniper_Base : public Enemy_SneakSniper
{
	public:
		Enemy_SneakSniper_Base(float x, float y, int z) : Enemy_SneakSniper(x, y, z) {}
		void Execute_DieAction() override;
		void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override;
};
