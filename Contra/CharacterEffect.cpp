#include "CharacterEffect.h"
#include "Game_Player.h"
using namespace CHARACTER_EFFECT; 
int CharacterEffect_Barrier::effectID()
{
	return BARRIER;
}

CharacterEffect_Barrier::CharacterEffect_Barrier(Game_Character* _target, int _duration, bool isInfinity) :CharacterEffect_IMMORTAL(_target, _duration, isInfinity)
{
}


void CharacterEffect_IMMORTAL::starting_Effect()
{
	target->IncImmortal();
}

void CharacterEffect_IMMORTAL::_remove_Effect()
{
	target->DecImmortal();
}

CharacterEffect_IMMORTAL::CharacterEffect_IMMORTAL(Game_Character* _target, int _duration, bool isInfinity) :CharacterEffect_Base(_target, _duration, isInfinity)
{

}

int CharacterEffect_IMMORTAL::effectID()
{
	return DEFAULT_IMORTAL;
}

void CHARACTER_EFFECT::applyEffect(Game_Character* _target, int _effect,int duration)
{
	CharacterEffect_Base* effect;
	bool infinity = (duration == -1);
	switch(_effect)
	{
	case DEFAULT_IMORTAL: effect = new CharacterEffect_IMMORTAL(_target, duration, infinity); break;
	case BARRIER:  effect = new CharacterEffect_Barrier(_target, duration, infinity); break;
	default:  effect = new CharacterEffect_IMMORTAL(_target, duration, infinity); break;
	}
	_target->addEffect(effect);
}
