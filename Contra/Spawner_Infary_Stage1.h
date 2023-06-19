#pragma once
#include "Game_Spawner.h"

#define SPAWNER_INFARY_S1_BASE_INTERVAL 1800

class Spawner_Infary_Stage1 : public Game_Spawner
{
	private:
		
	public:
		Spawner_Infary_Stage1(float x, float y, int z, DWORD modifier, DWORD offset) : Game_Spawner(x, y, z)
		{
			_Interval = SPAWNER_INFARY_S1_BASE_INTERVAL + modifier;
			_Offset = offset;
		}

		void Update(DWORD dt);
};

