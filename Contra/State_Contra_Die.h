#pragma once
#include "State_Contra_Base.h"

#define INFINITE_DELAY 99999999

class State_Contra_Die : public State_Contra_Base
{
	private:
		DWORD _delayDelete = 1;
		bool _trigger = true;
		bool _isOnGround = false;
	public:
		State_Contra_Die(Game_ObjectBase* obj, DWORD delayDelete) : State_Contra_Base(obj) { _delayDelete = delayDelete; }

		int StateId() override { return STATE_DIE; }

		void Render() override;
		void Update(DWORD dt) override;

};

