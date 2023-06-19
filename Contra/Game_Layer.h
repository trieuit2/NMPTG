#pragma once
#include "Game_Terrain.h"

class Game_Layer : public Game_Terrain
{
	public:
		Game_Layer(float x, float y, int z, int width, int height, int SpriteID) : Game_Terrain(x, y, z, width, height)
		{
			_SpriteId = SpriteID;
		}
		bool IsBlocking() { return 0; }
};

class Layer_BlackBox : Game_Layer
{
	public:
		Layer_BlackBox(float x, float y, int z) : Game_Layer(x, y, z, 32, 32, ANI_BLACK_BOX) {}
};

