#pragma once
#include "State_Base.h"


class State_Object_Base : public State_Base
{
	public:
		State_Object_Base(Game_ObjectBase* obj) : State_Base(obj) {}

		int StateId() override { return -1; }
		void Render() override {}
		void Update(DWORD dt) override {}

		virtual void KeyPressed_Active() {}
		virtual void KeyPressed_Hide() {}
		virtual void KeyPressed_Emerge() {}
};

