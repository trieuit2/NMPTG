#pragma once
#include "Obj_UpgradeBase.h"
#include "Contra_ANI_ID.h"

namespace UPGRADE
{
    #define UP_L 11
    #define UP_B 1
    #define UP_F 5
    #define UP_S 18
    #define UP_M 12
    #define UP_R 17

    #define UPGRADE_DEFAULT_FORCE_X 48
    #define UPGRADE_DEFAULT_FORCE_Y 48

    void spawnUpgradeIcon(int ICONTYPE, float centerX, float centerY, bool FlyToLeft);
}

class Obj_Upgrade_M : public Obj_UpgradeBase
{
    protected:
    public:
        Obj_Upgrade_M(float x, float y, int z, float ForceX, float ForceY) : Obj_UpgradeBase(x, y, z, ForceX, ForceY)
        {
            _SpriteId = ANI_UPGRADE_M;
        }
        void applyUpgrade(Game_Character*target) override;
    
};

class Obj_Upgrade_B : public Obj_UpgradeBase
{
    protected:

    public:
        Obj_Upgrade_B(float x, float y, int z, float ForceX, float ForceY) : Obj_UpgradeBase(x, y, z, ForceX, ForceY)
        {
            _SpriteId = ANI_UPGRADE_B;
        }
        void applyUpgrade(Game_Character*target) override;

};

class Obj_Upgrade_F : public Obj_UpgradeBase
{
protected:

public:
    Obj_Upgrade_F(float x, float y, int z, float ForceX, float ForceY) : Obj_UpgradeBase(x, y, z, ForceX, ForceY)
    {
        _SpriteId = ANI_UPGRADE_F;
    }
    void applyUpgrade(Game_Character*target) override;
};

class Obj_Upgrade_S : public Obj_UpgradeBase
{
protected:

public:
    Obj_Upgrade_S(float x, float y, int z, float ForceX, float ForceY) : Obj_UpgradeBase(x, y, z, ForceX, ForceY)
    {
        _SpriteId = ANI_UPGRADE_S;
    }
    void applyUpgrade(Game_Character*target) override;

};
class Obj_Upgrade_L : public Obj_UpgradeBase
{
protected:

public:
    Obj_Upgrade_L(float x, float y, int z, float ForceX, float ForceY) : Obj_UpgradeBase(x, y, z, ForceX, ForceY)
    {
        _SpriteId = ANI_UPGRADE_L;
    }
    void applyUpgrade(Game_Character*target) override;

};
class Obj_Upgrade_R : public Obj_UpgradeBase
{
protected:

public:
    Obj_Upgrade_R(float x, float y, int z, float ForceX, float ForceY) : Obj_UpgradeBase(x, y, z, ForceX, ForceY)
    {
        _SpriteId = ANI_UPGRADE_R;
    }
    void applyUpgrade(Game_Character*target) override;

};

