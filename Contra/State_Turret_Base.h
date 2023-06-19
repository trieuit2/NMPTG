#pragma once
#include "State_Base.h"
#include "spawnBulletHelper.h"

// Turret && station


class State_Turret_Base : public State_Base
{
	protected:
		int _currentAngle = 1;
	public:
		State_Turret_Base(Game_ObjectBase* obj) : State_Base(obj) {}
		int CurrentAngle() { return _currentAngle; }
		virtual void KeyPressed_Left() {}
		virtual void KeyPressed_Right() {}
		virtual void KeyPressed_Shoot() {}
		virtual void KeyPressed_Hide() {}
};

