#pragma once
#include "State_Object_Base.h"

// change from hide to active
class State_Object_Emerge : public State_Object_Base
{
	public:
		State_Object_Emerge(Game_ObjectBase* obj) : State_Object_Base(obj) {}

		int StateId() override { return STATE_OBJ_EMERGE; }
		void Render() override;
		void Update(DWORD dt) override;
};

