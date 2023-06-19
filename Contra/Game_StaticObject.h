#pragma once
#include "Game_ObjectBase.h"
#include <string>

#define TYPE_TERRAIN 0
#define TYPE_LAYER 1

class Game_StaticObject : public Game_ObjectBase
{
protected:
public:
	Game_StaticObject(float x, float y, int z, int width, int height) : Game_ObjectBase(x, y, z, width, height) {};
	
	//-------------------------------------------------------------------------------
	// INHERITED

	int baseType() { return TYPE_STATIC; }
	virtual void Render() { Game_ObjectBase::Render(); }
	virtual void SetNeedRender(bool b) { _needRender = b; }
	virtual bool NeedRender() { return _needRender; }


	// Get hitbox
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override { Game_ObjectBase::GetBoundingBox(left, top, right, bottom); }
	// Collision ON or OFF ? This can change depending on object's state. For example: die
	int IsCollidable() override { return 1; }
	// When no collision has been detected (triggered by CCollision::Process)
	void OnNoCollision(DWORD dt) override { Game_ObjectBase::OnNoCollision(dt); }
	// When collision with an object has been detected (triggered by CCollision::Process)
	void OnCollisionWith(PCOLLISIONEVENT e) override { Game_ObjectBase::OnCollisionWith(e); }
	// Is this object blocking other object? If YES, collision framework will automatically push the other object
	bool IsBlocking() override { return 0; }
	// Aditional condition for blocking object. This condition will check if object has IsBlocking = 1.
	// If NO, this Blocking object will be skip while processing collision framework.
	bool BlockingCondition(DWORD dt, PCOLLISIONEVENT e) override { return 1; }
	//-------------------------------------------------------------------------------

	virtual int objectType() = 0;

	/// Update
	virtual void Update(DWORD dt) {};
};

