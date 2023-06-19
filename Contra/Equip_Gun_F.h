#pragma once
#include "Equip_PlayerGunBase.h"
#include "Obj_Bullet_F.h"

class Equip_Gun_F : public Equip_PlayerGunBase
{
	private:
	public:
		Equip_Gun_F()
		{
			_isAuto = false;
			_FireRate = 250;
		}
		int GunID() override { return GUN_F; }
		void Fire(float& x, float& y, float& vx, float& vy, bool type = false) override;
		void Fire(float& x, float& y, int DIR) override;
};

