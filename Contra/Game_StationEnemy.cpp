#include "Game_StationEnemy.h"
#include "State_Station.h"
#include "State_Station_Hide.h"
#include "State_Contra_Die.h"
#include "State_Turret_Active.h"
#include "State_Turret_Emerge.h"
#include "State_Turret_Hide.h"

void Game_StationEnemy::UpdateState()
{
	if (_state == NULL)
	{
		if (!_station_12DIR)
			_state.reset(new State_Station(this));
		else
			_state.reset(new State_Turret_Active(this, DIR_9_OCLOCK));
		return;
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

	if (!_station_12DIR)
	{
		switch (_state->NextState())
		{
			// 8 DIR
		case STATE_IDLE:
			_state.reset(new State_Station_Hide(this));
			break;
		case STATE_WALK:
			_state.reset(new State_Station(this));
			break;
		}
	}
	else
	{
		State_Turret_Base* state = (State_Turret_Base*)(_state.get());
		// 12 DIR
		switch (_state->NextState())
		{
		case STATE_ACTIVE:
			_state.reset(new State_Turret_Active(this, state->CurrentAngle()));
			break;
		case STATE_EMERGE:
			_state.reset(new State_Turret_Emerge(this, state->CurrentAngle()));
			break;
		case STATE_HIDE:
			_state.reset(new State_Turret_Hide(this, state->CurrentAngle()));
			break;
		}
	}
}

void Game_StationEnemy::KeyDownEventHandler(int KeyCode)
{
	if (_state == NULL)
		return;

	// Characer in force-moving state, ignore KeyEvent.
	if (_ForceX != 0)
		return;

	if (!_station_12DIR)
	{
		// 8 DIR KeyEventHandler

		Game_Enemy::KeyDownEventHandler(KeyCode);

		if (dynamic_cast<State_Station*>(_state.get()))
		{
			State_Station* state = (State_Station*)_state.get();
			switch (KeyCode)
			{
			case DIK_NUMPAD1:
				state->KeyPressed_FaceDownLeft();
				break;
			case DIK_NUMPAD2:
				state->KeyPressed_FaceDown();
				break;
			case DIK_NUMPAD3:
				state->KeyPressed_FaceDownRight();
				break;
			case DIK_NUMPAD4:
				state->KeyPressed_FaceLeft();
				break;
			case DIK_NUMPAD6:
				state->KeyPressed_FaceRight();
				break;
			case DIK_NUMPAD7:
				state->KeyPressed_FaceUpLeft();
				break;
			case DIK_NUMPAD8:
				state->KeyPressed_FaceUp();
				break;
			case DIK_NUMPAD9:
				state->KeyPressed_FaceUpRight();
				break;
			}
		}
	}
	else
	{
		// 12 DIR KeyEventHandler

		State_Turret_Base* state = (State_Turret_Base*)(_state.get());
		switch (KeyCode)
		{
		case DIK_LEFT:
			state->KeyPressed_Left();
			break;
		case DIK_RIGHT:
			state->KeyPressed_Right();
			break;
		case DIK_P:
			state->KeyPressed_Hide();
			break;
		case DIK_O:
			state->KeyPressed_Shoot();
			break;
		}
	}

}

void Game_StationEnemy::KeyUpEventHandler(int KeyCode)
{
	if (!_station_12DIR)
	{
		Game_Enemy::KeyUpEventHandler(KeyCode);
	}
	// Station_12DIR doesn't have KeyUpEventHandler
}

#define SLOPE_DIR8_D1 0.41421f
#define SLOPE_DIR8_D2 2.41421f
#define SLOPE_DIR8_D3 -2.41421f
#define SLOPE_DIR8_D4 -0.41421f
int Game_StationEnemy::Detect_Dir(float baseX, float baseY, float tarX, float tarY)
{
	// Find a, b of straight line formula (y = ax + b) ; (baseX, baseY) is a point on the line
	// a = slope
	// straight line formula: y = a(x - baseX) + baseY 
	// => b = baseY - a * baseX

	// d1 (angle inclination = 22.5 degree)
	float d1_a = SLOPE_DIR8_D1;
	float d1_b = baseY - d1_a * baseX;
	// d2 (angle inclination = 67.5 degree)
	float d2_a = SLOPE_DIR8_D2;
	float d2_b = baseY - d2_a * baseX;
	// d3 (angle inclination = 112.5 degree)
	float d3_a = SLOPE_DIR8_D3;
	float d3_b = baseY - d3_a * baseX;
	// d4 (angle inclination = 157.5 degree)
	float d4_a = SLOPE_DIR8_D4;
	float d4_b = baseY - d4_a * baseX;

	// above d1, below d4
	if (tarY > d1_a * tarX + d1_b && tarY < d4_a * tarX + d4_b)  return DIR_LEFT;
	// above d4, below d1
	else if (tarY > d4_a * tarX + d4_b && tarY < d1_a * tarX + d1_b)  return DIR_RIGHT;
	// above d2, above d3
	else if (tarY > d2_a * tarX + d2_b && tarY > d3_a * tarX + d3_b)  return DIR_TOP;
	// below d2, below d3
	else if (tarY < d2_a * tarX + d2_b && tarY < d3_a * tarX + d3_b)  return DIR_BOTTOM;
	// below d3, above d4
	else if (tarY < d3_a * tarX + d3_b && tarY > d4_a * tarX + d4_b)  return DIR_TOP_LEFT;
	// below d2, above d1
	else if (tarY < d2_a * tarX + d2_b && tarY > d1_a * tarX + d1_b)  return DIR_TOP_RIGHT;
	// below d1, above d2
	else if (tarY < d1_a * tarX + d1_b && tarY > d2_a * tarX + d2_b)  return DIR_BOTTOM_LEFT;
	// below d4, above d3
	else if (tarY < d4_a * tarX + d4_b && tarY > d3_a * tarX + d3_b)  return DIR_BOTTOM_RIGHT;
	else return -1;
}

#define SLOPE_DIR12_D1 0.26795f
#define SLOPE_DIR12_D2 1.0f
#define SLOPE_DIR12_D3 3.73205f
#define SLOPE_DIR12_D4 -3.73205f
#define SLOPE_DIR12_D5 -1.0f
#define SLOPE_DIR12_D6 -0.26795f
int Game_StationEnemy::Detect_Dir12(float baseX, float baseY, float tarX, float tarY)
{
	// Find a, b of straight line formula (y = ax + b) ; (baseX, baseY) is a point on the line
	// a = slope
	// straight line formula: y = a(x - baseX) + baseY 
	// => b = baseY - a * baseX

	// d1 (angle inclination = 15 degree)
	float d1_a = SLOPE_DIR12_D1;
	float d1_b = baseY - d1_a * baseX;
	// d2 (angle inclination = 45 degree)
	float d2_a = SLOPE_DIR12_D2;
	float d2_b = baseY - d2_a * baseX;
	// d3 (angle inclination = 75 degree)
	float d3_a = SLOPE_DIR12_D3;
	float d3_b = baseY - d3_a * baseX;
	// d4 (angle inclination = 105 degree)
	float d4_a = SLOPE_DIR12_D4;
	float d4_b = baseY - d4_a * baseX;
	// d5 (angle inclination = 135 degree)
	float d5_a = SLOPE_DIR12_D5;
	float d5_b = baseY - d5_a * baseX;
	// d6 (angle inclination = 165 degree)
	float d6_a = SLOPE_DIR12_D6;
	float d6_b = baseY - d6_a * baseX;

	// above d2, below d3
	if (tarY > d2_a * tarX + d2_b && tarY < d3_a * tarX + d3_b)  return DIR_1_OCLOCK;
	// above d1, below d2
	else if (tarY > d1_a * tarX + d1_b && tarY < d2_a * tarX + d2_b)  return DIR_2_OCLOCK;
	// above d6, below d1
	else if (tarY > d6_a * tarX + d6_b && tarY < d1_a * tarX + d1_b)  return DIR_3_OCLOCK;
	// above d5, below d6
	else if (tarY > d5_a * tarX + d5_b && tarY < d6_a * tarX + d6_b)  return DIR_4_OCLOCK;
	// above d4, below d5
	else if (tarY > d4_a * tarX + d4_b && tarY < d5_a * tarX + d5_b)  return DIR_5_OCLOCK;
	// below d3, below d4
	else if (tarY < d3_a * tarX + d3_b && tarY < d4_a * tarX + d4_b)  return DIR_6_OCLOCK;
	// above d3, below d2
	else if (tarY > d3_a * tarX + d3_b && tarY < d2_a * tarX + d2_b)  return DIR_7_OCLOCK;
	// above d2, below d1
	else if (tarY > d2_a * tarX + d2_b && tarY < d1_a * tarX + d1_b)  return DIR_8_OCLOCK;
	// above d1, below d6
	else if (tarY > d1_a * tarX + d1_b && tarY < d6_a * tarX + d6_b)  return DIR_9_OCLOCK;
	// above d6, below d5
	else if (tarY > d6_a * tarX + d6_b && tarY < d5_a * tarX + d5_b)  return DIR_10_OCLOCK;
	// above d5, below d4
	else if (tarY > d5_a * tarX + d5_b && tarY < d4_a * tarX + d4_b)  return DIR_11_OCLOCK;
	// above d3, above d4
	else if (tarY > d3_a * tarX + d3_b && tarY > d4_a * tarX + d4_b)  return DIR_12_OCLOCK;
	else return -1;
}