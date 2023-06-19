#pragma once
#include "Equip_GunBase.h"
class Equip_PlayerGunBase :
    public Equip_GunBase
{
    static float* modifier;
public:
    Equip_PlayerGunBase() :Equip_GunBase() { };
    virtual DWORD FireRate() override;

};

