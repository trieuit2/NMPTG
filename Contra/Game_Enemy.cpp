#include "Game_Enemy.h"
#include "Game.h"
#include "State_Contra_Idle.h"
#include "State_Contra_Walk.h"
#include "State_Contra_Fall.h"
#include "State_Contra_Swim.h"
#include "State_Contra_Jump.h"
#include "State_Contra_Die.h"
#include "State_Contra_Lie.h"
#include "Contra_GET_ANI.h"
#include "Obj_Bullet_L.h"
#include "Game_DeadlyBlock.h"
#include "Game_SweeperBlock.h"
#include "GameManager.h"

int Game_Enemy::CharID()
{
	return -1;
}

void Game_Enemy::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	ExecuteAction();
	Game_Character::Update(dt, coObjects);
	Game_Collision::GetInstance()->Process(this, dt, coObjects);

	if (_state.get() != NULL)
		_state->Update(dt);
	UpdateState();

	if (_hp <= 0)
	{
		forceDie();
	}

	UpdateBehavior(dt, coObjects);
	ResetStateParams();
}

void Game_Enemy::Render()
{
	RenderHitbox();
	if (_state.get() != NULL)
		_state->Render();
}

void Game_Enemy::UpdateState()
{

	if (_state == NULL)
	{
		_state.reset( new State_Contra_Idle(this));
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
	
	switch (_state->NextState())
	{
		
	case STATE_IDLE:
		_state.reset(new State_Contra_Idle(this));
		break;
	case STATE_WALK:
		_state.reset(new State_Contra_Walk(this));
		break;
	case STATE_FALL:
		_state.reset(new State_Contra_Fall(this));
		break;
	case STATE_LIE:
		_state.reset(new State_Contra_Lie(this));
		break;
	case STATE_SWIM:
		_state.reset(new State_Contra_Swim(this));
		break;
	case STATE_JUMP:;
		_state.reset(new State_Contra_Jump(this));
		break;
	}
}

void Game_Enemy::KeyDownEventHandler(int KeyCode)
{
	if (_state == NULL)
		return;

	// Characer in force-moving state, ignore KeyEvent.
	if (_ForceX != 0)
		return;

	State_Contra_Base* state = (State_Contra_Base*)_state.get();
	switch (KeyCode)
	{
	case DIK_UP:
		state->KeyHold_Up();
		state->KeyReleased_Down();
		break;
	case DIK_DOWN:
		state->KeyHold_Down();
		state->KeyReleased_Up();
		break;
	case DIK_LEFT:
		state->KeyHold_Left();
		state->KeyReleased_Right();
		break;
	case DIK_RIGHT:
		state->KeyHold_Right();
		state->KeyReleased_Left();
		break;
	case DIK_O:
		state->KeyPressed_Shoot();
		break;
	case DIK_P:
		state->KeyPressed_Jump();
		break;
	}
}

void Game_Enemy::KeyUpEventHandler(int KeyCode)
{
	if (_state == NULL)
		return;

	// Characer in force-moving state, ignore KeyEvent.
	if (_ForceX != 0)
		return;

	State_Contra_Base* state = (State_Contra_Base*)_state.get();

	switch (KeyCode)
	{
	case DIK_UP:
		state->KeyReleased_Up();
		break;
	case DIK_DOWN:
		state->KeyReleased_Down();
		break;
	case DIK_LEFT:
		state->KeyReleased_Left();
		break;
	case DIK_RIGHT:
		state->KeyReleased_Right();
		break;
	case DIK_O:
		state->KeyReleased_Shoot();
		break;
	case DIK_P:
		state->KeyReleased_Jump();
		break;
	}
}

void Game_Enemy::KeyStateHandler(BYTE* state)
{
	if (_state == NULL)
		return;

	// Player characer in force-moving state, ignore KeyEvent.
	if (_ForceX != 0)
		return;

	LPGAME game = CGame::GetInstance();
	State_Contra_Base* CharState = (State_Contra_Base*)_state.get();
	if (game->IsKeyDown(DIK_UP))
	{
		CharState->KeyHold_Up();
		CharState->KeyReleased_Down();
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		CharState->KeyHold_Down();
		CharState->KeyReleased_Up();
	}
	else
	{
		CharState->KeyReleased_Down();
		CharState->KeyReleased_Up();
	}

	if (game->IsKeyDown(DIK_RIGHT))
	{
		CharState->KeyHold_Right();
		CharState->KeyReleased_Left();
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		CharState->KeyHold_Left();
		CharState->KeyReleased_Right();
	}
	else
	{
		CharState->KeyReleased_Left();
		CharState->KeyReleased_Right();
	}
}

void Game_Enemy::OnNoCollision(DWORD dt)
{
	Game_Character::OnNoCollision(dt);
}

void Game_Enemy::OnCollisionWith(PCOLLISIONEVENT e)
{
	if (e->obj->IsDeleted())
		return;

	Game_Character::OnCollisionWith(e);

	// Collision with deadly block
	if (dynamic_cast<Game_DeadlyBlock*>(e->obj))
	{
		DeleteThis();
		return;
	}
	// Hit bullet

	// Laser
	if (!_ghost && dynamic_cast<Obj_Bullet_L*>(e->obj))
	{
		Obj_Bullet_L* bullet = ((Obj_Bullet_L*)e->obj);

		if (bullet->OwnerID() == B_OWNER_PLAYER && bullet->Test_InternalCollision(this))
		{
			if (!_immortal)
				_hp -= bullet->Damage();
			if (_HardBody)
				bullet->DeleteThis();
		}
		return;
	}

	// other bullet
	if (!_ghost && dynamic_cast<Game_Bullet*>(e->obj))
	{
		Game_Bullet* bullet = ((Game_Bullet*)e->obj);

		if (bullet->OwnerID() == B_OWNER_PLAYER)
		{
			if (!_immortal)
				_hp -= bullet->Damage();
			bullet->DeleteThis();
		}
	}
}

void Game_Enemy::KeyReleaseAll()
{
	KeyUpEventHandler(DIK_UP);
	KeyUpEventHandler(DIK_DOWN);
	KeyUpEventHandler(DIK_LEFT);
	KeyUpEventHandler(DIK_RIGHT);
	KeyUpEventHandler(DIK_O);
	KeyUpEventHandler(DIK_P);
}

// ENEMY BEHAVIOR

void Game_Enemy::UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{

}

void Game_Enemy::Execute_DieAction()
{
	Game_Character::Execute_DieAction();
	_BodyDamage = false;
	_ghost = true;
	GameManager::GetInstance()->GainScore_P1(RewardScore());
}

void Game_Enemy::CreateDieAnimation(int aniId)
{
	Scene_Battle* scene = (Scene_Battle*)ScreenManager::GetInstance()->Scene();
	float x, y;
	GetCenterPoint(x, y);
	unique_ptr<Game_Effect> explosion(new Game_Effect(x, y, Z_INDEX_ANIMATION, aniId));
	scene->AddEffect(move(explosion));
}