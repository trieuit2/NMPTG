#pragma once
#include "State_Contra_Base.h"

class State_Contra_Fall : public State_Contra_Base
{
	public:
		State_Contra_Fall(Game_ObjectBase* obj) : State_Contra_Base(obj) {}

		int StateId() override { return STATE_FALL; }
		void Render() override;
		void Update(DWORD dt) override;

		void KeyHold_Left() override;
		void KeyHold_Right() override;
};

