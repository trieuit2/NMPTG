#pragma once
#include "State_Contra_Base.h" 

class State_Contra_Swim : public State_Contra_Base
{
	public:
		State_Contra_Swim(Game_ObjectBase* obj) : State_Contra_Base(obj) {}

		int StateId() override { return STATE_SWIM; }
		void Render() override;
		void Update(DWORD dt) override;

		void KeyHold_Left() override;
		void KeyHold_Right() override;
		
		void KeyPressed_Shoot() override;
		void KeyHold_Shoot() override;

};

