#include "Obj_EnemyBullet_SBomb.h"
#include "Game_Platform.h"
#include "Obj_MovingStone.h"
#include "ScreenManager.h"
#include "Contra_ANI_ID.h"

void Obj_EnemyBullet_SBomb::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	// always move up

	if (!_isDeleted && _explodeFlag)
	{
		DeleteThis();
		return;
	}

	Game_Bullet::Update(dt, coObjects);
	if (!_gravity)
		_vy = _moveSpd;
	Game_Collision::GetInstance()->Process(this, dt, coObjects);
	ResetStateParams();
}

bool Obj_EnemyBullet_SBomb::CollideBlockerCondition(DWORD dt, PCOLLISIONEVENT e)
{
	// if collide object is platform or moving stone
	if (!_explodeFlag && (dynamic_cast<Game_Platform*>(e->obj)
		|| dynamic_cast<Obj_MovingStone*>(e->obj)))
	{
		// old platform
		if (_bypassPlatformID == e->obj->id())
		{
			return false;
		}
		// new platform
		else if (_bypassPlatformID < 0)
		{
			_bypassPlatformID = e->obj->id();
			return false;
		}
		else
		{
			Execute_ExplodingEffect();
			return true;
		}
	}

	if (dynamic_cast<Game_Terrain*>(e->obj))
	{
		return false;
	}

	return true;
}

void Obj_EnemyBullet_SBomb::Create_ExplodeAnimation()
{
	Scene_Battle* scene = (Scene_Battle*)ScreenManager::GetInstance()->Scene();
	float x, y;
	GetCenterPoint(x, y);
	unique_ptr<Game_Effect> explosion(new Game_Effect(x, y, Z_INDEX_ANIMATION, ANI_EXPLOSION_BULLET));
	scene->AddEffect(move(explosion));
}

void Obj_EnemyBullet_SBomb::Execute_ExplodingEffect()
{
	_explodeFlag = true;
}

void Obj_EnemyBullet_SBomb::Execute_BeforeDelete()
{
	if (_explodeFlag)
	{
		Create_ExplodeAnimation();
		
		// spawn small bullet
		Scene_Battle* scene = (Scene_Battle*)ScreenManager::GetInstance()->Scene();
		float x, y;
		GetCenterPoint(x, y);
		unique_ptr<Obj_EnemyBullet_SBomb_Phase2> bullets[3];
		bullets[0] = unique_ptr<Obj_EnemyBullet_SBomb_Phase2>(new Obj_EnemyBullet_SBomb_Phase2(x, y, Z_INDEX_ANIMATION, _bypassPlatformID, -SBOMB_SPREAD_X, SBOMB_SPREAD_Y));
		bullets[1] = unique_ptr<Obj_EnemyBullet_SBomb_Phase2>(new Obj_EnemyBullet_SBomb_Phase2(x, y, Z_INDEX_ANIMATION, _bypassPlatformID, 0, SBOMB_SPREAD_Y));
		bullets[2] = unique_ptr<Obj_EnemyBullet_SBomb_Phase2>(new Obj_EnemyBullet_SBomb_Phase2(x, y, Z_INDEX_ANIMATION, _bypassPlatformID, SBOMB_SPREAD_X, SBOMB_SPREAD_Y));
		for (int i = 0; i < 3; i++)
		{
			scene->add_object(move(bullets[i]));
		}
	}
}

bool Obj_EnemyBullet_SBomb_Phase2::CollideBlockerCondition(DWORD dt, PCOLLISIONEVENT e)
{
	// if collide object is platform or moving stone
	if (!_explodeFlag && (dynamic_cast<Game_Platform*>(e->obj)
		|| dynamic_cast<Obj_MovingStone*>(e->obj)))
	{
		// old platform
		if (_firstBypassPlatform == e->obj->id() || _bypassPlatformID == e->obj->id())
		{
			return false;
		}
		// new platform
		else if (_bypassPlatformID < 0)
		{
			_bypassPlatformID = e->obj->id();
			return false;
		}
		else
		{
			Execute_ExplodingEffect();
			return true;
		}
	}

	if (dynamic_cast<Game_Terrain*>(e->obj))
	{
		return false;
	}

	return true;
}

void Obj_EnemyBullet_SBomb_Phase2::Execute_BeforeDelete()
{
	if (_explodeFlag)
	{
		Create_ExplodeAnimation();
	}
}