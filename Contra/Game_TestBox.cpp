#include "Game_TestBox.h"

void Game_TestBox::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	_collisionList.clear();
	Game_Collision::GetInstance()->Process(this, dt, coObjects);
}

void Game_TestBox::OnNoCollision(DWORD dt)
{

}

void Game_TestBox::OnCollisionWith(PCOLLISIONEVENT e)
{
	PCOLLISIONEVENT clone = new Game_CollisionEvent(*e);
	_collisionList.push_back(clone);
}