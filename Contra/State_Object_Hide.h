#pragma once
#include "State_Object_Base.h"
class State_Object_Hide : public State_Object_Base
{
	public:
		State_Object_Hide(Game_ObjectBase* obj) : State_Object_Base(obj) {}

		int StateId() override { return STATE_OBJ_HIDE; }
		void Render() override;
		void Update(DWORD dt) override {}

		virtual void KeyPressed_Active() override;
};

