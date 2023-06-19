#pragma once
//#include "debug.h"
//
#include "State_CONST.h"
#define DIR_TOP_LEFT 1
#define DIR_TOP 2
#define DIR_TOP_RIGHT 3
#define DIR_LEFT 4
#define DIR_RIGHT 6
#define DIR_BOTTOM_LEFT 7
#define DIR_BOTTOM 8
#define DIR_BOTTOM_RIGHT 9



using namespace std;

namespace BULLETHELPER
{
    void getSpawnCor(float& x, float& y, int CHAR_ID, int state, int& DIR);
};
