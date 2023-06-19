#pragma once
#include "Game_SpecialObject.h"

#define FLAME_WIDTH 12
#define FLAME_HEIGHT 12
#define FLAME_CHANGE_DIR_INTERVAL 200

class Obj_Flame : public Game_SpecialObject
{
	private:
		float _maxRangeL = 0;
		float _maxRangeR = 0;
		bool _moveToLeft = false;
		DWORD _changeDir = 0;
		void UpdateState() override;
		void UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects = NULL) override;
	public:
		Obj_Flame(float x, float y, int z, float maxRangeL, float maxRangeR) : Game_SpecialObject(x, y, z, FLAME_WIDTH, FLAME_HEIGHT)
		{
			_moveSpd = 0.05f;
			_haveStandby = false;
			_BodyDamage = true;
			_faceLeft = true;
			_ghost = true;
			_lockFace = true;
			_gravity = true;
			if (_maxRangeL <= _maxRangeR)
			{
				_maxRangeL = maxRangeL;
				_maxRangeR = maxRangeR;
			}
			else
			{
				_maxRangeL = maxRangeR;
				_maxRangeR = maxRangeL;
			}

		}
		~Obj_Flame() {
			Game_SpecialObject::~Game_SpecialObject();
			Cleaning();
		};

		void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override;
		int CharID() override;
		// When no collision has been detected (triggered by CCollision::Process)
		void OnNoCollision(DWORD dt) override { Game_MovableObject::OnNoCollision(dt); }

		void Execute_DieAction() override {}
};

