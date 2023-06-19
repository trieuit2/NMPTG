#pragma once

#include <Windows.h>
#include <unordered_map>

#include "Sprites.h"
#include "AnimationFrame.h"

using namespace std;

class CAnimation
{
protected:
	ULONGLONG lastFrameTime;
	int defaultTime;
	int currentFrame;
	
	int variance = 0;
public:
	vector<LPANIMATION_FRAME> frames;
	CAnimation(int defaultTime = 100) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	virtual void Render(float x, float y, ULONGLONG& curFrameTime, int& curFrame);
	// Render using screen position instead of world location
	virtual void RenderOnScreen(float x, float y, BYTE RenderMode = RENDER_MODE_CENTER,float ratiox=1,float ratioy=1);
	virtual CAnimation* Clone_Flip();
	bool checkFinalFrame(int&curFrame);
};
LPSPRITE _Clone_Flip_CSprite(LPSPRITE target, int new_id = -1111111);
typedef CAnimation* LPANIMATION;