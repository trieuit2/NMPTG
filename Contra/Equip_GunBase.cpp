#include "Equip_GunBase.h"


DWORD Equip_GunBase::FireRate()
{
	if (_maxAmmo <= 0)
		return _FireRate;
	if (_ammo > 1)
	{
		_ammo--;
		return _FireRate;
	}
	else
	{
		_ammo = _maxAmmo;
		return _reloadTime ;
	}
}