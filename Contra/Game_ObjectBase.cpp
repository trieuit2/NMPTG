#include "Game_ObjectBase.h"
#include <d3dx9.h>
#include <algorithm>
#include "Textures.h"
#include "ScreenManager.h"
#include "Game_Screen.h"
#include "Scene_Battle.h"

using namespace std;

Game_ObjectBase::Game_ObjectBase(float x, float y, int z, int width, int height)
{
	_x = x;
	_y = y;
	_z = z;
	_width = width;
	_height = height;
}

void Game_ObjectBase::SetWidth(int width, int mode)
{
	
	switch (mode)
	{
	case 0: // left alignment
		break;
	case 1: // center alignment
		_x += (_width - width) / 2;
		break;
	case 2: // right alignment
		_x += (_width - width);
		break;
	}
	_width = width;
}

void Game_ObjectBase::SetHeight(int height, int mode)
{

	switch (mode)
	{
	case 0: // top alignment
		break;
	case 1: // center alignment
		_y -= (float)(_height - height) / 2 - 1;
		break;
	case 2: // bottom alignment
		_y -= (float)(_height - height) - 1;
		break;
	}
	_height = height;
}

void Game_ObjectBase::Render()
{
	RenderHitbox();
	_Render(_SpriteId);

}

void Game_ObjectBase::RenderHitbox()
{
	//D3DXVECTOR3 p(_x, _y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(-100);

	//float l, t, r, b;

	//GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = _width;
	rect.bottom = _height;

	//float cx, cy;
	Game_Screen* screen = ScreenManager::GetInstance()->Screen();
	//screen->GetPosition(cx, cy);

	float centerX, centerY;
	GetCenterPoint(centerX, centerY);
		
	screen->Convert_WorldPos_to_ScreenPos(centerX, centerY);

	CGame::GetInstance()->Draw(centerX, centerY, bbox, &rect, 0.5f, _width, _height);
}

void Game_ObjectBase::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = _x;
	top = _y;
	right = _x + _width;
	bottom = _y - _height;
}

void Game_ObjectBase::OnNoCollision(DWORD dt)
{
	UpdatePosition(dt);
}

void Game_ObjectBase::OnCollisionWith(PCOLLISIONEVENT e)
{

}

void Game_ObjectBase::_Render(int aniId)
{
	float x, y;
	GetCenterPoint(x, y);
	_Render(aniId, x, y);
}

void Game_ObjectBase::_Render(int aniId, float x, float y)
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
		animations->Get(aniId)->Render(x, y, curFrameTime, curFrame);
	}
}

bool Game_ObjectBase::atFinalFrame(int curAni)
{
	if (curAni == -99)
		curAni = this->curAni;
	else if (curAni != this->curAni)
		return false;
	else if (curAni == 0)
		return true;
	return CAnimations::GetInstance()->Get(curAni)->checkFinalFrame(curFrame);
}

void Game_ObjectBase::UpdatePosition(DWORD dt)
{
	_x += _vx * dt;
	_y += _vy * dt;
}

void Game_ObjectBase::ResetStateParams()
{

}

void Game_ObjectBase::ResetSpeed()
{
	_vx = 0;
	_vy = 0;
}