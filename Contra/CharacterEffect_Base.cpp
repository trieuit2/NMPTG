#include "CharacterEffect_Base.h"
#include "Game_Character.h"
CharacterEffect_Base::CharacterEffect_Base(Game_Character* _target, int _duration,bool isInfinity)
{
	target = _target;
	duration = _duration;
	starting_Effect();
	_isInfinity = isInfinity;
}
bool CharacterEffect_Base::isExpired()
{
	return _isExpired;
}

void CharacterEffect_Base::update(DWORD& dt)
{
	_apply_DOT(dt);
	_update_Duration(dt);
}
void CharacterEffect_Base::_update_Duration(DWORD& dt)
{
	if (_isInfinity)
		return;
	duration -= dt;
	if (duration <= 0)
		forceExpire();
}

void CharacterEffect_Base::forceExpire()
{
	_remove_Effect();
	_isExpired = true;

}


void CharacterEffect_Base::starting_Effect()
{
}

void CharacterEffect_Base::_apply_DOT(DWORD& dt)
{
}

void CharacterEffect_Base::_remove_Effect()
{
}




