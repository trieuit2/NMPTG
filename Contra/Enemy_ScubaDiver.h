#pragma once
#include "Game_StationEnemy.h"
#include "Equip_EnemyGun_ScubaDiver.h"

#define SCUBADIVER_BASE_WIDTH 16
#define SCUBADIVER_BASE_HEIGHT 16
#define SCUBADIVER_HIDE_WIDTH 16
#define SCUBADIVER_HIDE_HEIGHT 10
#define SCUBADIVER_HIDING_INTERVAL 2000
#define SCUBADIVER_ATTACK_RANGE 20

class Enemy_ScubaDiver : public Game_StationEnemy
{
private:
	void UpdateState() override;
	void UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects = NULL) override;
	DWORD _waitToChangeState = SCUBADIVER_HIDING_INTERVAL;
	void Cleaning() override { Game_StationEnemy::Cleaning(); }
public:
	Enemy_ScubaDiver(float x, float y, int z) : Game_StationEnemy(x, y, z, SCUBADIVER_BASE_WIDTH, SCUBADIVER_BASE_HEIGHT)
	{
		_weapon = new Equip_EnemyGun_ScubaDiver();
		_gravity = false;
		_faceLeft = false;
	}
	~Enemy_ScubaDiver() {
		Game_StationEnemy::~Game_StationEnemy();
		Cleaning();
	};

	void Shoot(int DIR) override;

	void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override;
	int CharID() override;
	int EnemyType() override { return ENEMY_SOLDIER; }
	// When no collision has been detected (triggered by CCollision::Process)
	void OnNoCollision(DWORD dt) override { Game_StationEnemy::OnNoCollision(dt); }
	// When collision with an object has been detected (triggered by CCollision::Process)
	void OnCollisionWith(PCOLLISIONEVENT e) override { Game_StationEnemy::OnCollisionWith(e); }

	void GetCustomSize(int state, int& width, int& height) override;
	void Execute_DieAction() override;
	void Execute_BeforeDelete() override;
	virtual int RewardScore() override { return 500; };
};

