#pragma once

#include <d3d10.h>
#include <d3dx10.h>
#include <memory>
//
// Warpper class to simplify texture manipulation. See also CGame::LoadTexture
//
class CTexture
{
protected:
	ID3D10Texture2D* _tex=NULL;
	ID3D10ShaderResourceView* _rsview=NULL;
	int _width=-1;
	int _height=-1;
public:
	CTexture() = default;

	CTexture(ID3D10Texture2D* tex, ID3D10ShaderResourceView* rsview)
	{
		this->_tex = tex;
		this->_rsview = rsview;

		D3D10_TEXTURE2D_DESC desc;
		this->_tex->GetDesc(&desc);
		this->_width = desc.Width;
		this->_height = desc.Height;
	}

	ID3D10ShaderResourceView* getShaderResourceView() { return this->_rsview; }

	int getWidth() { return this->_width; }
	int getHeight() { return this->_height; }

	~CTexture()
	{
		if (_rsview != NULL) this->_rsview->Release();
		if (_tex != NULL) this->_tex->Release();
	}
};

typedef CTexture* LPTEXTURE;
