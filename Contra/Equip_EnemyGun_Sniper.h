#pragma once
#include "Equip_EnemyGun_N.h"
class Equip_EnemyGun_Sniper : public Equip_EnemyGun_N
{
	private:
	public:
		Equip_EnemyGun_Sniper()
		{
			_isAuto = false;
			_FireRate = 500;
			_reloadTime = 1400;
			_maxAmmo = 3;
			_ammo = _maxAmmo;
		}

		void Fire(float& x, float& y, float& vx, float& vy, bool type = false) override { Equip_EnemyGun_N::Fire(x, y, vx, vy, type); }
		void Fire(float& x, float& y, int DIR) override { Equip_EnemyGun_N::Fire(x, y, DIR); }
};

