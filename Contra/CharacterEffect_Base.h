#pragma once
#include "Game_ObjectBase.h"
class Game_Character;
namespace CHARACTER_EFFECT
{
	enum CharacterEffect
	{
		BARRIER,
		DEFAULT_IMORTAL
	};
};
class CharacterEffect_Base
{
protected:
	Game_Character* target=NULL;
	int duration=0;
	bool _isInfinity=false;
	bool _isExpired=false;
	
	virtual void _update_Duration(DWORD& dt);
	virtual void _apply_DOT(DWORD& dt);
	virtual void _remove_Effect();
public:
	virtual void starting_Effect();
	CharacterEffect_Base(Game_Character* _target=NULL, int _duration=0, bool isInfinity=0);
	virtual void update(DWORD& dt);
	virtual void forceExpire();
	bool isExpired();
	int getDuration() { return duration; };
	virtual  int effectID() { return 0; };
	~CharacterEffect_Base() {};
	//CharacterEffect_Base() = default;
};
	
