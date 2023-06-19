#pragma once
#include "Game_Spawner.h"

#define SPAWN_FALLING_ROCK_INTERVAL 3000

class Spawner_FallingStone : public Game_Spawner
{
	public:
		Spawner_FallingStone(float x, float y, int z, DWORD modifier, DWORD offset = 0) : Game_Spawner(x, y, z)
		{
			_Interval = SPAWN_FALLING_ROCK_INTERVAL + modifier;
			_Offset = offset;
		}

		void Update(DWORD dt);
};

