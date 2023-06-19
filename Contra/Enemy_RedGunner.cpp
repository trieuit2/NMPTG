#include "Enemy_RedGunner.h"
#include "Contra_GET_ANI.h"
#include "Game_Water.h"
#include "Game_TestBox.h"
#include "Game_Player.h"
#include "Scene_Battle.h"
#include "State_Contra_Jump.h"
#include "Obj_MovingStone.h"

int Enemy_RedGunner::CharID()
{
	return RED_GUNNER;
}

void Enemy_RedGunner::UpdateState()
{
	Game_MovableEnemy::UpdateState();
}

void Enemy_RedGunner::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	Game_MovableEnemy::Update(dt, coObjects);
}

void Enemy_RedGunner::OnCollisionWith(PCOLLISIONEVENT e)
{
	Game_MovableEnemy::OnCollisionWith(e);
	if (dynamic_cast<Game_Water*>(e->obj))
	{
		DeleteThis();
		return;
	}
}

void Enemy_RedGunner::UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	if (!_needRender)
		return;

	if (_ActionQueue.size() > 0)
		return;
	//--------------------------------------------------------------------
	// Jump Off event
	if (_jumpOff)
		return;

	//--------------------------------------------------------------------
	// shooting
	if (_shootingTick > dt)
	{
		AddAction(DIK_DOWN);
		AddAction(DIK_DOWN, DIK_O);
		_shootingTick -= dt;
		return;
	}
	else if (_shootingTick > 0)
	{
		_wanderingTick = REDGUNNER_WANDERING_INTERVAL - (dt - _shootingTick);
		_shootingTick = 0;
		return;
	}

	//--------------------------------------------------------------------
	// wandering
	if (_wanderingTick > dt)
	{
		_wanderingTick -= dt;
	}
	else if (_jumpOff)
	{
		_wanderingTick = REDGUNNER_WANDERING_INTERVAL;
	}
	else
	{
		_shootingTick = REDGUNNER_SHOOTING_INTERVAL - (dt - _wanderingTick);
		_wanderingTick = 0;
		AddAction(DIK_PAUSE, 4);
		return;
	}

	if (_HeadToLeft)
		AddAction(DIK_LEFT);
	else
		AddAction(DIK_RIGHT);

	//--------------------------------------------------------------------
	// Use testbox to check before making decision what to do next.
	unique_ptr<Game_TestBox>testbox(new Game_TestBox(_x, _y + 1, _z, _width, _height, 0, 0));
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	Game_Player* player = scene->p1();

	// define some params
	float NEAR_X = _moveSpd * dt * 2;
	float NEAR_Y = JUMP_VECTOR * dt * 2;

	// Make testbox move down in order to get data of platform which this obj is standing on 
	testbox->SetSpeed(0, -JUMP_VECTOR);
	testbox->Update(dt, coObjects);
	// Get Collisions and handle them.
	vector<PCOLLISIONEVENT>* coEvents = testbox->GetCollisionList();
	for (int i = 0; i < coEvents->size(); i++)
	{
		PCOLLISIONEVENT e = coEvents->at(i);
		// Check current terrain
		if (dynamic_cast<Game_Terrain*>(e->obj))
		{
			if (e->ny > 0)
			{
				// obj is near border of terrain
				if (((footerX() - NEAR_X < e->obj->x() || _x <= NEAR_X) && _HeadToLeft)
					|| ((footerX() + NEAR_X > e->obj->x() + e->obj->width() || _x + _width >= scene->MapWidth() - NEAR_X) && !_HeadToLeft))
				{
					if (_turnTimes > 0)
					{
						// Turn back
						_HeadToLeft = !_HeadToLeft;
						_turnTimes--;
					}
					else
					{
						// Jump off
						Perform_JumpOff();
					}
					return;
				}
			}
		}
	}
}

void Enemy_RedGunner::Perform_JumpOff()
{
	_jumpOff = true;
	_state.reset(new State_Contra_Jump(this));
	if (_HeadToLeft)
		_ForceX = -64;
	else
		_ForceX = 64;
	_ForceY = _jumpHeight;
}

bool Enemy_RedGunner::CollideBlockerCondition(DWORD dt, PCOLLISIONEVENT e)
{
	if (_jumpOff
		&&	(	dynamic_cast<Game_Platform*>(e->obj)
			||	dynamic_cast<Game_Blocker*>(e->obj)
			||  dynamic_cast<Game_Water*>(e->obj)
			|| dynamic_cast<Obj_MovingStone*>(e->obj)))
	{
		return false;
	}
	return true;
}

void Enemy_RedGunner::Execute_DieAction()
{
	Game_MovableEnemy::Execute_DieAction();
	if (_onGround)
		jump();
}

void Enemy_RedGunner::Execute_BeforeDelete()
{
	if (_die)
	{
		CreateDieAnimation(ANI_EXPLOSION_ARMY);
	}
}

void Enemy_RedGunner::GetCustomSize(int state, int &width, int &height)
{
	switch (state)
	{
	case STATE_IDLE:
		width = REDGUNNER_BASE_WIDTH;
		height = REDGUNNER_BASE_HEIGHT;
		break;
	case STATE_FALL:
		width = REDGUNNER_BASE_WIDTH;
		height = REDGUNNER_BASE_HEIGHT;
		break;
	case STATE_SWIM:
		width = REDGUNNER_BASE_WIDTH;
		height = REDGUNNER_BASE_HEIGHT;
		break;
	case STATE_WALK:
		width = REDGUNNER_BASE_WIDTH;
		height = REDGUNNER_BASE_HEIGHT;
		break;
	case STATE_LIE:
		width = REDGUNNER_BASE_WIDTH;
		height = REDGUNNER_BASE_HEIGHT;
		break;
	case STATE_JUMP:
		width = REDGUNNER_JUMP_WIDTH;
		height = REDGUNNER_JUMP_HEIGHT;
		break;
	case STATE_DIE:
		width = REDGUNNER_BASE_WIDTH;
		height = REDGUNNER_BASE_HEIGHT;
		break;
	default:
		break;
	}
}