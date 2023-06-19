#include "Obj_Bullet_L.h"
#include "Equip_Gun_L.h"
#include "Game_TestBox.h"

void Obj_Bullet_L::Update(DWORD dt)
{
	if (_srcObj->CurrentWaveID() != _WaveID)
	{
		DeleteThis();
		return;
	}

	if (_delay >= dt)
	{
		_delay -= dt;
		if (_save_vx == 0 && _save_vy == 0)
		{
			_save_vx = _vx;
			_save_vy = _vy;
			_vx = 0;
			_vy = 0;
		}
	}
	else
	{
		if (_delay > 0)
			_delay = 0;
		if (_save_vx != 0 || _save_vy != 0)
		{
			_vx = _save_vx;
			_vy = _save_vy;
			_save_vx = 0;
			_save_vy = 0;
		}
	}
	Game_Bullet::Update(dt);
}

void Obj_Bullet_L::Render()
{
	if (_delay == 0)
	{
		// top
		if (_vy > 0.0f && IsEqual(_vx, 0.0f))
			_SpriteId = CONTRA_BULLET_ANI_BULLET_L_UP;
		// bottom
		else if (_vy < 0.0f && IsEqual(_vx, 0.0f))
			_SpriteId = CONTRA_BULLET_ANI_BULLET_L_DOWN;
		// left
		else if (IsEqual(_vy, 0.0f) && _vx < 0.0f)
			_SpriteId = CONTRA_BULLET_ANI_BULLET_L_LEFT;
		// right
		else if (IsEqual(_vy, 0.0f) && _vx > 0.0f)
			_SpriteId = CONTRA_BULLET_ANI_BULLET_L_RIGHT;
		// top left
		else if (_vy > 0.0f && _vx < 0.0f)
			_SpriteId = CONTRA_BULLET_ANI_BULLET_L_UP_LEFT;
		// top right
		else if (_vy > 0.0f && _vx > 0.0f)
			_SpriteId = CONTRA_BULLET_ANI_BULLET_L_UP_RIGHT;
		// bottom left
		else if (_vy < 0.0f && _vx < 0.0f)
			_SpriteId = CONTRA_BULLET_ANI_BULLET_L_DOWN_LEFT;
		// bottom right
		else if (_vy < 0.0f && _vx > 0.0f)
			_SpriteId = CONTRA_BULLET_ANI_BULLET_L_DOWN_RIGHT;
		else
			_SpriteId = ANI_EMPTY;
		Game_Bullet::Render();
	}
}

int Obj_Bullet_L::IsCollidable()
{
	if (_delay > 0)
	{
		return 0;
	}
	return 1;
}

bool Obj_Bullet_L::Test_InternalCollision(Game_ObjectBase* colObject)
{
	unique_ptr<Game_TestBox>testbox(new Game_TestBox(_x, _y, _z, BULLET_L_INTERNAL_HITBOX_WIDTH, BULLET_L_INTERNAL_HITBOX_HEIGHT, 0, 0));
	vector<Game_ObjectBase*>* col = new vector<Game_ObjectBase*>();
	col->push_back(colObject);

	float vx = (float)_width;
	float vy = (float)_height;

	// Fix internal hitbox position & speed
	// MOVING UP
	if (_vx == 0 && _vy > 0)
	{
		testbox->SetCenterPoint(footerX(), footerY());
		testbox->SetSpeed(0, vy);
	}
	// MOVING DOWN
	else if (_vx == 0 && _vy < 0)
	{
		testbox->SetCenterPoint(footerX(), _y);
		testbox->SetSpeed(0, -vy);
	}
	// MOVING LEFT
	else if (_vx < 0 && _vy == 0)
	{
		testbox->SetCenterPoint(_x + _width, _y - _height/2.0f);
		testbox->SetSpeed(-vx, 0);
	}
	// MOVING RIGHT
	else if (_vx > 0 && _vy == 0)
	{
		testbox->SetCenterPoint(_x, _y - _height / 2.0f);
		testbox->SetSpeed(vx, 0);
	}
	// MOVING UP LEFT
	else if (_vx < 0 && _vy > 0)
	{
		testbox->SetCenterPoint(_x + _width, _y - _height);
		testbox->SetSpeed(-vx, vy);
	}
	// MOVING UP RIGHT
	else if (_vx > 0 && _vy > 0)
	{
		testbox->SetCenterPoint(_x, _y - _height);
		testbox->SetSpeed(vx, vy);
	}
	// MOVING DOWN LEFT
	else if (_vx < 0 && _vy < 0)
	{
		testbox->SetCenterPoint(_x + _width, _y);
		testbox->SetSpeed(-vx, -vy);
	}
	// MOVING DOWN RIGHT
	else if (_vx > 0 && _vy < 0)
	{
		testbox->SetCenterPoint(_x, _y);
		testbox->SetSpeed(vx, -vy);
	}
	//----------------------------------------------

	// Scan collision
	bool result = false;
	
	testbox->Update(1, col);
	// Get Collisions and handle them.
	vector<PCOLLISIONEVENT>* coEvents = testbox->GetCollisionList();
	for (int i = 0; i < coEvents->size(); i++)
	{
		PCOLLISIONEVENT e = coEvents->at(i);
		if (e->obj == colObject)
		{
			result = true;
			break;
		}
	}

	delete col;
	return result;
}