#include "Obj_EnemyBullet_Bomb.h"
#include "Game_Platform.h"
#include "ScreenManager.h"
#include "Contra_ANI_ID.h"

void Obj_EnemyBullet_Bomb::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	// always move up
	if (!_isDeleted && _explodeFlag)
	{
		DeleteThis();
		return;
	}
	Game_Bullet::Update(dt, coObjects);
	Game_Collision::GetInstance()->Process(this, dt, coObjects);
	ResetStateParams();
}

bool Obj_EnemyBullet_Bomb::CollideBlockerCondition(DWORD dt, PCOLLISIONEVENT e)
{
	// if collide object is platform or moving stone
	if (!_explodeFlag && (dynamic_cast<Game_Platform*>(e->obj)
		|| dynamic_cast<Obj_MovingStone*>(e->obj)))
	{
		return false;
	}
	return true;
}

void Obj_EnemyBullet_Bomb::OnCollisionWith(PCOLLISIONEVENT e)
{
	if (dynamic_cast<Game_Blocker*>(e->obj))
	{
		Execute_ExplodingEffect();
	}
}

void Obj_EnemyBullet_Bomb::Create_ExplodeAnimation()
{
	Scene_Battle* scene = (Scene_Battle*)ScreenManager::GetInstance()->Scene();
	float x, y;
	GetCenterPoint(x, y);
	unique_ptr<Game_Effect> explosion(new Game_Effect(x, y, Z_INDEX_ANIMATION, ANI_EXPLOSION_BULLET));
	scene->AddEffect(move(explosion));
}

void Obj_EnemyBullet_Bomb::Execute_ExplodingEffect()
{
	_explodeFlag = true;
}

void Obj_EnemyBullet_Bomb::Execute_BeforeDelete()
{
	if (_explodeFlag)
	{
		Create_ExplodeAnimation();
	}
}