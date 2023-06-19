#include "Obj_Bullet_S.h"
#include "Equip_Gun_S.h"

void Obj_Bullet_S::Init()
{
	_owner->Use_Bullet();
	_moveSpd = 0.25f;
	_OwnerID = B_OWNER_PLAYER;
	_Damage = 3;
	_SpriteId = CONTRA_BULLET_ANI_BULLET_S;
}

void Obj_Bullet_S::DeleteThis()
{
	if (_removeFlag)
		return;
	_removeFlag = true;
	_owner->Recharge_Bullet();
	Game_Bullet::DeleteThis();
}