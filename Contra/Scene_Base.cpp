#include "Scene_Base.h"
#include "Word.h"
#include "GameManager.h"
void Scene_Base::Render()
{
	RenderFILLER();
	RenderImagePhase();
}
void Scene_Base::RenderFILLER()
{
	float BG_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	CGame::GetInstance()->GetDirect3DDevice()->ClearRenderTargetView(CGame::GetInstance()->GetRenderTargetView(), BG_color);
}
void Scene_Base::RenderImagePhase()
{
	vector<Game_Picture*> RenderQueue;

	for (auto& pic : _images)
	{
		Game_Picture* obj = pic.second.get();

		if (obj == NULL)
			continue;

		if (RenderQueue.size() == 0)
		{
			RenderQueue.push_back(obj);
			continue;
		}
		int j = int(RenderQueue.size());
		while (j > 0 && obj->z() < RenderQueue[j - 1]->z())
		{
			j--;
		}
		std::vector<Game_Picture*>::iterator it = RenderQueue.begin();
		RenderQueue.insert(it + j, obj);
	}

	float x, y;
	ScreenManager::GetInstance()->Screen()->GetCenterPoint(x, y);
	for (int i = 0; i < RenderQueue.size(); i++)
	{
		RenderQueue[i]->Render();
	}
}
void Scene_Base::_NextScene(int signal)
{
	GameManager::GetInstance()->ReceiveSignal(signal, this);
}
void Scene_Base::AddBlinkingDarkEffect(float x, float y, int width, int height, int& id,int ani_id)
{
	AddImage(x, y, id++, ani_id,32.0f/width,32.0f/height, RENDER_MODE_CENTER);
}
void Scene_Base::AddImage(float x, float y, int index, int spriteID, BYTE RenderMode)
{
	if (_images[index] != NULL)
	{
		_images[index].reset(new Game_Picture(x, y, index, spriteID, RenderMode));
	}
	else
	{
		unique_ptr <Game_Picture> image(new Game_Picture(x, y, index, spriteID, RenderMode));
		_images[index] = move(image);
	}
}
void Scene_Base::AddImage(float x, float y, int index, int spriteID, float ratiox, float ratioy, BYTE RenderMode)
{
	if (_images[index] != NULL)
	{
		_images[index].reset(new Game_Picture(x, y, index, spriteID, RenderMode,ratiox,ratioy));
	}
	else
	{
		unique_ptr <Game_Picture> image(new Game_Picture(x, y, index, spriteID, RenderMode,ratiox,ratioy));
		_images[index] = move(image);
	}
}
void Scene_Base::AddText(int& x, int& y, const wchar_t* str, int& index, float ratio, BYTE RenderMode)
{
	AddText(x, y, str, index, ratio, ratio, RenderMode);
}
void Scene_Base::AddText(int& x, int& y, const wchar_t* str, int& index, float ratiox,float ratioy, BYTE RenderMode)
{
int length = wcslen(str);
const int word_dis = 18/ratiox;
for (int i = 0; i < length; ++i)
{
    wchar_t currentChar = str[i];

    // Check if it is a space
    if (currentChar == L' ')
    {
		x = x + word_dis;
        continue; // Skip spaces
    }
    // Check if it is an alphabetic character
    else if (iswalpha(currentChar))
    {
        int asciiCode = static_cast<int>(currentChar);
		AddImage_Static(x = x + word_dis, y, index++, WORDSPRITE::getCharacterSpriteID(asciiCode),ratiox,ratioy, RenderMode);
    }
    // Check if it is a number
    else if (iswdigit(currentChar))
    {
        int numericValue = currentChar - L'0';
		AddImage_Static(x = x + word_dis, y, index++, WORDSPRITE::getNumberSpriteID(numericValue), ratiox,ratioy, RenderMode);
    }
}
}
void Scene_Base::AddNumber(int& x, int& y, int str, int& index, float ratio, BYTE RenderMode)
{
	AddNumber(x, y, str, index, ratio, ratio, RenderMode);
}
void Scene_Base::AddNumber(int& x, int& y, int str, int& index, float ratiox,float ratioy, BYTE RenderMode)
{
	AddText(x, y, to_wstring(str).c_str(), index, ratiox,ratioy, RenderMode);
}
void Scene_Base::AddImage_Static(float x, float y, int index, int spriteID, float ratio, BYTE RenderMode)
{
	AddImage_Static(x, y, index, spriteID, ratio, ratio, RenderMode);
}
void Scene_Base::AddImage_Static(float x, float y, int index, int spriteID,float ratiox, float ratioy, BYTE RenderMode)
{
	if (_images[index] != NULL)
	{
		_images[index].reset(new Game_Picture_Static(x, y, index, spriteID, RenderMode, ratiox, ratioy));
	}
	else
	{
		unique_ptr <Game_Picture_Static> image(new Game_Picture_Static(x, y, index, spriteID, RenderMode, ratiox, ratioy));
		_images[index] = move(image);
	}
}
