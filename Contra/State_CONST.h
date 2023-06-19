#pragma once

constexpr auto STATE_IDLE = 0;
constexpr auto STATE_WALK = 1;
constexpr auto STATE_JUMP = 2;
constexpr auto STATE_SWIM = 3;
constexpr auto STATE_LIE = 4;
constexpr auto STATE_FALL = 5;
constexpr auto STATE_DIVE = 6;
constexpr auto STATE_DIE = 7;
constexpr auto STATE_ACTIVE = 10;
constexpr auto STATE_EMERGE = 11;
constexpr auto STATE_HIDE = 12;
constexpr auto STATE_OBJ_STANDBY = 20;
constexpr auto STATE_OBJ_ACTIVE = 21;
constexpr auto STATE_OBJ_HIDE = 22;
constexpr auto STATE_OBJ_EMERGE = 23;
enum TURRET_DIR
{
	DIR_1_OCLOCK = 10,
	DIR_2_OCLOCK,
	DIR_3_OCLOCK,
	DIR_4_OCLOCK,
	DIR_5_OCLOCK,
	DIR_6_OCLOCK,
	DIR_7_OCLOCK,
	DIR_8_OCLOCK,
	DIR_9_OCLOCK,
	DIR_10_OCLOCK,
	DIR_11_OCLOCK,
	DIR_12_OCLOCK,
	DIR_OCLOCK

};