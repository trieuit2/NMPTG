#pragma once
#include "Game_SpecialObject.h"

//#define BoxFlying_Radius 20
//#define BoxFlying_Speed 0.25f
//#define PI 3.14
//#define BoxFlying_ExpireTime 5000
#define FLYING_UP_BOX_RADIUS 20
#define FLYING_UP_BOX_ANGULAR_V_MULTIPLY 1.0f
#define FLYING_UPGRADEBOX_WIDTH 18
#define FLYING_UPGRADEBOX_HEIGHT 12
#define FLYING_UP_BOX_HORIZONAL 0
#define FLYING_UP_BOX_VERTICAL 1

class Obj_FlyingUpgradeBox : public Game_SpecialObject
{
    private:
        float _currentRad = 0;
        bool _trigger = false;
        int _flyingDir = 0;
        int _type = 0;
        float _baseX;
        float _baseY;
        void UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects = NULL) override;
    public:
        Obj_FlyingUpgradeBox(float x, float y, int z, int flyingDir, int type)
            : Game_SpecialObject(x, y, z, FLYING_UPGRADEBOX_WIDTH, FLYING_UPGRADEBOX_HEIGHT)
        {
            _flyingDir = flyingDir;
            _hp = 1;        
            _haveStandby = false;
            _SpriteId = 958890;
            _gravity = false;
            _moveSpd = 0.115f;
            _type = type;
            _baseX = x;
            _baseY = y;
            switch (_flyingDir)
            {
            case FLYING_UP_BOX_HORIZONAL:
                _ForceX = 9999;
                break;
            case FLYING_UP_BOX_VERTICAL:
                _ForceY = 9999;
                break;

            }
        }
        int CharID() override;
        void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects);
        void Render() override;
        int baseType() override { return TYPE_MOVABLE; }
        void Execute_BeforeDelete() override;
};

