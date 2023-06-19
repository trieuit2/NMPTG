#pragma once

#include <Windows.h>
#include <vector>
#include <algorithm>

#define BLOCK_PUSH_FACTOR 0.4f

using namespace std;

class Game_ObjectBase;
typedef Game_ObjectBase* PGAMEOBJECT;

struct Game_CollisionEvent;
typedef Game_CollisionEvent* PCOLLISIONEVENT;

struct Game_CollisionEvent
{
	PGAMEOBJECT src_obj;		// source object : the object from which to calculate collision
	PGAMEOBJECT obj;			// the target object

	float t, nx, ny;

	float dx, dy;				// *RELATIVE* movement distance between this object and obj
	bool isDeleted;

	Game_CollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0,
		PGAMEOBJECT obj = NULL, PGAMEOBJECT src_obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj;
		this->src_obj = src_obj;
		this->isDeleted = false;
	}

	int WasCollided() { return t >= -1.0f && t <= 1.0f; }

	static bool compare(const PCOLLISIONEVENT& a, PCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};

class Game_Collision
{
	static Game_Collision* __instance;
public:
	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st,
		float sr,
		float sb,
		float& t,
		float& nx,
		float& ny);

	PCOLLISIONEVENT SweptAABB(
		PGAMEOBJECT objSrc,
		DWORD dt,
		PGAMEOBJECT objDest);
	void Scan(
		PGAMEOBJECT objSrc,
		DWORD dt,
		vector<PGAMEOBJECT>* objDests,
		vector<PCOLLISIONEVENT>& coEvents);

	void Filter(
		PGAMEOBJECT objSrc,
		vector<PCOLLISIONEVENT>& coEvents,
		PCOLLISIONEVENT& colX,
		PCOLLISIONEVENT& colY,
		int filterBlock,
		int filterX,
		int filterY);

	void Process(PGAMEOBJECT objSrc, DWORD dt, vector<PGAMEOBJECT>* coObjects);

	static Game_Collision* GetInstance();
};