#include "Obj_FlyingUpgradeBox.h"
#include <math.h>
#include "Scene_Battle.h"
#include "ScreenManager.h"
#include "Obj_Upgrade.h"

int Obj_FlyingUpgradeBox::CharID()
{
	return UP_BOX_FLYING;
}

void Obj_FlyingUpgradeBox::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	// Get Object's screen pos
	float sx = _x;
	float sy = _y;
	Game_Screen* screen = ScreenManager::GetInstance()->Screen();
	screen->Convert_WorldPos_to_ScreenPos(sx, sy);

	// Trigger condition
	if (!_trigger 
		&& ((_flyingDir == FLYING_UP_BOX_HORIZONAL && sx < 0)
			|| (_flyingDir == FLYING_UP_BOX_VERTICAL && sy > screen->height())))
		_trigger = true;

	if (!_trigger)
		return;

	// If out of camera zone
	if ((sx > screen->width() || sy < 0) && !_needRender)
	{
		DeleteThis();
	}

	Game_SpecialObject::Update(dt, coObjects);
}

void Obj_FlyingUpgradeBox::UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	//float x = (int)start_dt * BoxFlying_Speed / PI;
	//float y = sin(x * PI / BoxFlying_Radius / 2) * BoxFlying_Radius * 2;
	//_y = start_y + y;
	


	// angular velocity
	float w = _moveSpd / FLYING_UP_BOX_RADIUS * FLYING_UP_BOX_ANGULAR_V_MULTIPLY;
	_currentRad += w * dt;
	float newX = 0;
	float newY = 0;
	switch (_flyingDir)
	{
	case FLYING_UP_BOX_HORIZONAL:
		newY = sin(_currentRad) * FLYING_UP_BOX_RADIUS;
		teleport(TP_NO_CHANGE_X, _baseY + newY);
		break;
	case FLYING_UP_BOX_VERTICAL:
		newX = cos(_currentRad) * FLYING_UP_BOX_RADIUS;
		teleport(_baseX + newX, TP_NO_CHANGE_Y);
		break;

	}

}

void Obj_FlyingUpgradeBox::Execute_BeforeDelete()
{
	if (_die)
	{
		CreateDieAnimation(ANI_EXPLOSION_ARMY);
		float cx, cy;
		GetCenterPoint(cx, cy);
		UPGRADE::spawnUpgradeIcon(_type, cx, cy, 0);
	}
}

void Obj_FlyingUpgradeBox::Render()
{
	if (_trigger)
		Game_SpecialObject::Render();
}