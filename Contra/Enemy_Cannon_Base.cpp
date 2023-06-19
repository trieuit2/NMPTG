#include "Enemy_Cannon_Base.h"
#include "Scene_Battle.h"
#include "Contra_GET_ANI.h"
#include "State_Station.h"
#include "GameManager.h"

int Enemy_Cannon_Base::CharID()
{
	if (_IsTurretLeft)
		return BASE_CANNON_LEFT;
	else
		return BASE_CANNON_RIGHT;
}

void Enemy_Cannon_Base::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	Game_StationEnemy::Update(dt, coObjects);
	if (GameManager::GetInstance()->Get_StagePasscardRemain() > 3)
		_immortal = true;
	else
		_immortal = false;
}

void Enemy_Cannon_Base::Execute_DieAction()
{
	Game_StationEnemy::Execute_DieAction();
	GameManager::GetInstance()->Gain_StagePasscard();
	jump();
}

void Enemy_Cannon_Base::Execute_BeforeDelete()
{
	if (_die)
	{
		CreateDieAnimation(ANI_EXPLOSION_BULLET);
	}
}

void Enemy_Cannon_Base::UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	if (_ActionQueue.size() > 0)
		return;

	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	Game_Player* player = scene->p1();

	if (!_needRender || !player->NeedRender())
		return;

	if (_GunReloadInterval > 0)
	{
		return;
	}
	AddAction(DIK_NUMPAD4);
	AddAction(DIK_O);
}

void Enemy_Cannon_Base::Shoot(int DIR)
{
	if (_weapon == NULL || _GunReloadInterval > 0)
		return;
	float x, y;
	GetCenterPoint(x, y);
	BULLETHELPER::getSpawnCor(x, y, CharID(), Sprite_ActID(), DIR);

	_GunReloadInterval = _weapon->FireRate();

	// Cannon Base only shoot left
	_weapon->Fire(x, y, DIR_LEFT);
}

void Enemy_Cannon_Base::UpdateState()
{
	if (_state == NULL)
		_state.reset(new State_Station(this));
	Game_StationEnemy::UpdateState();
}