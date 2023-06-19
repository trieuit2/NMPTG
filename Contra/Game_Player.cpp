#include "Game_Player.h"
#include "Game.h"
#include "State_Contra_Idle.h"
#include "State_Contra_Walk.h"
#include "State_Contra_Fall.h"
#include "State_Contra_Swim.h"
#include "State_Contra_Jump.h"
#include "State_Contra_Lie.h"
#include "State_Contra_Dive.h"
#include "State_Contra_Die.h"
#include "Contra_GET_ANI.h"
#include "Enemy_RedGunner.h"
#include "Game_DeadlyBlock.h"
#include "ScreenManager.h"
#include "StageEventHandler_Base.h"
#include "CharacterEffect.h"
using namespace CHARACTER_EFFECT;
int Game_Player::CharID()
{
	return CHAR_CONTRA;
}

void Game_Player::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	if (_auto)
		ExecuteAction();

	Game_Character::Update(dt, coObjects);

	// UPDATE SOME PARAMS
	// invincible mode
	if (_havingInvinicble_effect)
	{
		_ghost = true;
		_invincible_interval += dt;
		_invincible_ani_flash= !(_invincible_interval / PLAYER_INVINCIBLE_ANI_INTERVAL%2);
	}
	else
	{
		//_invincible_interval = 0;
		//_invincible_ani_flash = false;
		if (_state != NULL && _state.get()->StateId() != STATE_DIVE)
			_ghost = false;
	}
	if (_havingB_effect)
	{
		_upgradeB_interval += dt;
		_upgradeB_ani_flash = ((_upgradeB_interval % 250) > 125);
	}
	// Wait for revive
	if (_hp > 0)
	{
		if (_die && _revive_interval > dt)
		{
			_ghost = true;
			_revive_interval -= dt;
		}
		else if (_die)
		{
			PerformRevive();
		}
	}

	// Check Collision event
	Game_Collision::GetInstance()->Process(this, dt, coObjects);
	
	if (_state != NULL)
		_state->Update(dt);
	UpdateState();
	ResetStateParams();
}

void Game_Player::_Render(int aniId, float x, float y)
{
	if (aniId > 0)
	{
		CAnimations* animations = CAnimations::GetInstance();
		if (curAni != aniId)
		{
			curFrameTime = 0;
			curFrame = 0;
			curAni = aniId;
		}
		aniId += _upgradeB_ani_flash && !_die? 160000 : 0;
		animations->Get(aniId)->Render(x, y, curFrameTime, curFrame);
	}
}

void Game_Player::Render()
{
	RenderHitbox();

	if (_invincible_interval > 0 && _invincible_ani_flash)
		return;

	//if (_upgradeB_interval > 0 && _upgradeB_ani_flash)
	//	return;

	if (_state != NULL)
		_state->Render();
}

void Game_Player::UpdateState()
{
	if (_state == NULL)
	{
		_state.reset(new State_Contra_Idle(this));
		return;
	}

	if (_die && !dynamic_cast<State_Contra_Die*>(_state.get()))
	{
		// player won't be deleted
		_state.reset(new State_Contra_Die(this, 1000000));
		return;
	}
	else if (_die && dynamic_cast<State_Contra_Die*>(_state.get()))
	{
		return;
	}
	else if (!_die && dynamic_cast<State_Contra_Die*>(_state.get()))
	{
		_state.reset(new State_Contra_Idle(this));
		return;
	}

	int saveFace = 0;
	if (_state->StateId() == STATE_JUMP)
	{
		saveFace = ((State_Contra_Jump*)(_state.get()))->GetFace();
	}

	switch (_state->NextState())
	{
	case STATE_IDLE:		
		_state.reset( new State_Contra_Idle(this, saveFace));
		break;
	case STATE_WALK:	
		_state.reset(new State_Contra_Walk(this));
		break;
	case STATE_FALL:
		_state.reset(new State_Contra_Fall(this));
		break;
	case STATE_SWIM:
		_state.reset(new State_Contra_Swim(this));
		break;
	case STATE_JUMP:
		_state.reset(new State_Contra_Jump(this));
		break;
	case STATE_LIE:
		_state.reset(new State_Contra_Lie(this));
		break;
	case STATE_DIVE:
		if (_state.get()->StateId() == STATE_JUMP
			|| _state.get()->StateId() == STATE_FALL)
			_state.reset(new State_Contra_Dive(this, 500));
		else 
			_state.reset(new State_Contra_Dive(this));
		break;
	}
}

