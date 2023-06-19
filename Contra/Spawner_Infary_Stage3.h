#pragma once
#include "Game_Spawner.h"

#define SPAWNER_INFARY_S3_BASE_INTERVAL 2800

class Spawner_Infary_Stage3 : public Game_Spawner
{
	protected:
		bool _spawnToLeft = true;
	public:
		Spawner_Infary_Stage3(float x, float y, int z, DWORD modifier, DWORD offset) : Game_Spawner(x, y, z)
		{
			_Interval = SPAWNER_INFARY_S3_BASE_INTERVAL + modifier;
			_Offset = offset;
		}

		void Update(DWORD dt);
};

class Spawner_Infary_Stage3_Left : public Spawner_Infary_Stage3
{
	public:
		Spawner_Infary_Stage3_Left(float x, float y, int z, DWORD modifier, DWORD offset) : Spawner_Infary_Stage3(x, y, z, modifier, offset)
		{
			_spawnToLeft = true;
		}
		void Update(DWORD dt) override { Spawner_Infary_Stage3::Update(dt); }
};

class Spawner_Infary_Stage3_Right : public Spawner_Infary_Stage3
{
public:
	Spawner_Infary_Stage3_Right(float x, float y, int z, DWORD modifier, DWORD offset) : Spawner_Infary_Stage3(x, y, z, modifier, offset)
	{
		_spawnToLeft = false;
	}
	void Update(DWORD dt) override { Spawner_Infary_Stage3::Update(dt); }
};
