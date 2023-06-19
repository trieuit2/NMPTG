#include "Enemy_Jumper.h"
#include "Contra_GET_ANI.h"
#include "Game_Water.h"
#include "Game_TestBox.h"
#include "Game_Player.h"
#include "Scene_Battle.h"
#include "State_Contra_Base.h"


int Enemy_Jumper::CharID()
{
	return RED_GUNNER;
}

void Enemy_Jumper::UpdateState()
{
	Game_MovableEnemy::UpdateState();
}

void Enemy_Jumper::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	Game_MovableEnemy::Update(dt, coObjects);
}

void Enemy_Jumper::OnCollisionWith(PCOLLISIONEVENT e)
{
	Game_MovableEnemy::OnCollisionWith(e);
	if (dynamic_cast<Game_Water*>(e->obj))
	{
		DeleteThis();
	}
}

void Enemy_Jumper::UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	if (_HeadToLeft)
		AddAction(DIK_LEFT);
	else
		AddAction(DIK_RIGHT);

	//--------------------------------------------------------------------
	// Use testbox to check before making decision what to do next.
	unique_ptr<Game_TestBox>testbox(new Game_TestBox(_x, _y, _z, _width, _height, 0, 0));
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
				if ((footerX() - NEAR_X < e->obj->x() && _faceLeft)
					|| (footerX() + NEAR_X > e->obj->x() + e->obj->width() && !_faceLeft))
				{
					// Turn back
					_HeadToLeft = !_HeadToLeft;
					return;
				}
			}
		}
	}

}

void Enemy_Jumper::Execute_DieAction()
{
	Game_MovableEnemy::Execute_DieAction();
	jump();
}

void Enemy_Jumper::GetCustomSize(int state, int& width, int& height)
{
	switch (state)
	{
	case STATE_IDLE:
		width = INFARY_BASE_WIDTH;
		height = INFARY_BASE_HEIGHT;
		break;
	case STATE_FALL:
		width = INFARY_BASE_WIDTH;
		height = INFARY_BASE_HEIGHT;
		break;
	case STATE_SWIM:
		width = INFARY_BASE_WIDTH;
		height = INFARY_BASE_HEIGHT;
		break;
	case STATE_WALK:
		width = INFARY_BASE_WIDTH;
		height = INFARY_BASE_HEIGHT;
		break;
	case STATE_JUMP:
		width = INFARY_JUMP_WIDTH;
		height = INFARY_JUMP_HEIGHT;
		break;
	case STATE_DIE:
		width = INFARY_BASE_WIDTH;
		height = INFARY_BASE_HEIGHT;
		break;
	default:
		break;
	}
}