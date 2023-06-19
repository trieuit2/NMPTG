#pragma once
#include "Game_SpecialObject.h"

#define STATION_UPGRADEBOX_WIDTH 32
#define STATION_UPGRADEBOX_HEIGHT 32
#define STATION_UP_HIDE_INTERVAL 2000
#define STATION_UP_SHOW_INTERVAL 2000

class Obj_StationUpgradeBox : public Game_SpecialObject
{
    private:
        int _type;
        DWORD _waitToChangeState = STATION_UP_HIDE_INTERVAL;
        void UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects = NULL) override;
    public:
        Obj_StationUpgradeBox(float x, float y, int z, bool FaceLeft, int type)
            : Game_SpecialObject(x, y, z, STATION_UPGRADEBOX_WIDTH, STATION_UPGRADEBOX_HEIGHT)
        {
            _faceLeft = FaceLeft;
            _type = type;
            _BodyDamage = false;
            _HardBody = true;
            _gravity = false;
            _hp = 10;
        }
        int CharID() override;
        void Execute_DieAction() override { Game_SpecialObject::Execute_DieAction(); }
        int RewardScore() override { return 500; }
        void Execute_BeforeDelete() override;
        void UpdateState() override;
        void Update(DWORD dt, vector<Game_ObjectBase*>* coObjects);

};

