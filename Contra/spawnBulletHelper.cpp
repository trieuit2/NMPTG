#include "spawnBulletHelper.h"
#include "State_Contra_Base.h"
#include "Contra_GET_ANI.h"
/*

    bool getContraCor(float& x, float& y,int&state,int&DIR)
    {


        switch (state)
        {
        case STATE_IDLE:
        case STATE_WALK:
        case STATE_JUMP:
        case STATE_SWIM:
        case STATE_FALL:
        case STATE_DIVE:
        case STATE_ACTIVE:
            switch (DIR)
            {
            case DIR_TOP_LEFT:
            case DIR_TOP:
            case DIR_TOP_RIGHT:
            case DIR_LEFT:
            case DIR_RIGHT:
            case DIR_BOTTOM_LEFT:
            case DIR_BOTTOM:
            case DIR_BOTTOM_RIGHT:
            default:
                break;
            }
            break;
        case STATE_LIE:
            break;
        default:

            return false;
            break;

        }
        return true;

    }
*/
namespace BULLETHELPER
{
    bool getTurretCor(float& x, float& y, int& DIR)
    {
        const float x_dis=13;
        const float y_dis=13;
        const float xxx_dis=7,xxy_dis=6;
        const float xyx_dis = 6, xyy_dis = 7;
        const float xy_dis=7;
        bool applyNegativeX = false;
        bool applyNegativeY = false;

        switch (DIR)
        {
        case DIR_2_OCLOCK: y *= -1;
        case DIR_4_OCLOCK: x *= -1;
        case DIR_8_OCLOCK: y *= -1;
        case DIR_10_OCLOCK:x *= -1*xxx_dis; y *= xxy_dis; break;

        case DIR_1_OCLOCK:  y *= -1;
        case DIR_5_OCLOCK:  x *= -1;
        case DIR_7_OCLOCK:  y *= -1;
        case DIR_11_OCLOCK: x *= -1 * xyx_dis; y *= xyy_dis; break;
        
        
        case DIR_3_OCLOCK: x = x_dis; y = 0; break;
        case DIR_6_OCLOCK: y = y_dis; x = 0; break;
        case DIR_9_OCLOCK: x = -x_dis; y = 0;break;
        case DIR_12_OCLOCK: x = 0; y = y_dis; break;
        default:
            x = 0;
            y = 0;
            return false;
        }
        return true;
    }
    bool getContraCor(float& x, float& y,int&state,int&DIR)
    {


        switch (state)
        {
        case STATE_IDLE:
            x = -6;
            y = 10;
            break;
        case STATE_JUMP:
        case STATE_SWIM:
        case STATE_FALL:
        case STATE_DIVE:
        case STATE_ACTIVE:
            switch (DIR)
            {
            case DIR_TOP_LEFT:      x = -1; y = 1; 
            case DIR_TOP_RIGHT:     x *= 7; y *= 7; break;

            case DIR_BOTTOM:        y =-1;
            case DIR_TOP:           y *= 10; break;

            case DIR_LEFT:          x = -1;
            case DIR_RIGHT:         x *= 12; y = 5; break;

            case DIR_BOTTOM_LEFT:   x = -1;
            case DIR_BOTTOM_RIGHT:  x *= 7; y *= 7; break;
            default:
                                    x = 0; y = 0;return false;
            }break;
        case STATE_LIE:
        {
            switch (DIR)
            {
            case DIR_LEFT:          x = -1;
            case DIR_RIGHT:         x *= 10; break;
            }
        }
            break;
        default:
            x = 0;
            y = 0;
            return false;
            break;

        }
        return true;
        
    }
    void getSpawnCor(float& _x, float& _y, int CHAR_ID, int state, int& DIR)
    {
        float x = 1,
            y = 1;

        switch (CHAR_ID)
        {
        case CHAR_CONTRA:
        case INFARY:
        case RED_GUNNER:
        case SNEAKY_SNIPER:
        case SNIPER:
            getContraCor(x, y, state, DIR);break;
        case TURRET_BASE:
        case CANNON:
        case TURRET: getTurretCor(x, y, DIR); break;

        default:getContraCor(x, y, state, DIR);
        }
        _x += x;
        _y += y;
    }
};