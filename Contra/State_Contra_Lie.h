#pragma once
#include "State_Contra_Base.h"
class State_Contra_Lie : public State_Contra_Base
{
	public:
		State_Contra_Lie(Game_ObjectBase* obj) : State_Contra_Base(obj) {}

		int StateId() override { return STATE_LIE; }
		void Render() override;
		void Update(DWORD dt) override;

		void KeyHold_Left() override;
		void KeyHold_Right() override;
		void KeyHold_Shoot() override;
		void KeyPressed_Jump() override;
		void KeyPressed_Shoot() override;
};

