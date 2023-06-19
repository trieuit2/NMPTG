#pragma once
#include "Equip_PlayerGunBase.h"
class Equip_Gun_M : public Equip_PlayerGunBase
{
	private:
	public:
		Equip_Gun_M()
		{
			_isAuto = true;
			_FireRate = 120;
			_reloadTime = 0;
			_maxAmmo = 0;
			_ammo = _maxAmmo;

		}
		int GunID() override { return GUN_R; }
		void Fire(float& x, float& y, float& vx, float& vy, bool type = false) override;
		void Fire(float& x, float& y, int DIR) override;
};

