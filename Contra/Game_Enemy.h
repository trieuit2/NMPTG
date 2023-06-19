#pragma once
#include "Game_Character.h"
#include "Enemies_ID.h"

#define ENEMY_SOLDIER 1
#define ENEMY_CONSTRUCTION 2
#define ENEMY_OBJECT 3

class Game_Enemy : public Game_Character
{
	protected:
		bool _BodyDamage = false;
		// If true, this enemy can block laser bullet
		bool _HardBody = false;
		DWORD _DieDelay = 150;
		void UpdateState() override;
		virtual void UpdateBehavior(DWORD dt, vector<Game_ObjectBase*>* coObjects = NULL);
		void KeyReleaseAll() override;
		void CreateDieAnimation(int aniID);
	public:
		Game_Enemy(float x, float y, int z, int width, int height) : Game_Character(x, y, z, width, height)
		{
			_moveSpd = 0.1f;
		}

		// GET & SET
		bool BodyDamage() { return _BodyDamage; }

		void Render() override;
		void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override;
		void KeyDownEventHandler(int KeyCode) override;
		void KeyUpEventHandler(int KeyCode) override;
		void KeyStateHandler(BYTE* state) override;
		virtual int EnemyType() { return 0; }
		void Execute_DieAction() override;

		//============================================================================================
		// INHERITED

		// Collision ON or OFF ? This can change depending on object's state. For example: die
		int IsCollidable() override { return 1; }
		// When no collision has been detected (triggered by CCollision::Process)
		void OnNoCollision(DWORD dt);
		// When collision with an object has been detected (triggered by CCollision::Process)
		void OnCollisionWith(PCOLLISIONEVENT e) override;
		// Sprite ID
		int CharID() override;

		void GetCustomSize(int state, int& width, int& height) override { Game_Character::GetCustomSize(state,width,height); }
};


