#pragma once
#include "State_Contra_Base.h"

class State_Station : public State_Contra_Base
{
	private:
		int _DIR = -1;
	public:
		State_Station(Game_ObjectBase* obj) : State_Contra_Base(obj) {}
		int StateId() override { return STATE_WALK; }
		void Render() override;
		void Update(DWORD dt) override;

		void KeyPressed_Left() override;
		void KeyPressed_Right() override;
		void KeyPressed_Jump() override;
		void KeyPressed_Shoot() override;

		virtual void KeyPressed_FaceUp();
		virtual void KeyPressed_FaceDown();
		virtual void KeyPressed_FaceLeft();
		virtual void KeyPressed_FaceRight();
		virtual void KeyPressed_FaceUpLeft();
		virtual void KeyPressed_FaceUpRight();
		virtual void KeyPressed_FaceDownLeft();
		virtual void KeyPressed_FaceDownRight();
};

