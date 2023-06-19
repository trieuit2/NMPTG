#pragma once
#include "Game_MovableObject.h"

class QuadTree;

#define GAMESCREEN_WIDTH 256
#define GAMESCREEN_HEIGHT 240
#define WINDOW_WIDTH 272
#define WINDOW_HEIGHT 279

class Game_Screen : public Game_MovableObject
{
	private:
	public:
		Game_Screen(float x, float y) : Game_MovableObject(x, y, 0, GAMESCREEN_WIDTH, GAMESCREEN_HEIGHT) { _gravity = false; }
		vector<int> Get_ObjectsID_InsideScreen(QuadTree* spatial, float size);
		void CheckObjectIfNeedRender(Game_ObjectBase* obj);
		void Convert_WorldPos_to_ScreenPos(float &x, float &y);
		void DeleteThis();
		void forceDie();
};

