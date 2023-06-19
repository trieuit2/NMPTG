#pragma once
#include "State_Object_Base.h"

class State_Object_Active : public State_Object_Base
{
	public:
		State_Object_Active(Game_ObjectBase* obj) : State_Object_Base(obj) {}

		int StateId() override { return STATE_OBJ_ACTIVE; }
		void Render() override;
		void Update(DWORD dt) override {}

		virtual void KeyPressed_Hide() override;
};

