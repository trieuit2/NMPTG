#pragma once
#include "Game_Terrain.h"
#include "Contra_ANI_ID.h"

#define BRIDGE_S1_WIDTH 32
#define BRIDGE_S1_HEIGHT 32
#define BRIDGE_S1_EXPLOSION_INTERVAL 300

class Game_Bridge_S1 : public Game_Terrain
{
	private:
		int _triggerID = 0;
		DWORD _explosionOffset = 0;
		DWORD _explosionTick = 0;
		bool _explosionTrigger = false;
		bool _finishExplosion = false;
		void StartExplosion();
	public:
		Game_Bridge_S1(float x, float y, int z, int triggerID, DWORD TimeOffset) : Game_Terrain(x, y, z, BRIDGE_S1_WIDTH, BRIDGE_S1_HEIGHT)
		{
			_triggerID = triggerID;
			_explosionOffset = TimeOffset;
			_SpriteId = ANI_BLACK_BOX;
		}
		bool IsBlocking() { return 1; }
		bool BlockingCondition(DWORD dt, PCOLLISIONEVENT e) override;
		void Update(DWORD dt) override;
		void Render() override;
		void TriggerExplosion(int ID);
};

