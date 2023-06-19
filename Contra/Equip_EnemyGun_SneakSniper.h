#pragma once
#include "Equip_EnemyGun_N.h"

class Equip_EnemyGun_SneakSniper : public Equip_EnemyGun_N
{
	private:
	public:
		Equip_EnemyGun_SneakSniper()
		{
			_isAuto = false;
			_FireRate = 500;
			_reloadTime = 0;
			_maxAmmo = 0;
			_ammo = _maxAmmo;
		}
};

