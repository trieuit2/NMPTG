#pragma once
#include "Game_StaticObject.h"

class Game_Terrain : public Game_StaticObject
{
	public:
		Game_Terrain(float x, float y, int z, int width, int height) : Game_StaticObject(x, y, z, width, height) { }

		int objectType() { return TYPE_TERRAIN; }
		bool IsBlocking() override { return 1; }
		
		// Aditional condition for blocking object. This condition will check if object has IsBlocking = 1.
		// If NO, this Blocking object will be skip while processing collision framework.
		bool BlockingCondition(DWORD dt, PCOLLISIONEVENT e) override { return 1; }

		void Render() { RenderHitbox(); }
		void SetNeedRender(bool b) { _needRender = b; }
		bool NeedRender() { return _needRender; }
};

