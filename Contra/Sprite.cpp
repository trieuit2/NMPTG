#include "Sprite.h"
#include "ScreenManager.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPTEXTURE tex,bool isMirror)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;

	float texWidth = (float)tex->getWidth();
	float texHeight = (float)tex->getHeight();

	// Set the sprite’s shader resource view
	sprite.pTexture = tex->getShaderResourceView();

	sprite.TexCoord.x = this->left / texWidth;
	sprite.TexCoord.y = this->top / texHeight;

	int spriteWidth = (this->right - this->left + 1);
	int spriteHeight = (this->bottom - this->top + 1);

	sprite.TexSize.x = spriteWidth / texWidth;
	sprite.TexSize.y = spriteHeight / texHeight;

	sprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	sprite.TextureIndex = 0;

	D3DXMatrixScaling(&this->matScaling, (FLOAT)spriteWidth, (FLOAT)spriteHeight, 1.0f);
	if (isMirror)
	{
		D3DXMATRIX matTranslate;
		D3DXMatrixScaling(&sprite.matWorld, (float)(right - left + 1), (float)(bottom - top + 1), 1.0f);

		// Flip the sprite from right to left
		sprite.TexCoord.x = right / texWidth; // set the right edge of the sprite as the left edge of the flipped sprite
		sprite.TexSize.x *= -1.0f; // invert the texture size along the x-axis to flip horizontally
		D3DXMatrixScaling(&sprite.matWorld, -1.0f * (float)(right - left + 1), (float)(bottom - top + 1), 1.0f); // invert the scaling matrix along the x-axis to flip horizontally
		D3DXMatrixTranslation(&matTranslate, (float)(right - left + 1), 0.0f, 0.0f); // translate the sprite to the right edge of the original sprite
		D3DXMatrixMultiply(&sprite.matWorld, &sprite.matWorld, &matTranslate); // apply the translation matrix
	}
}

void CSprite::Draw(float x, float y, BYTE RenderMode)
{	
	CGame* g = CGame::GetInstance();

	Game_Screen* screen = ScreenManager::GetInstance()->Screen();

	D3DXMATRIX matTranslation;
	
	screen->Convert_WorldPos_to_ScreenPos(x, y);

	float _width, _height;
	getWH(_width, _height);
	_width = round(_width);
	_height = round(_height);
	if (RenderMode == RENDER_MODE_TOP_LEFT)
	{
		x = ((x - _width / 2.0f));
		y = ((y - _height / 2.0f));
	}

	x = floorf(x);
	y = floorf(y);

	D3DXMatrixTranslation(&matTranslation, x,g->GetBackBufferHeight() - y, 0.1f);
	D3DXMATRIX matScaling;

	D3DXMatrixScaling(&matScaling, _width, _height, 1.0f);
	this->sprite.matWorld = (matScaling * matTranslation);

	g->GetSpriteHandler()->DrawSpritesImmediate(&sprite, 1, 0, 0);
}
void CSprite::DrawOnScreen(float x, float y, int width, int height, BYTE RenderMode)
{

}
void CSprite::DrawOnScreen(float x, float y, BYTE RenderMode,float ratiox,float ratioy)
{

	CGame* g = CGame::GetInstance();

	D3DXMATRIX matTranslation;

	float _width, _height;
	getWH(_width, _height);
	_width = _width / ratiox;
	_height = _height / ratioy;

	if (RenderMode == RENDER_MODE_TOP_LEFT)
	{
		x = x - _width / 2.0f;
		y = y - _height / 2.0f;
	}

	x = floor(x);
	y = floor(y);

	D3DXMatrixTranslation(&matTranslation, x, round(g->GetBackBufferHeight()) - y, 0.1f);
	D3DXMATRIX matScaling;

	D3DXMatrixScaling(&matScaling, _width, _height, 1.0f);
	this->sprite.matWorld = (matScaling * matTranslation);
	//this->sprite.matWorld = (this->matScaling * matTranslation);
	g->GetSpriteHandler()->DrawSpritesImmediate(&sprite, 1, 0, 0);
}

void CSprite::getAll(int& id, int& left, int& top, int& right, int& bottom, LPTEXTURE& tex)
{
	id = this->id;
	left = this->left;
	top = this->top;
	right = this->right;
	bottom = this->bottom;
	tex = texture;
}

