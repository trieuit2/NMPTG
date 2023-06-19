#pragma once

#include "Equip_PlayerGunBase.h"
#include "Obj_Bullet_N.h"

class Equip_Gun_N : public Equip_PlayerGunBase
{
	private:
	public:
		Equip_Gun_N()
		{
			_isAuto = false;
			_FireRate = 150;
			_reloadTime = 0;
			_maxAmmo = 0;
			_ammo = _maxAmmo;
		}
		int GunID() override { return GUN_N; }
		void Fire(float& x, float& y, float& vx, float& vy, bool type = false) override;
		void Fire(float& x, float& y, int DIR) override;
};

