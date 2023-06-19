#pragma once
#include "Game_Terrain.h"

class Game_Water : public Game_Terrain
{
	public:
		Game_Water(float x, float y, int z, int width, int height) : Game_Terrain(x, y, z, width, height) {}
		bool IsBlocking() { return 1; }
};

