#include "Equip_PlayerGunBase.h"
#include "GameManager.h"
float* Equip_PlayerGunBase::modifier = &(GameManager::GetInstance()->Speed_Upgrade());

DWORD Equip_PlayerGunBase::FireRate()
{
	return DWORD(Equip_GunBase::FireRate() / (*modifier));
}
