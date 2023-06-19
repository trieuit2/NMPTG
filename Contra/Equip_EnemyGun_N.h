#pragma once
#include "Equip_GunBase.h"
class Equip_EnemyGun_N : public Equip_GunBase
{
	private:
	public:
		Equip_EnemyGun_N()
		{
			_isAuto = false;
			_FireRate = 180;
			_reloadTime = 600;
			_maxAmmo = 2;
		}

		void Fire(float& x, float& y, float& vx, float& vy, bool type = false) override;
		void Fire(float& x, float& y, int DIR) override;
};

