#include "Game_Picture.h"

void Game_Picture::Update(DWORD dt)
{
	// Update movement
	if (_moveSpeed > 0)
	{
		if (_moveDuration > dt)
		{
			_moveDuration -= dt;
			_screenX += _vx * dt;
			_screenY += _vy * dt;
		}
		else
		{
			_vx = 0;
			_vy = 0;
			_screenX = _movePosX;
			_screenY = _movePosY;
			_moveDuration = 0;
			_moveSpeed = 0;
		}
	}


	// Flasing
	if (_flashingLoop || _flashingDuration > dt)
	{
		if (!_flashingLoop)
			_flashingDuration -= dt;
		if (_flashingTicker >= dt)
		{
			_flashingTicker -= dt;
		}
		else
		{
			_flashing = !_flashing;
			_flashingTicker = _flashingInterval - (dt - _flashingTicker);
		}
	}
	else
	{
		StopFlash();
	}
}

void Game_Picture::Render()
{
	if (_SpriteID > 0 && !_flashing)
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(_SpriteID)->RenderOnScreen(_screenX, _screenY, _RenderMode,_ratiox,_ratioy);
	}
}

void Game_Picture::MoveToPoint(float x, float y, DWORD duration)
{
	float sideX = x - _screenX;
	float sideY = y - _screenY;
	float hypotenuse = sqrt(sideX * sideX + sideY * sideY);
	_moveSpeed = hypotenuse / duration;
	_vx = _moveSpeed * sideX / hypotenuse;
	_vy = _moveSpeed * sideY / hypotenuse;

	_moveDuration = duration;
	_movePosX = x;
	_movePosY = y;
}

void Game_Picture::Flash(DWORD duration, DWORD flashInterval)
{
	_flashingLoop = false;
	_flashingDuration = duration;
	_flashingInterval = flashInterval;
	_flashingTicker = _flashingInterval;
}

void Game_Picture::Flash(DWORD flashInterval)
{
	_flashingLoop = true;
	_flashingDuration = 0;
	_flashingInterval = flashInterval;
	_flashingTicker = _flashingInterval;
}

void Game_Picture::StopFlash()
{
	_flashingLoop = false;
	_flashingDuration = 0;
	_flashingInterval = 0;
	_flashingTicker = 0;
	_flashing = false;
}

