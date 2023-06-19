#pragma once
#include "Equip_EnemyGun_N.h"
class Equip_EnemyGun_Turret : public Equip_EnemyGun_N
{
	public:
		Equip_EnemyGun_Turret()
		{
			_isAuto = false;
			_FireRate = 1000;
			_reloadTime = 0;
			_maxAmmo = 0;
			_ammo = _maxAmmo;
		}

		void Fire(float& x, float& y, float& vx, float& vy, bool type = false) override { Equip_EnemyGun_N::Fire(x, y, vx, vy, type); }
		void Fire(float& x, float& y, int DIR) override;
};

