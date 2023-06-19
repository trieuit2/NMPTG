#pragma once
#include "State_Turret_Base.h"
class State_Turret_Hide : public State_Turret_Base
{
	private:

	public:
		State_Turret_Hide(Game_ObjectBase* obj, int angle = DIR_12_OCLOCK) : State_Turret_Base(obj)
		{
			_currentAngle = angle;
		}
		int StateId() override { return STATE_HIDE; }
		void Render() override;
		void Update(DWORD dt) override {}

		virtual void KeyPressed_Shoot() override;
};

