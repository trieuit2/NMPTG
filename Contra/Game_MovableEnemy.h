#pragma once
#include "Game_Enemy.h"
class Game_MovableEnemy : public Game_Enemy
{
	protected:
		void UpdateState() override { Game_Enemy::UpdateState(); }
		void UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects = NULL) override { Game_Enemy::UpdateBehavior(dt, coObjects); }
	public:
		Game_MovableEnemy(float x, float y, int z, int width, int height) : Game_Enemy(x, y, z, width, height) {}

		void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override { Game_Enemy::Update(dt, coObjects); }
		int CharID() override { return 0; }
		void GetCustomSize(int state, int& width, int& height) override { Game_Enemy::GetCustomSize(state, width, height); }
		
		// When no collision has been detected (triggered by CCollision::Process)
		void OnNoCollision(DWORD dt) override { Game_Enemy::OnNoCollision(dt); }
		// When collision with an object has been detected (triggered by CCollision::Process)
		void OnCollisionWith(PCOLLISIONEVENT e) override { Game_Enemy::OnCollisionWith(e); }

		void Execute_DieAction() override { Game_Enemy::Execute_DieAction(); }
};

