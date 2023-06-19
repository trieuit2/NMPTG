#include "Obj_Bullet_F.h"

void Obj_Bullet_F::Update(DWORD dt)
{
	Game_Bullet::Update(dt);

	// No Update when just spawning
	if (_init)
	{
		_init = false;
		return;
	}

	_centerX += _vx * dt;
	_centerY += _vy * dt;

	// calc angular velocity
	float w = _moveSpd / _radius * BULLET_F_ANGULAR_V_MULTIPLY;

	if (_direct == BULLET_F_DIR_CLOCKWISE)
		_currentRad -= w * dt;
	else
		_currentRad += w * dt;

	// find destination
	float dvx, dvy;
	Rad_to_Vector(_currentRad, _radius, dvx, dvy);
	SetCenterPoint(_centerX + dvx, _centerY + dvy);
}

#define PI 3.14159265

void Obj_Bullet_F::SetupMovement()
{
	float cx, cy;
	GetCenterPoint(cx, cy);

	float rad = Vector_to_Rad(_vx, _vy);
	if (_vx != 0)
		_centerX = cx + cos(rad) * _radius;
	else
		_centerX = cx;
	if (_vy != 0)
		_centerY = cy + sin(rad) * _radius;
	else
		_centerY = cy;

	_currentRad = rad + PI;
}

float Obj_Bullet_F::Vector_to_Rad(float vx, float vy)
{
	if (vx < 0)
	{

	}
	return acos(vx/sqrt(vx*vx + vy*vy));
}

void Obj_Bullet_F::Rad_to_Vector(float rad, float radius, float& vx, float& vy)
{
	vx = cos(rad) * radius;
	vy = sin(rad) * radius;
}