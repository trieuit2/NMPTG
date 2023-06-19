#include "Game_Character.h"
#include "Game_Water.h"
#include "Game_Platform.h"
#include "Game_Collision.h"
#include "Game_TestBox.h"
#include "Scene_Battle.h"
#include "Game_DeadlyBlock.h"
#include "Obj_MovingStone.h"
#include "CharacterEffect_Base.h"
#include "MusicManager.h"
void Game_Character::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	_handle_CharacterEffect(dt);
	Game_MovableObject::Update(dt, coObjects);

	if (_GunReloadInterval > dt)
	{
		_GunReloadInterval -= dt;
	}
	else if (_GunReloadInterval > 0 && _GunReloadInterval < dt)
	{
		_GunReloadInterval = 0;
	}
	if (!_moveFlag)
		_vx = 0;
	_moveFlag = false;
	ApplyExternalForce();
}

void Game_Character::OnNoCollision(DWORD dt)
{
	Game_MovableObject::OnNoCollision(dt);
}

#define CLIMP_UP_TERRAIN_SCALE_Y_X 0.25f

void Game_Character::OnCollisionWith(PCOLLISIONEVENT e)
{
	Game_MovableObject::OnCollisionWith(e);

	// on ground state already handled, only used to check swim state
	if (dynamic_cast<Game_Terrain*>(e->obj) && !dynamic_cast<Game_Water*>(e->obj) && e->ny > 0)
	{
		_swim = false;
		return;
	}
	else if (dynamic_cast<Game_Water*>(e->obj))
	{
		_swim = true;
		return;
	}

	if (dynamic_cast<Obj_MovingStone*>(e->obj)
		&& footerY() >= e->obj->y()
		) {
		float vx, vy;
		e->obj->GetSpeed(vx, vy);
		_external_vx += vx;
		_external_vy += vy;
		_swim = false;
		return;
	}

	// climb up
	if (e->nx != 0 && _onGround && dynamic_cast<Game_Terrain*>(e->obj)
		&& e->obj->y() - footerY() <= CHARACTER_JUMP_ON_HEIGHT)
	{
		// character is under water
		teleport(_x, e->obj->y() + _height + CHARACTER_JUMP_ON_HEIGHT / 3.0f);
		float forceXValue = abs(e->obj->y() - footerY()) / CLIMP_UP_TERRAIN_SCALE_Y_X;
		if (e->nx < 0)
		{
			_ForceX = forceXValue;
		}
		else
		{
			_ForceX = -forceXValue;
		}
	}
}

void Game_Character::Shoot(int DIR)
{
	if (_weapon == NULL || _GunReloadInterval > 0)
		return;
	float x, y;
	GetCenterPoint(x, y);
	BULLETHELPER::getSpawnCor(x, y,CharID(),Sprite_ActID(), DIR);
	
	/* GET OFFSET
	int dir = DIR_TOP;
	x += _spawnBulletHelper[dir][X];
	y += _spawnBulletHelper[dir][Y];
	*/

	_GunReloadInterval = _weapon->FireRate();
	_weapon->Fire(x, y, DIR);
}

void Game_Character::Shoot(float x, float y)
{
	if (_weapon == NULL || _GunReloadInterval > 0)
		return;
	float cx, cy;
	GetCenterPoint(cx, cy);

	/* GET OFFSET
	int dir = DIR_TOP;
	x += _spawnBulletHelper[dir][X];
	y += _spawnBulletHelper[dir][Y];
	*/

	_GunReloadInterval = _weapon->FireRate();
	_weapon->Fire(cx, cy, x, y, GUN_SPAWNMODE_TARGETPOS);
}

void Game_Character::Execute_DieAction()
{
	Game_MovableObject::Execute_DieAction();
	playSFXexplode();
}

int Game_Character::Sprite_ActID()
{
	if(_state.get()==NULL)
		return 0;
	else
	{
		return _state.get()->CurrentActID();
	}
}

void Game_Character::moveLeft()
{
	Game_MovableObject::moveLeft();
	_moveFlag = true;
}

void Game_Character::moveRight()
{
	Game_MovableObject::moveRight();
	_moveFlag = true;
}

