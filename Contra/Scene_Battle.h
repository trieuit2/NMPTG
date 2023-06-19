#pragma once

#include "Scene_Base.h"
#include "ScreenManager.h"
#include <string>
#include "debug.h"

// Terrains
#include "Game_Effect.h"
#include "Game_Blocker.h"
#include "Game_Terrain.h"
#include "Game_Platform.h"
#include "Game_Collision.h"
#include "Game_Water.h"
#include "Game_DeadlyBlock.h"
#include "Game_Bridge_S1.h"
#include "Game_SweeperBlock.h"

// Objects
#include "Game_Player.h"
#include "Enemy_RedGunner.h"
#include "Enemy_Infary.h"
#include "Game_Bullet.h"
#include "Enemy_Sniper.h"
#include "Enemy_SneakSniper.h"
#include "Enemy_ScubaDiver.h"
#include "Enemy_Turret.h"
#include "Enemy_Cannon.h"
#include "Spawner_Infary_Stage1.h"
#include "Spawner_FallingStone.h"
#include "Spawner_Infary_Stage3.h"
#include "Obj_MovingStone.h"
#include "Obj_Flame.h"
#include "Game_PlayerBlocker.h"
#include "Obj_FlyingUpgradeBox.h"
#include "Obj_StationUpgradeBox.h"
// Boss 1
#include "Enemy_Cannon_Base.h"
#include "Enemy_Base_Door.h"
#include "Obj_BossBase_S1.h"

// EventHandler
#include "StageEventHandler_Base.h"
// DEMO
#include "Spatial.h"
#include "QuadTree/QuadTree.h"
#include "MusicManager.h"

#include "Utils.h"
#include "STL_storage.h"
using namespace std;
#define UP_BLOCK 1
#define DOWN_BLOCK -1
#define BRIDGE_BLOCK 2
#define NOTHING 999

#define Z_INDEX_PLAYER 8
#define Z_INDEX_ENEMY 6
#define Z_INDEX_STATION 5
#define Z_INDEX_BULLET 7
#define Z_INDEX_BACKGROUND 1
#define Z_INDEX_ANIMATION 10
#define Z_INDEX_TERRAIN 2
#define Z_INDEX_ITEM 3

#define GET_OBJECTS_RANGE 1.4f

class Scene_Battle : public Scene_Base
{
	private:
		int _p1_id=-1;
		//int _p2_id=-1;
		unique_ptr<Game_Player> _p1 ;
		//Game_Player* _p2 = NULL;
		vector<unique_ptr<Game_Effect>> _effects;
		//vector<Game_ObjectBase*> _objects;
		unordered_map<int,unique_ptr<Game_ObjectBase>> __objects;
		int _mapWidth = 1;
		int _mapHeight = 1;

		// Stage controller
		StageEventHandler_Base* _controller = NULL;
		bool _massKilling = false;

	public:
		Scene_Battle();
		~Scene_Battle();
		//vector<Game_ObjectBase*>* objects() { return &_objects; }
		Game_Player* p1() { return dynamic_cast<Game_Player*>(__objects[_p1_id].get()); }
		void addPlayer1();
		//Game_Player* p2() { return dynamic_cast<Game_Player*>(__objects[_p2_id].get()); }
		//void addPlayer2();
		int MapWidth() { return _mapWidth; }
		int MapHeight() { return _mapHeight; }
		void SetMapSize(int width, int height) { _mapWidth = width; _mapHeight = height; }

		void AddEffect(unique_ptr<Game_Effect>&& obj);

		void Render() override;
		void Update(DWORD dt) override;
		void Load() override;
		void Unload() override;
		void MassKilling() { _massKilling = true; }
		//void Create_Stage_Demo();

		// Key event handler
		virtual void KeyDownEventHandler(int KeyCode) override;

		/// from this is protype
		void SetStageEventHandler(StageEventHandler_Base* handler)
		{
			if (_controller != NULL)
				delete _controller;
			_controller = handler;
		}
		StageEventHandler_Base* GetStageEventHandler() { return _controller; }

	private:
		int id_nth = 0;
		vector<int> id_recycle_bin;
		void _init_spatial();
		void _delete_spatial();
	public:
		//Spatial *spatial=NULL;
		unique_ptr<QuadTree> spatial;
		vector<int> getNearByIDwithWH(int x, int y, int width, int height);
		vector<int> getNearByID(int left, int bottom, int right, int top);
		//vector<int> getNearbyIDFast();
		
		Game_ObjectBase* getObjectByID(int id) { return __objects[id].get(); }
		vector<Game_ObjectBase*>* getObjectById(vector<int>& vtr);

		int add_object(unique_ptr<Game_ObjectBase>&& object);
		void delete_object(int id);
		//void delete_object(unique_ptr<Game_ObjectBase>& object);

		// from here is MAP SPATIAL
		void parseMap(string line);

		///spatial map
	protected:
		unordered_map<int, unordered_map<int, int>> map;
		//unordered_map<int, int> map_info;
		unordered_map<int, unique_ptr<CSprite>> map_sprite;
		LPTEXTURE _map_tex=NULL;
		unique_ptr<SpatialforTex>mapTexSpatial;
		void renderBG(float x, float y);
		void renderBG(int& x, int& y);
		int width, height, map_id;
	public:
		void _ParseSection_DICT(string line);
		void _ParseOBject(string line);
		void addMapPart( int partID, int x, int y);

		// Delete later
		void init_spatial() { _init_spatial(); }

private:
	static Scene_Battle* __instance;
	int curHP=0;
	void HUB_HP_handler();
public:
	static Scene_Battle* GetInstance();
	static Scene_Battle* GenInstance();

};

