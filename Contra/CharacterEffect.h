#pragma once
#include "CharacterEffect_Base.h"
#include "Game_Character.h"


class CharacterEffect_IMMORTAL :
    public CharacterEffect_Base
{
protected:
    void starting_Effect() override;
    void _remove_Effect() override;
public:
    CharacterEffect_IMMORTAL(Game_Character* _target, int _duration=0, bool isInfinity=false);
    int effectID() override;
    

};

class CharacterEffect_Barrier :
    public CharacterEffect_IMMORTAL
{
protected:
public:
    int effectID() override;
    CharacterEffect_Barrier(Game_Character* _target, int _duration = 0, bool isInfinity = false);

};
namespace CHARACTER_EFFECT
{
    void applyEffect(Game_Character* _target, int _effect,int duration);
};