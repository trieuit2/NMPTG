#pragma once
#include "Game_MovableObject.h"
#include "Contra_ANI_ID.h"

#define MOVING_STONE_WIDTH 32
#define MOVING_STONE_HEIGHT 32

class Obj_MovingStone : public Game_MovableObject
{
	private:
		float _maxRangeL = 0;
		float _maxRangeR = 0;
		bool _moveToLeft = false;
	public:
		Obj_MovingStone(float x, float y, int z, float maxRangeL, float maxRangeR)
			: Game_MovableObject(x, y, z, MOVING_STONE_WIDTH, MOVING_STONE_HEIGHT)
		{
			_maxRangeL = maxRangeL;
			_maxRangeR = maxRangeR;
			_moveSpd = 0.05f;
			_gravity = false;
			_SpriteId = ANI_MOVING_ROCK;
			_needScanCollision = false;
		}
		void Update(DWORD dt) override;
		bool IsBlocking() { return 1; }
		bool BlockingCondition(DWORD dt, PCOLLISIONEVENT e) override;
};

