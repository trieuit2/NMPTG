#include "Animations.h"
#include "debug.h"

CAnimations* CAnimations::__instance = NULL;
CAnimations* CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani,int isOneDirect)
{
if (isOneDirect == 0)
{
	LPANIMATION left_ani = ani->Clone_Flip();

	if (animations[id+1] != NULL)
		DebugOut(L"[WARNING] Animation %d already exists\n", id);

	animations[id+1] = left_ani;
}
if (animations[id] != NULL)
DebugOut(L"[WARNING] Animation %d already exists\n", id);
animations[id] = ani;
if (animations[id] == NULL)
DebugOut(L"[WARNING] Animation %d error!\n", id);
}

LPANIMATION CAnimations::Get(int id)
{
	LPANIMATION ani = animations[id];
	if (ani == NULL)
		DebugOut(L"[ERROR] Animation ID %d not found\n", id);
	return ani;
}

void CAnimations::Clear()
{
	for (auto x : animations)
	{
		LPANIMATION ani = x.second;
		delete ani;
	}

	animations.clear();
}