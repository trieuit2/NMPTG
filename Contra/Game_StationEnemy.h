#pragma once
#include "Game_Enemy.h"

class Game_StationEnemy : public Game_Enemy
{
	protected:
		bool _station_12DIR = false;
		void UpdateState() override;
		void UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects = NULL) override { Game_Enemy::UpdateBehavior(dt, coObjects); }
		static int Detect_Dir(float baseX, float baseY, float tarX, float tarY);
		static int Detect_Dir12(float baseX, float baseY, float tarX, float tarY);
	public:
		Game_StationEnemy(float x, float y, int z, int width, int height) : Game_Enemy(x, y, z, width, height)
		{
			_moveSpd = 0;
		}
		int baseType() { return TYPE_MOVABLE; }

		void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override { Game_Enemy::Update(dt, coObjects); }
		int CharID() override { return 0; }
		void GetCustomSize(int state, int& width, int& height) override { Game_Enemy::GetCustomSize(state, width, height); }

		// When no collision has been detected (triggered by CCollision::Process)
		void OnNoCollision(DWORD dt) override { Game_Enemy::OnNoCollision(dt); }
		// When collision with an object has been detected (triggered by CCollision::Process)
		void OnCollisionWith(PCOLLISIONEVENT e) override { Game_Enemy::OnCollisionWith(e); }

		void KeyDownEventHandler(int KeyCode) override;
		void KeyUpEventHandler(int KeyCode) override;

		void Execute_DieAction() override { Game_Enemy::Execute_DieAction(); }
};

