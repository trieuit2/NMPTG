#include "Game_Picture_Static.h"

Game_Picture_Static::Game_Picture_Static(float screenX, float screenY, int z, int spriteID, BYTE RenderMode, float ratiox, float ratioy) :Game_Picture(_screenX, _screenY, z, _SpriteID, RenderMode, ratiox, ratioy)
{
	_screenX = screenX;
	_screenY = screenY;
	_ratiox = ratiox;
	_ratioy = ratioy;
	_z = z;
	_SpriteID = spriteID;
	_RenderMode = RenderMode;
}

void Game_Picture_Static::Render()
{
	auto a = CSprites::GetInstance()->Get(_SpriteID);
	CSprites::GetInstance()->Get(_SpriteID)->DrawOnScreen(_screenX, _screenY, _RenderMode,_ratiox,_ratioy);
}
