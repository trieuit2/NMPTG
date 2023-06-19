#pragma once
#include "Game_Bullet.h"

class Equip_Gun_L;

#define BULLET_L_WIDTH 20
#define BULLET_L_HEIGHT 20
#define BULLET_L_INTERNAL_HITBOX_WIDTH 8
#define BULLET_L_INTERNAL_HITBOX_HEIGHT 8

class Obj_Bullet_L : public Game_Bullet
{
private:
	BYTE _WaveID = -1;
	Equip_Gun_L* _srcObj;
	DWORD _delay = 0;
	float _save_vx = 0.0f;
	float _save_vy = 0.0f;
	void Init(Equip_Gun_L* src, BYTE wave, DWORD delay)
	{
		_srcObj = src;
		_delay = delay;
		_WaveID = wave;
		_moveSpd = 0.25f;
		_OwnerID = B_OWNER_PLAYER;
		_Damage = 5;
		_SpriteId = CONTRA_BULLET_ANI_BULLET_N;
	}
public:
	// If type = true, use point (x,y) instead of vx, vy
	// vx, vy will be caculated so that bullet can move toward that point. 
	Obj_Bullet_L(Equip_Gun_L* src, BYTE wave, DWORD delay, float x, float y, int z, float vx, float vy, bool type = false) : Game_Bullet(x, y, z, BULLET_L_WIDTH, BULLET_L_HEIGHT)
	{
		Init(src, wave, delay);
		if (type)
			SetTargetPos(vx, vy);
		else
			SetVector(vx, vy);
	}

	Obj_Bullet_L(Equip_Gun_L* src, BYTE wave, DWORD delay, float x, float y, int z, float degree) : Game_Bullet(x, y, z, BULLET_L_WIDTH, BULLET_L_HEIGHT)
	{
		Init(src, wave, delay);
		SetAngle(degree);
	}

	void Update(DWORD dt) override;
	void Render() override;
	int IsCollidable() override;
	bool Test_InternalCollision(Game_ObjectBase* colObject);
};

