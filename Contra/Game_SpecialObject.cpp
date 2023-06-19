#include "Game_SpecialObject.h"
#include "State_Object_Active.h"
#include "State_Object_Standby.h"
#include "State_Object_Emerge.h"
#include "State_Object_Hide.h"
#include "State_Contra_Die.h"

void Game_SpecialObject::UpdateState()
{
	if (_state == NULL)
	{
		if (_haveStandby)
			_state.reset(new State_Object_Standby(this));
		else 
			_state.reset(new State_Object_Active(this));
	}

	if (_die && !dynamic_cast<State_Contra_Die*>(_state.get()))
	{
		_state.reset(new State_Contra_Die(this, _DieDelay));
		return;
	}
	else if (_die && dynamic_cast<State_Contra_Die*>(_state.get()))
	{
		return;
	}

	switch (_state->NextState())
	{
	case STATE_OBJ_STANDBY:
		_state.reset(new State_Object_Standby(this));
		break;
	case STATE_OBJ_EMERGE:
		_state.reset(new State_Object_Emerge(this));
		break;
	case STATE_OBJ_ACTIVE:
		_state.reset(new State_Object_Active(this));
		break;
	case STATE_OBJ_HIDE:
		_state.reset(new State_Object_Hide(this));
		break;
	}
}

void Game_SpecialObject::KeyDownEventHandler(int KeyCode)
{
	if (_state == NULL)
		return;

	// Characer in force-moving state, ignore KeyEvent.
	if (_ForceX != 0 || _ForceY != 0)
		return;

	if (dynamic_cast<State_Object_Base*>(_state.get()))
	{
		State_Object_Base* state = (State_Object_Base*)_state.get();
		switch (KeyCode)
		{
		case DIK_O:
			state->KeyPressed_Active();
			break;
		case DIK_P:
			state->KeyPressed_Hide();
			break;

		}
	}
}