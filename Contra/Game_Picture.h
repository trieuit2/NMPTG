#pragma once
#include "debug.h"
#include "Animations.h"

using namespace std;

class Game_Picture
{
	protected:
		float _screenX = 0;
		float _screenY = 0;
		int _z = 0;
		int _SpriteID = 0;
		float _vx = 0;
		float _vy = 0;
		float _ratiox;
		float _ratioy;
		DWORD _moveDuration = 0;
		float _movePosX = 0;
		float _movePosY = 0;
		float _moveSpeed = 0;
		DWORD _flashingInterval = 0;
		DWORD _flashingTicker = 0;
		DWORD _flashingDuration = 0;
		bool _flashingLoop = false;
		bool _flashing = false;
		BYTE _RenderMode;
	public:
		Game_Picture(float screenX, float screenY, int z, int spriteID, BYTE RenderMode = RENDER_MODE_TOP_LEFT,float ratiox = 1, float ratioy = 1 )
		{
			_screenX = screenX;
			_screenY = screenY;
			_z = z;
			_ratiox = ratiox;
			_ratioy = ratioy;
			_SpriteID = spriteID;
			_RenderMode = RenderMode;
		}

		float screenX() { return _screenX; }
		float screenY() { return _screenY; }
		int z() { return _z; }
		void MoveToPoint(float x, float y, DWORD duration);

		void Update(DWORD dt);
		virtual void Render();

		void Flash(DWORD duration, DWORD flashInterval);
		void Flash(DWORD flashInterval);
		void StopFlash();
};

