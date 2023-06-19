#pragma once
#include "Game_Picture.h"
namespace WORDSPRITE
{

	int getNumberSpriteID(int number);
	//int getCharcaterSpriteID(const wchar_t& a);
	int getCharacterSpriteID(int number);
	Game_Picture createNumber(int number, float screenX, float screenY, int z);
}