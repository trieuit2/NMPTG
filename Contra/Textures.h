#pragma once

#include <d3dx10.h>
#include "debug.h"
#include "Texture.h"

using namespace std;

/*
	Manage texture database
*/
class CTextures
{
	static CTextures* __instance;

	unordered_map<int, LPTEXTURE> textures;

public:
	CTextures();
	void Add(int id, LPCWSTR filePath);
	LPTEXTURE Get(unsigned int i);
	void Clear();

	static CTextures* GetInstance();
};