#pragma once
#include "State_Base.h"
#include "Contra_ANI_ID.h"



class State_Contra_Base : public State_Base
{
	protected:
		bool HoldKeyUp = false;
		bool HoldKeyDown = false;
		bool HoldKeyLeft = false;
		bool HoldKeyRight = false;
		bool HoldKeyShoot = false;
	public:
		State_Contra_Base(Game_ObjectBase* obj) : State_Base(obj){}

		int StateId() override { return -1; }
		void Render() override {}
		void Update(DWORD dt) override {}

		virtual void KeyHold_Up() { HoldKeyUp = true; }
		virtual void KeyHold_Down() { HoldKeyDown = true; }
		virtual void KeyHold_Left() { HoldKeyLeft = true; }
		virtual void KeyHold_Right() { HoldKeyRight = true; }
		virtual void KeyHold_Shoot() { HoldKeyShoot = true; }

		virtual void KeyPressed_Up() {}
		virtual void KeyPressed_Down() {}
		virtual void KeyPressed_Left() {}
		virtual void KeyPressed_Right() {}
		virtual void KeyPressed_Shoot() { HoldKeyShoot = true; }
		virtual void KeyPressed_Jump() {}

		virtual void KeyReleased_Up() { HoldKeyUp = false; }
		virtual void KeyReleased_Down() { HoldKeyDown = false; }
		virtual void KeyReleased_Left() { HoldKeyLeft = false; }
		virtual void KeyReleased_Right() { HoldKeyRight = false; }
		virtual void KeyReleased_Shoot() { HoldKeyShoot = false; }
		virtual void KeyReleased_Jump() {}
};

