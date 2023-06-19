#pragma once
#include "Game_Bullet.h"

class Equip_Gun_S;

#define BULLET_S_WIDTH 8
#define BULLET_S_HEIGHT 8

class Obj_Bullet_S : public Game_Bullet
{
	private:
		Equip_Gun_S* _owner;
		bool _removeFlag = false;
		void Init();
	public:
		// If type = true, use point (x,y) instead of vx, vy
		// vx, vy will be caculated so that bullet can move toward that point. 
		Obj_Bullet_S(Equip_Gun_S* owner, float x, float y, int z, float vx, float vy, bool type = false) : Game_Bullet(x, y, z, BULLET_S_WIDTH, BULLET_S_HEIGHT)
		{
			_owner = owner;
			Init();
			if (type)
				SetTargetPos(vx, vy);
			else
				SetVector(vx, vy);
		}

		Obj_Bullet_S(Equip_Gun_S* owner, float x, float y, int z, float degree) : Game_Bullet(x, y, z, BULLET_S_WIDTH, BULLET_S_HEIGHT)
		{
			_owner = owner;
			Init();
			SetAngle(degree);
		}

		void DeleteThis() override;
};

