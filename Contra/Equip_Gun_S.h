#pragma once
#include "Equip_PlayerGunBase.h"
#include "Obj_Bullet_S.h"

#define EQUIP_GUN_S_MAX_BULLETS_EXIST 10

class Equip_Gun_S : public Equip_PlayerGunBase
{
	private:
		UINT _TotalShooted = 0;
		int CanShoot()
		{
			return EQUIP_GUN_S_MAX_BULLETS_EXIST - _TotalShooted;
		}
	public:
		Equip_Gun_S()
		{
			_isAuto = false;
			_FireRate = 160;
			_reloadTime = 0;
			_maxAmmo = 0;
			_ammo = _maxAmmo;
		}
		int GunID() override { return GUN_S; }
		void Recharge_Bullet() { _TotalShooted -= 1; }
		void Use_Bullet() { _TotalShooted += 1; }
		void Fire(float& x, float& y, float& vx, float& vy, bool type = false) override;
		void Fire(float& x, float& y, int DIR) override;
};

