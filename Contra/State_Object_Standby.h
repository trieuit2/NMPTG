#pragma once
#include "State_Object_Base.h"

class State_Object_Standby : public State_Object_Base
{
	public:
		State_Object_Standby(Game_ObjectBase* obj) : State_Object_Base(obj) {}

		int StateId() override { return STATE_OBJ_STANDBY; }
		void Render() override;
		void Update(DWORD dt) override {}

		virtual void KeyPressed_Active() override;
};

