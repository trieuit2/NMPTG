#pragma once
#include "State_Contra_Base.h"
class State_Contra_Dive : public State_Contra_Base
{
	private:
		DWORD _diveTime = 0;
	public:
		State_Contra_Dive(Game_ObjectBase* obj, DWORD diveTime = 0) : State_Contra_Base(obj)
		{
			_diveTime = diveTime;
		}

		int StateId() override { return STATE_DIVE; }
		void Render() override;
		void Update(DWORD dt) override;
};

