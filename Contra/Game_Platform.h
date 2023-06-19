#pragma once
#include "Game_Terrain.h"

class Game_Platform : public Game_Terrain
{
	public:
		Game_Platform(float x, float y, int z, int width, int height) : Game_Terrain(x, y, z, width, height) {}
		bool IsBlocking() { return 1; }
		bool BlockingCondition(DWORD dt, PCOLLISIONEVENT e) override;
};

