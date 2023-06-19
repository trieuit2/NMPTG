#pragma once
#include "Game_MovableEnemy.h"

#define JUMPER_BASE_WIDTH 20
#define JUMPER_BASE_HEIGHT 32
#define JUMPER_JUMP_WIDTH 20
#define JUMPER_JUMP_HEIGHT 28
#define JUMPER_SWIM_WIDTH 20
#define JUMPER_SWIM_HEIGHT 32

class Enemy_Jumper : public Game_MovableEnemy
{
	private:
		bool _HeadToLeft = true;
		void UpdateState() override;
		void UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects = NULL) override;
	public:
		Enemy_Jumper(float x, float y, int z) : Game_MovableEnemy(x, y, z, JUMPER_BASE_WIDTH, JUMPER_BASE_HEIGHT)
		{
			_moveSpd = 0.08f;
			_BodyDamage = true;
		}
		~Enemy_Jumper() {
			Game_MovableEnemy::~Game_MovableEnemy();
		};
		void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override;
		int CharID() override;
		// When no collision has been detected (triggered by CCollision::Process)
		void OnNoCollision(DWORD dt) override { Game_MovableObject::OnNoCollision(dt); }
		// When collision with an object has been detected (triggered by CCollision::Process)
		void OnCollisionWith(PCOLLISIONEVENT e) override;

		void GetCustomSize(int state, int& width, int& height) override;
		void Execute_DieAction() override;
		virtual int RewardScore() override { return 100; };
};

