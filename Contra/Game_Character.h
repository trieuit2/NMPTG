#pragma once
#include "Game_MovableObject.h"
#include "Equip_GunBase.h"
#include "spawnBulletHelper.h"
#include "CharacterEffect_Base.h"
//#include "Contra_GET_ANI.h"

#define CHARACTER_JUMP_ON_HEIGHT 12

using namespace std;

class Game_Character : public Game_MovableObject
{
protected:
	int _hp = 1;
	bool _jumpDown = false;
	bool _moveFlag = false;
	// Weapon
	Equip_GunBase* _weapon = NULL;
	DWORD _GunReloadInterval = 0;
	// Auto control
	vector<pair<int, int>> _ActionQueue; // save keycode list
	
	
	virtual void UpdateState() {}	
	virtual void KeyReleaseAll() {}
	void ExecuteAction();
	void ResetStateParams() override;

	void Cleaning() override;

public:
	//static unordered_map<int, vector<float>> _spawnBulletHelper;
	Game_Character(float x, float y, int z, int width, int height) ;	
	~Game_Character() { }
	//-------------------------------------------------------------------------------
	/// INHERITED

	// Get hitbox
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override { Game_ObjectBase::GetBoundingBox(left, top, right, bottom); }
	// Collision ON or OFF ? This can change depending on object's state. For example: die
	int IsCollidable() override { return 1; }
	// When no collision has been detected (triggered by CCollision::Process)
	void OnNoCollision(DWORD dt);
	// When collision with an object has been detected (triggered by CCollision::Process)
	void OnCollisionWith(PCOLLISIONEVENT e) override;
	// Is this object blocking other object? If YES, collision framework will automatically push the other object
	bool IsBlocking() override { return 0; }
	// Can this object ingore blocking object and move through it?
	// If YES, collision framework will skip this collision event.

	virtual bool IgnoreBlocking() { return 0; }
	// Key event handler
	virtual void KeyDownEventHandler(int KeyCode) override {}
	// Key event handler
	virtual void KeyUpEventHandler(int KeyCode) override {}



	void Update(DWORD dt) override { Game_MovableObject::Update(dt); }
	void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override;
	//-------------------------------------------------------------------------------

	// Character action
	virtual void Shoot(int DIR);
	//virtual void getBulletLoc(float& x, float& y);
	virtual void Shoot(float x, float y);
	virtual bool IsFullAutomaticGun() { return _weapon != NULL && _weapon->IsAuto();}
	void Execute_DieAction() override;
	int Sprite_ActID();
	void moveLeft() override;
	void moveRight() override;
	void jumpDown();
	
	void AddAction(int KeyCode1, int KeyCode2 = -1);
	bool Test_IfHaveAction() { return _ActionQueue.size() > 0; }
	// GET & SET

	int Hp() { return _hp; }
	void SetHp(int hp) { _hp = hp; }

	bool IsJumpDown() { return _jumpDown; }
	void SetJumpDown(bool b) { _jumpDown = b; }
	float GetMovementSpeed() { return _moveSpd; }
	virtual void GetCustomSize(int state, int& width, int& height) { width = _width; height = _height; }
	virtual void GetSpriteOffset(int state, float& x, float& y) { x = 0; y = 0; }
	virtual int CharID() { return -1; }
	int GunID() { return _weapon->GunID(); }
	void ChangeWeapon(Equip_GunBase* newWep)
	{
		if (_weapon != NULL)
			delete _weapon;
		_weapon = newWep;
	}
	virtual int RewardScore() { return 0; }

	//effect
protected:
	unordered_map<int, unique_ptr<CharacterEffect_Base>> _effect_lists;

	virtual void _startCharacterEffect(int _effect) {};
	virtual void _updateCharacterEffect(int _effect) {};
	virtual void _expireCharacterEffect(int _effect) {};
	void _addtoEffectList(unique_ptr<CharacterEffect_Base>&& _effect);
	void _cleanEffect();
public:
	void _handle_CharacterEffect(DWORD& dt);
	void addEffect(CharacterEffect_Base*);
	int getHP() { return _hp; }
	virtual int getSFXCHANNEL();
	virtual int getSFXexplodeID();
	virtual int getSFXhitedID();
	void playSFXexplode();
	void playSFXhited();
};





