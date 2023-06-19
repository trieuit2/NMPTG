#pragma once
#include "Animation.h"
class CAnimation_OneLoop :
    public CAnimation
{

	void RenderOnScreen(float x, float y, BYTE RenderMode, float ratiox, float ratioy) override;
	void Render(float x, float y, ULONGLONG& curFrameTime, int& curFrame) override;
	LPANIMATION Clone_Flip() override;

public:

	CAnimation_OneLoop(int time=100) :CAnimation(time) { variance = 1; };
};

