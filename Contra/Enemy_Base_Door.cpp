#include "Enemy_Base_Door.h"
#include "GameManager.h"

int Enemy_Base_Door::CharID()
{
	return BASE_DOOR;
}

void Enemy_Base_Door::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	Game_SpecialObject::Update(dt, coObjects);
	if (GameManager::GetInstance()->Get_StagePasscardRemain() > 1)
		_immortal = true;
	else
		_immortal = false;
}

void Enemy_Base_Door::Execute_DieAction()
{
	Game_SpecialObject::Execute_DieAction();
	GameManager::GetInstance()->Gain_StagePasscard();
}

void Enemy_Base_Door::Execute_BeforeDelete()
{
	if (_die)
	{
		CreateDieAnimation(ANI_EXPLOSION_CONSTRUCT);
	}
}