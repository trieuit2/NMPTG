#include "Game_Bridge_S1.h"
#include "ScreenManager.h"

void Game_Bridge_S1::Update(DWORD dt)
{
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

void Game_Bridge_S1::Render()
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

void Game_Bridge_S1::StartExplosion()
{
	_finishExplosion = true;

	// animation
	Scene_Battle* scene = (Scene_Battle*)ScreenManager::GetInstance()->Scene();
	float x, y;
	GetCenterPoint(x, y);
	unique_ptr<Game_Effect> explosion1(new Game_Effect(x - 10, y - 5, Z_INDEX_ANIMATION, ANI_EXPLOSION_CONSTRUCT));
	unique_ptr<Game_Effect> explosion2(new Game_Effect(x + 10, y - 7, Z_INDEX_ANIMATION, ANI_EXPLOSION_CONSTRUCT, 100));
	unique_ptr<Game_Effect> explosion3(new Game_Effect(x, y + 5, Z_INDEX_ANIMATION, ANI_EXPLOSION_CONSTRUCT, 200));
	scene->AddEffect(move(explosion1));
	scene->AddEffect(move(explosion2));
	scene->AddEffect(move(explosion3));
}

void Game_Bridge_S1::TriggerExplosion(int ID)
{
	if (_triggerID == ID && !_explosionTrigger)
	{
		_explosionTrigger = true;
		_explosionTick = BRIDGE_S1_EXPLOSION_INTERVAL + _explosionOffset;
	}
}

bool Game_Bridge_S1::BlockingCondition(DWORD dt, PCOLLISIONEVENT e)
{
	if (_finishExplosion)
		return 0;

	if (dynamic_cast<Game_MovableObject*>(e->src_obj))
	{

		Game_MovableObject* SrcObj = (Game_MovableObject*)e->src_obj;
		if (e->ny > 0 && SrcObj->footerY() >= _y)
		{
			if (dynamic_cast<Game_Character*>(SrcObj))
			{
				Game_Character* Char = (Game_Character*)SrcObj;
				if (!Char->IsJumpDown())
					return 1;
				else
				{
					Char->SetJumpDown(0);
					return 0;
				}
			}

			return 1;
		}

	}
	return 0;
}

