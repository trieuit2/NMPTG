#pragma once
#include "Game_StaticObject.h"

#define SPAWNER_BASE_WIDTH 10
#define SPAWNER_BASE_HEIGHT 10

class Game_Spawner : public Game_StaticObject
{
	protected:
		DWORD _Interval = 0;
		DWORD _Tick = 0;
		DWORD _Offset = 0;
		bool ProcessTimer(DWORD dt)
		{
			if (_Offset > dt)
			{
				_Offset -= dt;
				return false;
			}
			else if (_Offset > 0)
			{
				_Offset = 0;
				return false;
			}

			if (_Interval == 0)
			{
				return true;
			}
			if (_Tick > dt)
			{
				_Tick -= dt;
				return false;
			}
			else
			{
				_Tick = _Interval - (dt - _Tick);
				return true;
			}

		}
	public:
		Game_Spawner(float x, float y, int z) : Game_StaticObject(x, y, z, SPAWNER_BASE_WIDTH, SPAWNER_BASE_HEIGHT) { }

		int objectType() { return TYPE_LAYER; }
		bool IsBlocking() override { return 0; }

		void Update(DWORD dt) { Game_ObjectBase::Update(dt); }
};

