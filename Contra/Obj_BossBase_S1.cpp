#include "Obj_BossBase_S1.h"
#include "ScreenManager.h"
#include "GameManager.h"

void Obj_BossBase_S1::Update(DWORD dt)
{
	if (!_explosionTrigger && GameManager::GetInstance()->Test_IfPassStage() == CAN_PASS_STAGE)
	{
		TriggerExplosion();
	}

	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	Game_Player* p1 = scene->p1();

	if (_explosionTrigger)
	{
		if (_explosionTick > dt)
		{
			_explosionTick -= dt;
		}
		else if (!_finishExplosion)
		{
			StartExplosion();
		}
	}
}

void Obj_BossBase_S1::Render()
{
	if (!_finishExplosion)
		RenderHitbox();
	else if (_SpriteId > 0)
	{
		CAnimations* animations = CAnimations::GetInstance();
		float x, y;
		GetCenterPoint(x, y);

		_Render(_SpriteId, x, y);
	}
}

void Obj_BossBase_S1::StartExplosion()
{
	_finishExplosion = true;

	// animation
	Scene_Battle* scene = (Scene_Battle*)ScreenManager::GetInstance()->Scene();
	float x, y;
	GetCenterPoint(x, y);
	unique_ptr<Game_Effect> explosion1(new Game_Effect(x, y, Z_INDEX_ANIMATION, ANI_EXPLOSION_CONSTRUCT));
	scene->AddEffect(move(explosion1));
}

void Obj_BossBase_S1::TriggerExplosion()
{
	_explosionTrigger = true;
	_explosionTick = BRIDGE_S1_EXPLOSION_INTERVAL + _explosionOffset;
}

bool Obj_BossBase_S1::BlockingCondition(DWORD dt, PCOLLISIONEVENT e)
{
	if (_finishExplosion)
		return 0;

	if (dynamic_cast<Game_Player*>(e->src_obj))
	{
		return 1;
	}
	return 0;
}
