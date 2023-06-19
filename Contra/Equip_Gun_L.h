#pragma once
#include "Equip_PlayerGunBase.h"
#include "Obj_Bullet_L.h"

#define EQUIP_GUN_L_MAX_ID 20

class Equip_Gun_L : public Equip_PlayerGunBase
{
private:
	BYTE _CurrentWaveID = 0;
public:
	Equip_Gun_L()
	{
		_isAuto = false;
		_FireRate = 120;
		_reloadTime = 0;
		_maxAmmo = 0;
		_ammo = _maxAmmo;
	}
	int GunID() override { return GUN_L; }
	BYTE CurrentWaveID() { return _CurrentWaveID; }
	void Fire(float& x, float& y, float& vx, float& vy, bool type = false) override;
	void Fire(float& x, float& y, int DIR) override;
};