void Game_Player::KeyDownEventHandler(int KeyCode)
{
	if (_state.get() == NULL)
		return;

	// Player characer in force-moving state, ignore KeyEvent.
	if (_ForceX != 0)
		return;
	
	State_Contra_Base* state = (State_Contra_Base*)_state.get();

	// Auto mode (SceneEventHandler will control player instead)
	if (_auto)
	{
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
			// Can't auto shoot
			break;
		case DIK_P:
			state->KeyPressed_Jump();
			break;
		}
		return;
	}
	else
	{
		switch (KeyCode)
		{
		case DIK_UP:
			state->KeyPressed_Up();
			break;
		case DIK_DOWN:
			state->KeyPressed_Down();
			break;
		case DIK_LEFT:
			state->KeyPressed_Left();
			break;
		case DIK_RIGHT:
			state->KeyPressed_Right();
			break;
		case DIK_O:
			state->KeyPressed_Shoot();
			break;
		case DIK_P:
			state->KeyPressed_Jump();
			break;
		}
	}
}

void Game_Player::KeyUpEventHandler(int KeyCode)
{
	if (_state.get() == NULL)
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

void Game_Player::KeyReleaseAll()
{
	KeyUpEventHandler(DIK_UP);
	KeyUpEventHandler(DIK_DOWN);
	KeyUpEventHandler(DIK_LEFT);
	KeyUpEventHandler(DIK_RIGHT);
	KeyUpEventHandler(DIK_O);
	KeyUpEventHandler(DIK_P);
}

void Game_Player::KeyStateHandler(BYTE* state)
{
	if (_state == NULL)
		return;

	// Player characer in force-moving state, ignore KeyEvent.
	if (_ForceX != 0)
		return;
	
	// Disable when player's character in auto control mode
	if (_auto)
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

	if (game->IsKeyDown(DIK_O))
	{
		CharState->KeyHold_Shoot();
	}
	else
	{
		CharState->KeyReleased_Shoot();
	}
}

void Game_Player::OnNoCollision(DWORD dt) 
{
	Game_Character::OnNoCollision(dt);
}

void Game_Player::OnCollisionWith(PCOLLISIONEVENT e)
{
	Game_Character::OnCollisionWith(e);
	
	// touched deadly block
	if (!_die && dynamic_cast<Game_DeadlyBlock*>(e->obj))
	{
		DieEvent();
		return;
	}

	// touched sweeper block (vertical direction)
	if (!_die && dynamic_cast<Game_SweeperBlock*>(e->obj))
	{
		Game_SweeperBlock* block = (Game_SweeperBlock*)(e->obj);
		if (block->CanKillPlayer())
		{
			DieEvent();
			return;
		}
	}

	if (!_die && !_ghost && dynamic_cast<Game_Enemy*>(e->obj))
	{
		Game_Enemy* enemy = (Game_Enemy*)(e->obj);
		
		// Upgrade B effect
		if (_havingB_effect && !enemy->IsGhost() && !enemy->IsImmortal() && enemy->EnemyType() == ENEMY_SOLDIER)
		{
			enemy->forceDie();
			return;
		}
		
		if (!IsImmortal() && enemy->BodyDamage())
		{
			DieEvent();
			return;
		}
	}

	// Hit bullet
	if (!_ghost && dynamic_cast<Game_Bullet*>(e->obj))
	{
		Game_Bullet* bullet = ((Game_Bullet*)e->obj);
		if (bullet->OwnerID() == B_OWNER_ENEMY)
		{
			if (!_immortal)
				DieEvent();
			if (bullet->IsExplosive())
				bullet->Execute_ExplodingEffect();
			bullet->DeleteThis();
		}
	}
}

void Game_Player::GetCustomSize(int state, int& width, int& height)
{
	switch (state)
	{
	case STATE_IDLE:
		width = PLAYER_BASE_WIDTH;
		height = PLAYER_BASE_HEIGHT;
		break;
	case STATE_FALL:
		width = PLAYER_BASE_WIDTH;
		height = PLAYER_BASE_HEIGHT;
		break;
	case STATE_SWIM:
		width = PLAYER_SWIM_WIDTH;
		height = PLAYER_SWIM_HEIGHT;
		break;
	case STATE_WALK:
		width = PLAYER_BASE_WIDTH;
		height = PLAYER_BASE_HEIGHT;
		break;
	case STATE_JUMP:
		width = PLAYER_JUMP_WIDTH;
		height = PLAYER_JUMP_HEIGHT;
		break;
	case STATE_LIE:
		width = PLAYER_LIE_WIDTH;
		height = PLAYER_LIE_HEIGHT;
		break;
	case STATE_DIVE:
		width = PLAYER_DIVE_WIDTH;
		height = PLAYER_DIVE_HEIGHT;
		break;
	case STATE_DIE:
		width = PLAYER_BASE_WIDTH;
		height = PLAYER_BASE_HEIGHT;
		break;
	default:
		break;
	}
}

void Game_Player::GetSpriteOffset(int state, float& x, float& y)
{
	switch (state)
	{
	case STATE_IDLE:
		x = PLAYER_IDLE_OFFSET_X;
		y = PLAYER_IDLE_OFFSET_Y;
		break;
	case STATE_FALL:
		x = PLAYER_IDLE_OFFSET_X;
		y = PLAYER_IDLE_OFFSET_Y;
		break;
	case STATE_SWIM:
		x = PLAYER_SWIM_OFFSET_X;
		y = PLAYER_SWIM_OFFSET_Y;
		break;
	case STATE_WALK:
		x = PLAYER_WALK_OFFSET_X;
		y = PLAYER_WALK_OFFSET_Y;
		break;
	case STATE_JUMP:
		x = PLAYER_JUMP_OFFSET_X;
		y = PLAYER_JUMP_OFFSET_Y;
		break;
	case STATE_LIE:
		x = PLAYER_LIE_OFFSET_X;
		y = PLAYER_LIE_OFFSET_Y;
		break;
	case STATE_DIVE:
		x = PLAYER_DIVE_OFFSET_X;
		y = PLAYER_DIVE_OFFSET_Y;
	case STATE_DIE:
		x = PLAYER_DIE_OFFSET_X;
		y = PLAYER_DIE_OFFSET_Y;
		break;
	default:
		break;
	}
	if (!_faceLeft)
		x = -x;
}

void Game_Player::Execute_DieAction()
{
	Game_Character::Execute_DieAction();
	_lockFace = true;
	if (_faceLeft)
	{
		_ForceX = 40;
	}
	else
	{
		_ForceX = -40;
	}
	_ForceY = 40;
}

void Game_Player::DieEvent()
{
	forceDie();
	_cleanEffect();
	_hp--;
	
	_revive_interval = PLAYER_WAIT_FOR_REVIVE_TIME;
}

void Game_Player::PerformRevive()
{
	_die = false;
	_revive_interval = 0;
	//_invincible_ani_flash = false;
	//_invincible_interval = PLAYER_REVIVE_INVINCIBLE_TIME;
	_lockFace = false;
	
	// Get Respawn point

	StageEventHandler_Base* helper = ((Scene_Battle*)(ScreenManager::GetInstance()->Scene()))->GetStageEventHandler();

	helper->HelpGetRevivePoint(_revive_pos_X, _revive_pos_Y);
	// --------------
	_ForceX = 0;
	_x = _revive_pos_X;
	_y = _revive_pos_Y;
	// --------------
	_ghost = true;
	_state.reset(new State_Contra_Idle(this));
	// Reset to normal gun
	ChangeWeapon(new Equip_Gun_N());
	CHARACTER_EFFECT::applyEffect(this, CHARACTER_EFFECT::DEFAULT_IMORTAL, PLAYER_REVIVE_INVINCIBLE_TIME);
}

void Game_Player::Apply_UpgradeB(bool state)
{
	_havingB_effect = state;
	//_upgradeB_ani_flash = false;
}

void Game_Player::_startCharacterEffect(int _effect)
{
	switch (_effect)
	{
	case BARRIER: _havingB_effect = true; _upgradeB_ani_flash = false; break;
	case DEFAULT_IMORTAL: _havingInvinicble_effect = true; _invincible_ani_flash = false; break;
	default:
		break;
	}
}

void Game_Player::_updateCharacterEffect(int _effect)
{
	switch (_effect)
	{
	case BARRIER: _upgradeB_ani_flash = _effect_lists[_effect].get()->getDuration() % 500 > 250; break;
	case DEFAULT_IMORTAL: _invincible_ani_flash = _effect_lists[_effect].get()->getDuration() % 500 > 250; break;
	default:
		break;
	}
}

void Game_Player::_expireCharacterEffect(int _effect)
{
	switch (_effect)
	{
	case BARRIER: 
		_havingB_effect = false; 
		_upgradeB_ani_flash = false;
		break;
	case DEFAULT_IMORTAL: 
		_havingInvinicble_effect=false;
		_invincible_ani_flash = false;
		break;
	default:
		break;
	}
}
