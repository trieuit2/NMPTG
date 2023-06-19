#pragma once
#include "Game_MovableEnemy.h"

#define INFARY_BASE_WIDTH 18
#define INFARY_BASE_HEIGHT 28
#define INFARY_JUMP_WIDTH 18
#define INFARY_JUMP_HEIGHT 28
#define INFARY_LIE_WIDTH 18
#define INFARY_LIE_HEIGHT 28
#define INFARY_SWIM_WIDTH 18
#define INFARY_SWIM_HEIGHT 28

class Enemy_Infary : public Game_MovableEnemy
	{
	private:
		void UpdateState() override;
		void UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects = NULL) override;
	public:
		Enemy_Infary(float x, float y, int z, bool faceLeft = true) : Game_MovableEnemy(x, y, z, INFARY_BASE_WIDTH, INFARY_BASE_HEIGHT)
		{
			_moveSpd = 0.08f;
			_BodyDamage = true;
			_faceLeft = faceLeft;
		}
		~Enemy_Infary() {
			Game_MovableEnemy::~Game_MovableEnemy();
		};
		void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override;
		int CharID() override;
		int EnemyType() override { return ENEMY_SOLDIER; }
		// When no collision has been detected (triggered by CCollision::Process)
		void OnNoCollision(DWORD dt) override { Game_MovableObject::OnNoCollision(dt); }
		// When collision with an object has been detected (triggered by CCollision::Process)
		void OnCollisionWith(PCOLLISIONEVENT e) override;

		void GetCustomSize(int state, int& width, int& height) override;
		void Execute_DieAction() override;
		void Execute_BeforeDelete() override;
		virtual int RewardScore() override { return 100; };
};

