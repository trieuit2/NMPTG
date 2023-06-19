#pragma once
#include "Game_Bullet.h"

#define BULLET_F_WIDTH 12
#define BULLET_F_HEIGHT 12
#define BULLET_F_DIR_CLOCKWISE 0
#define BULLET_F_DIR_COUNTER_CLOCKWISE 1
#define BULLET_F_ANGULAR_V_MULTIPLY 3.0f

class Obj_Bullet_F : public Game_Bullet
{
	private:
		float _centerX = 0;
		float _centerY = 0;
		float _radius = 16.0f;
		float _currentRad = 0.0f;
		bool _direct;
		bool _init = true;
		void Init(bool direct)
		{
			_direct = direct;
			_moveSpd = 0.2f;
			_OwnerID = B_OWNER_PLAYER;
			_Damage = 4;
			_SpriteId = CONTRA_BULLET_ANI_BULLET_F;
		}
		void SetupMovement();
		static float Vector_to_Rad(float vx, float vy);
		static void Rad_to_Vector(float rad, float radius, float &vx, float &vy);
	public:
		// If type = true, use point (x,y) instead of vx, vy
		// vx, vy will be caculated so that bullet can move toward that point. 
		Obj_Bullet_F(bool direct, float x, float y, int z, float vx, float vy, bool type = false) : Game_Bullet(x, y, z, BULLET_F_WIDTH, BULLET_F_HEIGHT)
		{
			Init(direct);
			if (type)
				SetTargetPos(vx, vy);
			else
				SetVector(vx, vy);
			SetupMovement();
		}

		Obj_Bullet_F(bool direct, float x, float y, int z, float degree) : Game_Bullet(x, y, z, BULLET_F_WIDTH, BULLET_F_HEIGHT)
		{
			Init(direct);
			SetAngle(degree);
			SetupMovement();
		}

		void Update(DWORD dt);
};

