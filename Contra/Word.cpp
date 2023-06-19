#include "Word.h"

namespace WORDSPRITE

{
	
	enum
	{
		A_SPRITE = 1400001,
		B_SPRITE,
		C_SPRITE,
		D_SPRITE,
		E_SPRITE,
		F_SPRITE,
		G_SPRITE,
		H_SPRITE,
		I_SPRITE,
		J_SPRITE,
		K_SPRITE,
		L_SPRITE,
		M_SPRITE,
		N_SPRITE,
		O_SPRITE,
		P_SPRITE,
		Q_SPRITE,
		R_SPRITE,
		S_SPRITE,
		T_SPRITE,
		U_SPRITE,
		V_SPRITE,
		W_SPRITE,
		X_SPRITE,
		Y_SPRITE,
		Z_SPRITE,
		SPRITE_0,
		SPRITE_1,
		SPRITE_2,
		SPRITE_3,
		SPRITE_4,
		SPRITE_5,
		SPRITE_6,
		SPRITE_7,
		SPRITE_8,
		SPRITE_9,
		SPRITE_DOT,
		SPRITE_COMA,
		SPRITE_QUOTE_LEFT,
		SPRITE_QUOTE_RIGHT,
		SPRITE_QUOTE_RIGHT_2,
		SPRITE_QUOTE_RIGHT_SINGLE,
		SPRITE_QUESTION_MARK,
		SPRITE_EX_MARK,
		SPRITE_DASH_DOWN,
		SPRITE_DASH_MIDDLE,
		SPRITE_COLON,
		SPRITE_SEMI_COLON,
		SPRITE_CPRIGHT
	};
	Game_Picture createNumber(int number, float screenX, float screenY, int z)
	{
		int spriteID = getNumberSpriteID(number);
		return Game_Picture(screenX,screenY,z,spriteID);
	}
	int getNumberSpriteID(int number)
	{
		return number + SPRITE_0;
	}
	/*int getCharcaterSpriteID(const wchar_t& a)
	{
		number=
		return A_SPRITE + static_cast<int>(a)-97;
	}*/
	int getCharacterSpriteID(int number)
	{
		if (number >= 97)
			number = number - 97;
		if (number >= 65)
			number = number - 65;
		return number + A_SPRITE;
	}
}
