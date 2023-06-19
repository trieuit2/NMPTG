#pragma once
#include "State_Contra_Base.h" 

class State_Contra_Idle : public State_Contra_Base
{
	private:

	public:
		State_Contra_Idle(Game_ObjectBase* obj, int forceFace = 0);
		int StateId() override { return STATE_IDLE; }
		void Render() override;
		void Update(DWORD dt) override;

		void KeyHold_Left() override;
		void KeyHold_Right() override;
		//void KeyHold_Down() override;
		//void KeyReleased_Down() override;
		void KeyPressed_Jump() override;
		void KeyPressed_Shoot() override;
		void KeyHold_Shoot() override;

};

