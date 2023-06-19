#pragma once
#include "Game_SpecialObject.h"
#include "Game_Character.h"
namespace UPGRADE
{
#define UPGRADE_ICON_WIDTH 23
#define UPGRADE_ICON_HEIGHT 12
}
using namespace UPGRADE;
class Obj_UpgradeBase : public Game_SpecialObject
{
public:
    Obj_UpgradeBase(float x, float y, int z, float ForceX = 64, float ForceY = 48) : Game_SpecialObject(x, y, z, UPGRADE_ICON_WIDTH, UPGRADE_ICON_HEIGHT)
    {
        _moveSpd = 0.05f;
        _DieDelay = 0;
        _ForceX = ForceX;
        _ForceY = ForceY;
        _gravity = true;
        _ghost = true;
    }
    void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override;
    void Render() override;
    void OnCollisionWith(PCOLLISIONEVENT e) override;
    virtual void applyUpgrade(Game_Character*target) {}
};

