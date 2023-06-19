#pragma once
#include "Game_Terrain.h"

// Any living entities touching this block will be terminated except Game_Player.
// But Player will be blocked by this object.
class Game_SweeperBlock : public Game_Terrain
{
	private:
		bool _canKillPlayer = false;
	public:
		Game_SweeperBlock(float x, float y, int z, int width, int height, bool deadly = false) : Game_Terrain(x, y, z, width, height)
		{
			_canKillPlayer = deadly;
		}
		bool IsBlocking() { return 1; }
		bool BlockingCondition(DWORD dt, PCOLLISIONEVENT e) override;
		bool CanKillPlayer() { return _canKillPlayer; }
};

