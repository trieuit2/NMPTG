#include "Obj_Upgrade.h"
#include "Equip_Gun_M.h"
#include "Scene_Battle.h"
#include "GameManager.h"
#include "CharacterEffect.h"

void Obj_Upgrade_M::applyUpgrade(Game_Character*target)
{
	target->ChangeWeapon(new Equip_Gun_M());
}

void Obj_Upgrade_B::applyUpgrade(Game_Character* target)
{
	if (dynamic_cast<Game_Player*>(target))
	{
		Game_Player *ptr=(Game_Player*)target;
		CHARACTER_EFFECT::applyEffect(ptr, CHARACTER_EFFECT::BARRIER, 20000);
	}
}

void Obj_Upgrade_F::applyUpgrade(Game_Character*target)
{
	target->ChangeWeapon(new Equip_Gun_F());
}

void Obj_Upgrade_S::applyUpgrade(Game_Character*target)
{
	target->ChangeWeapon(new Equip_Gun_S());
}

void Obj_Upgrade_L::applyUpgrade(Game_Character*target)
{
	target->ChangeWeapon(new Equip_Gun_L());
}
void Obj_Upgrade_R::applyUpgrade(Game_Character*target)
{
	GameManager::GetInstance()->add_Speed_Upgrade();
}


void UPGRADE::spawnUpgradeIcon(int ICONTYPE, float centerX, float centerY, bool FlyToLeft)
{
	if (ICONTYPE >= 97)
		ICONTYPE -= 97;
	if (ICONTYPE >= 65)
		ICONTYPE -= 65;
	int dir = FlyToLeft ? -1 : 1;
	Obj_UpgradeBase* rtn=NULL;
	switch (ICONTYPE)
	{
	case UP_B:
		rtn = new Obj_Upgrade_B(0, 0, Z_INDEX_ITEM, dir * UPGRADE_DEFAULT_FORCE_X, UPGRADE_DEFAULT_FORCE_Y);
		break;
	case UP_F:
		rtn = new Obj_Upgrade_F(0, 0, Z_INDEX_ITEM, dir * UPGRADE_DEFAULT_FORCE_X, UPGRADE_DEFAULT_FORCE_Y);
		break;
	case UP_L:
		rtn = new Obj_Upgrade_L(0, 0, Z_INDEX_ITEM, dir * UPGRADE_DEFAULT_FORCE_X, UPGRADE_DEFAULT_FORCE_Y);
		break;
	case UP_R:
		rtn = new Obj_Upgrade_R(0, 0, Z_INDEX_ITEM, dir * UPGRADE_DEFAULT_FORCE_X, UPGRADE_DEFAULT_FORCE_Y); 
		break;
	case UP_M:
		rtn = new Obj_Upgrade_M(0, 0, Z_INDEX_ITEM, dir * UPGRADE_DEFAULT_FORCE_X, UPGRADE_DEFAULT_FORCE_Y); 
		break;
	case UP_S:
		rtn = new Obj_Upgrade_S(0, 0, Z_INDEX_ITEM, dir * UPGRADE_DEFAULT_FORCE_X, UPGRADE_DEFAULT_FORCE_Y); 
		break;
	default:
		rtn = new Obj_Upgrade_R(0, 0, Z_INDEX_ITEM, dir * UPGRADE_DEFAULT_FORCE_X, UPGRADE_DEFAULT_FORCE_Y);
		break;
	}
	rtn->SetCenterPoint(centerX, centerY);
	unique_ptr<Obj_UpgradeBase> _rtn(rtn);
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	scene->add_object(move(_rtn));
}