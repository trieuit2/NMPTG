#include "CAnimation_OneLoop.h"

void CAnimation_OneLoop::RenderOnScreen(float x, float y, BYTE RenderMode, float ratiox, float ratioy)
{
	ULONGLONG now = GetTickCount64();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else if (currentFrame == frames.size() - 1)
	{

	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
		}

	}

	frames[currentFrame]->GetSprite()->DrawOnScreen(x, y, RenderMode, ratiox, ratioy);
}

void CAnimation_OneLoop::Render(float x, float y, ULONGLONG& curFrameTime, int& curFrame)
{
	ULONGLONG now = GetTickCount64();
	if (curFrame == -1)
	{
		curFrame = 0;
		curFrameTime = now;
	}
	else if (curFrame == frames.size() - 1)
	{

	}
	else
	{
		DWORD t = frames[curFrame]->GetTime();
		if (now - curFrameTime > t)
		{
			curFrame++;
			curFrameTime = now;
		}

	}

	frames[curFrame]->GetSprite()->Draw(x, y);
}

LPANIMATION CAnimation_OneLoop::Clone_Flip()
{

	LPANIMATION clone = new CAnimation_OneLoop(this->defaultTime); // create a new instance of the CAnimation class with the same default time

	// copy the frames vector
	for (const auto& frame : this->frames)
	{
		LPANIMATION_FRAME cloneFrame = new CAnimationFrame(_Clone_Flip_CSprite(frame->GetSprite()), frame->GetTime());
		clone->frames.push_back(cloneFrame);
	}

	return clone;
}