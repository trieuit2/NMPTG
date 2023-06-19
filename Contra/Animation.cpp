#include "Animation.h"
#include "debug.h"

LPSPRITE _Clone_Flip_CSprite(LPSPRITE target,int new_id)
{	
	

	int id, left, top, right, bottom;
	
	LPTEXTURE tex;
	target->getAll(id, left, top, right, bottom, tex);
	new_id = id + 10;
	LPSPRITE clone = new CSprite(new_id, left, top, right, bottom, tex,true);
	return clone;

}

void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	if (sprite == NULL)
		DebugOut(L"[ERROR] Sprite ID %d not found!\n", spriteId);

	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y,ULONGLONG& curFrameTime,int&curFrame)
{
	ULONGLONG now = GetTickCount64();
	if (curFrame == -1)
	{
		curFrame = 0;
		curFrameTime = now;
	}
	else
	{
		DWORD t = frames[curFrame]->GetTime();
		if (now - curFrameTime > t)
		{
			curFrame++;
			curFrameTime = now;
			if (curFrame == frames.size()) curFrame = 0;
		}

	}

	frames[curFrame]->GetSprite()->Draw(x, y);
}
void CAnimation::RenderOnScreen(float x, float y, BYTE RenderMode,float ratiox,float ratioy)
{
	ULONGLONG now = GetTickCount64();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}

	}

	frames[currentFrame]->GetSprite()->DrawOnScreen(x, y, RenderMode,ratiox,ratioy);
}

LPANIMATION CAnimation::Clone_Flip()
{

	LPANIMATION clone = new CAnimation(this->defaultTime); // create a new instance of the CAnimation class with the same default time

	// copy the frames vector
	for (auto& frame : this->frames)
	{
		LPANIMATION_FRAME cloneFrame = new CAnimationFrame(_Clone_Flip_CSprite(frame->GetSprite()), frame->GetTime());
		clone->frames.push_back(cloneFrame);
	}

	return clone;
}

bool CAnimation::checkFinalFrame(int&curFrame)
{
	return (curFrame == frames.size() - 1);
}

