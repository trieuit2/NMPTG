#pragma once
#include "Game_StationEnemy.h"
#include "Equip_EnemyGun_Turret.h"

#define TURRET_BASE_WIDTH 32
#define TURRET_BASE_HEIGHT 32
#define TURRET_TRIGGER_RANGE_X 200
#define TURRET_TRIGGER_RANGE_Y 200
#define TURRET_ROTATE_CD 400

class Enemy_Turret : public Game_StationEnemy
{
	private:
		void UpdateState() override;
		void UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects = NULL) override;
		int _lockDir = 0;
		DWORD _rotate_CD = 0;
		void Cleaning() override { Game_StationEnemy::Cleaning(); }
	public:
		Enemy_Turret(float x, float y, int z, bool faceLeft = true) : Game_StationEnemy(x, y, z, TURRET_BASE_WIDTH, TURRET_BASE_HEIGHT)
		{
			_weapon = new Equip_EnemyGun_Turret();
			_hp = 12;
			_station_12DIR = true;
			_HardBody = true;
			_gravity = false;
			_DieDelay = 150;
			_faceLeft = faceLeft;
		}

		~Enemy_Turret() {
			Game_StationEnemy::~Game_StationEnemy();
		};

		void Shoot(int DIR) override;

		void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override;
		int CharID() override;
		int EnemyType() override { return ENEMY_CONSTRUCTION; }
		// When no collision has been detected (triggered by CCollision::Process)
		void OnNoCollision(DWORD dt) override { Game_StationEnemy::OnNoCollision(dt); }
		// When collision with an object has been detected (triggered by CCollision::Process)
		void OnCollisionWith(PCOLLISIONEVENT e) override { Game_StationEnemy::OnCollisionWith(e); }

		void GetCustomSize(int state, int& width, int& height) override;
		void Execute_DieAction() override;
		void Execute_BeforeDelete() override;
		virtual int RewardScore() override { return 300; };
};