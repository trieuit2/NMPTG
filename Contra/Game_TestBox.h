#pragma once
#include "Game_MovableObject.h"

class Game_TestBox : public Game_MovableObject
{
	private:
		vector<PCOLLISIONEVENT> _collisionList;
	public:
		Game_TestBox(float x, float y, int z, int width, int height, float vx, float vy) : Game_MovableObject(x, y, z, width, height)
		{
			SetSpeed(vx,vy);
		}
		~Game_TestBox()
		{
			for (int i = 0; i < _collisionList.size(); i++)
			{
				delete _collisionList[i];
			}
		}

		vector<PCOLLISIONEVENT>* GetCollisionList() { return &_collisionList; }

		void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override;
		// When no collision has been detected (triggered by CCollision::Process)
		void OnNoCollision(DWORD dt) override;
		// When collision with an object has been detected (triggered by CCollision::Process)
		void OnCollisionWith(PCOLLISIONEVENT e) override;
		// Is this object blocking other object? If YES, collision framework will automatically push the other object
};

