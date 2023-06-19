#pragma once
#include "Game_Character.h"
#include "Equip_Gun_N.h"
#include "Equip_Gun_M.h"
#include "Equip_Gun_S.h"
#include "Equip_Gun_L.h"
#include "Equip_Gun_F.h"
//#define KEY_UP 0
//#define KEY_DOWN 1
//#define KEY_LEFT 2
//#define KEY_RIGHT 3
//#define KEY_SHOOT 4
//#define KEY_JUMP 5

#define PLAYER_BASE_WIDTH 14
#define PLAYER_BASE_HEIGHT 28
#define PLAYER_JUMP_WIDTH 18
#define PLAYER_JUMP_HEIGHT 18
#define PLAYER_SWIM_WIDTH 18
#define PLAYER_SWIM_HEIGHT 8
#define PLAYER_LIE_WIDTH 20
#define PLAYER_LIE_HEIGHT 8
#define PLAYER_DIVE_WIDTH 18
#define PLAYER_DIVE_HEIGHT 8

#define PLAYER_IDLE_OFFSET_X 0
#define PLAYER_IDLE_OFFSET_Y 0
#define PLAYER_WALK_OFFSET_X 0
#define PLAYER_WALK_OFFSET_Y 0
#define PLAYER_JUMP_OFFSET_X 0
#define PLAYER_JUMP_OFFSET_Y 0
#define PLAYER_SWIM_OFFSET_X 0
#define PLAYER_SWIM_OFFSET_Y -4
#define PLAYER_FALL_OFFSET_X 0
#define PLAYER_FALL_OFFSET_Y 0
#define PLAYER_LIE_OFFSET_X 0
#define PLAYER_LIE_OFFSET_Y 10
#define PLAYER_DIVE_OFFSET_X 0
#define PLAYER_DIVE_OFFSET_Y -8
#define PLAYER_DIE_OFFSET_X 0
#define PLAYER_DIE_OFFSET_Y 0

// PARAM
#define PLAYER_REVIVE_INVINCIBLE_TIME 2000
#define PLAYER_WAIT_FOR_REVIVE_TIME 900
#define PLAYER_INVINCIBLE_ANI_INTERVAL 50
#define PLAYER_UPGRADE_B_TIME 20000
#define PLAYER_UPGRADE_B_ANI_INTERVAL 50 

class Game_Player : public Game_Character
{
	protected:
		bool _auto = false;

		// revive

		DWORD _revive_interval = 0;
		float _revive_pos_X = 0;
		float _revive_pos_Y = 0;

		// invincible after revive
		bool _havingInvinicble_effect = false;
		DWORD _invincible_interval = 0;
		bool _invincible_ani_flash = false;

		// upgrade B

		DWORD _upgradeB_interval = 0;
		bool _havingB_effect = false;
		bool _upgradeB_ani_flash = false;

		// functions

		void UpdateState();
		void KeyReleaseAll() override;
		void DieEvent();
		void PerformRevive();
	public:
		Game_Player(float x, float y, int z) : Game_Character(x, y, z, PLAYER_BASE_WIDTH, PLAYER_BASE_HEIGHT)
		{
			_moveSpd = 0.1f;
			_weapon = new Equip_Gun_N();
		}
		~Game_Player() { Cleaning(); }

		void SetAuto(bool b) { _auto = b; }
		bool IsAuto() { return _auto; }
		void _Render(int aniId, float x, float y) override;

		void Render() override;
		void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override;

		void KeyDownEventHandler(int KeyCode) override;
		void KeyUpEventHandler(int KeyCode) override;
		void KeyStateHandler(BYTE* state) override;

		//============================================================================================
		// INHERITED
		
		// Collision ON or OFF ? This can change depending on object's state. For example: die
		int IsCollidable() override { return 1; }
		// When no collision has been detected (triggered by CCollision::Process)
		void OnNoCollision(DWORD dt);
		// When collision with an object has been detected (triggered by CCollision::Process)
		void OnCollisionWith(PCOLLISIONEVENT e) override;

		int CharID();
		void GetCustomSize(int state, int& width, int& height) override;
		void GetSpriteOffset(int state, float& x, float& y) override;
		void Execute_DieAction() override;

		void Apply_UpgradeB(bool state);

protected:
	 void _startCharacterEffect(int _effect) override;
	 void _updateCharacterEffect(int _effect) override;
	 void _expireCharacterEffect(int _effect) override;
};

