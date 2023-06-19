#include "Game_Screen.h"
#include "QuadTree/QuadTree.h"
#include "Game_Bullet.h"

vector<int> Game_Screen::Get_ObjectsID_InsideScreen(QuadTree* spatial, float size)
{
	vector<int> objects;

	float l, t, r, b;
	GetBoundingBox(l, t, r, b);

	if (size <= 0)
	{
		DebugOut(L"[ERROR] size must be higher than 0.\n");
		return objects;
	}

	float width_modifier = (size * _width - _width) / 2.0f;
	float height_modifier = (size * _height - _height) / 2.0f;
	l -= width_modifier;
	r += width_modifier;
	t += height_modifier;
	b -= height_modifier;

	objects = spatial->search((int)l, (int)b,(int)r, (int)t, -100);
	return objects;
}

void Game_Screen::Convert_WorldPos_to_ScreenPos(float &x, float &y)
{
	x = x - _x;
	y = -(y - _y);
}

void Game_Screen::CheckObjectIfNeedRender(Game_ObjectBase* obj)
{
	float y, x;

	GetCenterPoint(x, y);
	//getNearByIDyx(y, x);
	if (obj->x() + obj->width() < _x
		|| obj->x() > _x + _width
		|| obj->y() < _y - _height
		|| obj->y() - obj->height() > _y)
	{
		obj->SetNeedRender(false);
		if (dynamic_cast<Game_Bullet*>(obj))
		{
			obj->DeleteThis();
		}
	}
	else {
		obj->SetNeedRender(true);
	}
}

void Game_Screen::DeleteThis()
{
	DebugOut(L"[INFO] This object can't be deleted\n");
}

void Game_Screen::forceDie()
{
	DebugOut(L"[INFO] This object can't be killed\n");
}