#pragma once
#include "Game_Terrain.h"

// Any living entities touching this block will be terminated
class Game_DeadlyBlock : public Game_Terrain
{
	public:
		Game_DeadlyBlock(float x, float y, int z, int width, int height) : Game_Terrain(x, y, z, width, height) {}
		bool IsBlocking() { return 1; }
};

