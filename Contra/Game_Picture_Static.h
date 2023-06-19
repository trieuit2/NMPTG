#pragma once
#include "Game_Picture.h"
#include "debug.h"
#include "Animations.h"
class Game_Picture_Static :
    public Game_Picture
{
public:
    Game_Picture_Static(float screenX, float screenY, int z, int spriteID, BYTE RenderMode = RENDER_MODE_TOP_LEFT, float ratiox = 1, float ratioy = 1);
    void Render() override;
};

