#pragma once
#include "Game_MovableEnemy.h"
#include "Equip_EnemyGun_N.h"

#define REDGUNNER_BASE_WIDTH 18
#define REDGUNNER_BASE_HEIGHT 28
#define REDGUNNER_JUMP_WIDTH 18
#define REDGUNNER_JUMP_HEIGHT 28
#define REDGUNNER_SWIM_WIDTH 18
#define REDGUNNER_SWIM_HEIGHT 28

#define REDGUNNER_WANDERING_INTERVAL 1200
#define REDGUNNER_SHOOTING_INTERVAL 400

class Enemy_RedGunner : public Game_MovableEnemy
{
	private:
		void UpdateState() override;
		void UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects = NULL) override;
		DWORD _wanderingTick = REDGUNNER_WANDERING_INTERVAL;
		DWORD _shootingTick = 0;
		bool _HeadToLeft = false;
		int _turnTimes = 4;
		bool _jumpOff = false;
		void Perform_JumpOff();
	public:
		Enemy_RedGunner(float x, float y, int z, bool HeadToLeft = true) : Game_MovableEnemy(x, y, z, REDGUNNER_BASE_WIDTH, REDGUNNER_BASE_HEIGHT)
		{
			_HeadToLeft = HeadToLeft;
			_moveSpd = 0.08f;
			_BodyDamage = true;
			_weapon = new Equip_EnemyGun_N();
		}
		~Enemy_RedGunner() { 
			Game_MovableEnemy::~Game_MovableEnemy();
		};
		void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override;
		int CharID() override;
		int EnemyType() override { return ENEMY_SOLDIER; }
		// When no collision has been detected (triggered by CCollision::Process)
		void OnNoCollision(DWORD dt) override { Game_MovableObject::OnNoCollision(dt); }
		// When collision with an object has been detected (triggered by CCollision::Process)
		void OnCollisionWith(PCOLLISIONEVENT e) override;
		bool CollideBlockerCondition(DWORD dt, PCOLLISIONEVENT e) override;

		void GetCustomSize(int state, int& width, int& height) override;
		void Execute_DieAction() override;
		void Execute_BeforeDelete() override;
		virtual int RewardScore() override { return 100; };
};

