#pragma once
#include "Equip_EnemyGun_Turret.h"
class Equip_EnemyGun_Cannon : public Equip_EnemyGun_Turret
{
	public:
		Equip_EnemyGun_Cannon()
		{
			_isAuto = false;
			_FireRate = 200;
			_reloadTime = 1200;
			_maxAmmo = 3;
			_ammo = _maxAmmo;
		}
};

