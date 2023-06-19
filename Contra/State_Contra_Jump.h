#pragma once
#include "State_Contra_Base.h"

class State_Contra_Jump : public State_Contra_Base
{
	private:
		int _saveLastFace = 0;
	public:
		State_Contra_Jump(Game_ObjectBase* obj) : State_Contra_Base(obj) {}

		int StateId() override { return STATE_JUMP; }
		int GetFace() { return _saveLastFace; }
		void Render() override;
		void Update(DWORD dt) override;

		void KeyHold_Left() override;
		void KeyHold_Right() override;

		void KeyPressed_Shoot() override;
		void KeyHold_Shoot() override;

};