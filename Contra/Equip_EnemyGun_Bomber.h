#pragma once
#include "Equip_EnemyGun_N.h"
class Equip_EnemyGun_Bomber : public Equip_EnemyGun_N
	{
	private:
	public:
		Equip_EnemyGun_Bomber()
		{
			_isAuto = false;
			_FireRate = 800;
			_reloadTime = 0;
			_maxAmmo = 0;
		}

		void Fire(float& x, float& y, float& vx, float& vy, bool type = false) override {}
		void Fire(float& x, float& y, int DIR) override;
};

