#pragma once

#include "Texture.h"
#include "Game.h"
#include "STL_storage.h"

#define RENDER_MODE_CENTER 0
#define RENDER_MODE_TOP_LEFT 1

class CSprite
{
	int id;				// Sprite ID in the sprite database

	int left;
	int top;
	int right;
	int bottom;

	LPTEXTURE texture;
	D3DX10_SPRITE sprite;
	D3DXMATRIX matScaling;
public:
	CSprite(int id, int left, int top, int right, int bottom, LPTEXTURE tex, bool isMirror = false);

	
	void Draw(float x, float y, BYTE RenderMode = RENDER_MODE_CENTER);
	void DrawOnScreen(float x, float y, int width, int height, BYTE RenderMode);
	// Draw using screen position instead of world location
	void DrawOnScreen(float x, float y, BYTE RenderMode = RENDER_MODE_CENTER,float ratiox=1,float ratioy=1);
	//void Draw(float x, float y, const int width,const int heigth);
	//void Draw(float x, float y, int& width, int& heigth);
	//void Draw(float x, float y,float&width,float&heigth);
	void getAll(int& id, int& left, int& top, int& right, int& bottom, LPTEXTURE& tex);
	void getWH(float& width, float& heigth) { width = abs(right - left)/1.0f+1; heigth = abs(top - bottom)/1.0f+1; }
};

typedef CSprite* LPSPRITE;