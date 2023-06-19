#pragma once
#include "State_Turret_Base.h"

class State_Turret_Emerge : public State_Turret_Base
{
	private:
		DWORD waitForChange = 50;
	public:
		State_Turret_Emerge(Game_ObjectBase* obj, int angle = DIR_12_OCLOCK) : State_Turret_Base(obj)
		{
			_currentAngle = angle;
		}
		int StateId() override { return STATE_EMERGE; }
		void Render() override;
		void Update(DWORD dt) override;

};