void Game_Character::jumpDown()
{
	unique_ptr<Game_TestBox>testbox(new Game_TestBox(_x, _y - _height - 12, _z, _width, 8, 0, 0));
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());

	vector<int> id_list = ScreenManager::GetInstance()->Screen()->Get_ObjectsID_InsideScreen(scene->spatial.get(), GET_OBJECTS_RANGE);
	vector<PGAMEOBJECT>* coObjects = scene->getObjectById(id_list);

	bool canJumpDown = false;

	// Make testbox move down
	testbox->SetSpeed(0, -scene->MapWidth());
	testbox->Update(1, coObjects);
	// Get Collisions and handle them.
	vector<PCOLLISIONEVENT>* coEvents = testbox->GetCollisionList();
	for (int i = 0; i < coEvents->size(); i++)
	{
		PCOLLISIONEVENT e = coEvents->at(i);
		//Check if under player have any terrain
		if (dynamic_cast<Game_DeadlyBlock*>(e->obj) || dynamic_cast<Game_SweeperBlock*>(e->obj))
		{
			canJumpDown = false;
			break;
		}

		if (dynamic_cast<Game_Platform*>(e->obj)
			|| dynamic_cast<Game_Blocker*>(e->obj)
			|| dynamic_cast<Game_Water*>(e->obj))
		{
			canJumpDown = true;
			break;
		}
	}
	if (canJumpDown)
		_jumpDown = true;
	else
		_jumpDown = false;
}

void Game_Character::AddAction(int KeyCode1, int KeyCode2)
{
	pair<int, int> p(KeyCode1,KeyCode2);
	_ActionQueue.push_back(p);
}


void Game_Character::ExecuteAction()
{
	if (_ActionQueue.size() == 0)
	{
		KeyReleaseAll();
		return;
	}

	pair<int,int> action = (_ActionQueue[0]);
	if (action.first == DIK_PAUSE)
	{
		KeyReleaseAll();
		if (action.second > 1)
			_ActionQueue[0].second--;
		else 
			_ActionQueue.erase(_ActionQueue.begin());
		return;
	}

	_ActionQueue.erase(_ActionQueue.begin());
	if (action.first == -1)
	{
		KeyReleaseAll();
		return;
	}
	KeyDownEventHandler(action.first);
	if (action.second != -1)
		KeyDownEventHandler(action.second);
}

void Game_Character::ResetStateParams()
{
	Game_MovableObject::ResetStateParams();
}

Game_Character::Game_Character(float x, float y, int z, int width, int height) : Game_MovableObject(x, y, z, width, height)
{
	_needScanCollision = true;
}

void Game_Character::Cleaning()
{
	_ActionQueue.clear();
	delete _weapon;
	Game_MovableObject::Cleaning();
}



void Game_Character::_addtoEffectList(unique_ptr<CharacterEffect_Base>&& _effect)
{
	int type = _effect.get()->effectID();
	_effect.get()->starting_Effect();
	if (_effect_lists.find(type) != _effect_lists.end())
	{
		_expireCharacterEffect(type);
		_effect_lists[type]->forceExpire();
	}
	_effect_lists[type] = move(_effect);
}

void Game_Character::_cleanEffect()
{
	for (auto i = _effect_lists.begin(); i != _effect_lists.end();) {
		auto* ptr = i->second.get();
		_expireCharacterEffect(ptr->effectID());
		i = _effect_lists.erase(i);
		ptr = nullptr;
	}
}

void Game_Character::_handle_CharacterEffect(DWORD& dt)
{
	for (auto i = _effect_lists.begin(); i != _effect_lists.end();) {
		auto* ptr = i->second.get();
		if (ptr->isExpired()) {
			_expireCharacterEffect(ptr->effectID());
			i = _effect_lists.erase(i);
			ptr = nullptr;
			continue;
		}
		++i;
	}
	for (auto& i : _effect_lists)
	{
		i.second.get()->update(dt);
	}

}

void Game_Character::addEffect(CharacterEffect_Base* _effect)
{
	int type = _effect->effectID();
	_addtoEffectList(move(unique_ptr<CharacterEffect_Base>(_effect)));
	_startCharacterEffect(type);
}

int Game_Character::getSFXCHANNEL()
{
	return CHANNEL_SFX_ENEMY;
}

int Game_Character::getSFXexplodeID()
{
	return -1;
}

int Game_Character::getSFXhitedID()
{
	return -1;
}

void Game_Character::playSFXexplode()
{
	SoundSystem::getInstance()->playSFX(getSFXexplodeID(), getSFXCHANNEL(), 0);
}

void Game_Character::playSFXhited()
{
	SoundSystem::getInstance()->playSFX(getSFXhitedID(), getSFXCHANNEL(), 0);
}
