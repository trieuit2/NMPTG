#include "Scene_Battle.h"
#include "ScreenManager.h"
#include "Game_KeyInput.h"

#include <fstream>
using namespace std;
#define MAP_TEXU_WIDTH 16
#define MAP_TEXU_HEIGHT 8
float BG_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
Scene_Battle* Scene_Battle::__instance = NULL;
Scene_Battle::Scene_Battle(): Scene_Base() {
    height = 0; map_id = 0; width = 0;
}
//Scene_Battle* Scene_Battle::__instance = NULL;
Scene_Battle::~Scene_Battle()
{
    Unload();
}

void Scene_Battle::Render()
{
    Game_Screen* screen = ScreenManager::GetInstance()->Screen();

    vector<Game_ObjectBase*> RenderQueue;
    // layers
    for (int i = 0; i < _effects.size(); i++)
    {
        Game_ObjectBase* obj = _effects[i].get();
        if (obj->NeedRender() == false) {
            continue;
        }
        if (RenderQueue.size() == 0)
        {
            RenderQueue.push_back(obj);
            continue;
        }
        int j = int(RenderQueue.size());
        while (j > 0 && obj->z() < RenderQueue[j-1]->z())
        {
            j--;
        }
        std::vector<Game_ObjectBase*>::iterator it = RenderQueue.begin();
        RenderQueue.insert(it + j, obj);
    }
    // other game objects
    vector<int> id_list = screen->Get_ObjectsID_InsideScreen(spatial.get(), GET_OBJECTS_RANGE);
    for (auto&i :id_list)
    {
        Game_ObjectBase* obj = __objects[i].get();
        if (obj->NeedRender() == false) {
            continue;
        }
        if (RenderQueue.size() == 0)
        {
            RenderQueue.push_back(obj);
            continue;
        }
        int j =int( RenderQueue.size());
        while (j > 0 && obj->z() < RenderQueue[j-1]->z())
        {
            j--;
        }
        std::vector<Game_ObjectBase*>::iterator it = RenderQueue.begin();
        RenderQueue.insert(it + j, obj);
    }

    // Start render
    RenderFILLER();
   //CGame::GetInstance()->GetDirect3DDevice()->ClearRenderTargetView(CGame::GetInstance()->GetRenderTargetView(), BG_color);
    float x, y;
    ScreenManager::GetInstance()->Screen()->GetCenterPoint(x, y);
    renderBG(x, y);
    for (int i = 0; i < RenderQueue.size(); i++)
    {
        RenderQueue[i]->Render();
    }
    RenderImagePhase();
    // Render HUD
//if (_controller != NULL)
 //       _controller->RenderHUD();
}

void Scene_Battle::Update(DWORD dt)
{
    dt = min(dt, 40);

    if (!_isPlaying)
        return;

    Game_Screen* screen = ScreenManager::GetInstance()->Screen();

    // Event Handler
    if (_controller != NULL)
        _controller->Update(dt);

    // Map Update
    for (int i = 0; i < _effects.size(); i++)
    {
        Game_Effect* obj = _effects[i].get();
        screen->CheckObjectIfNeedRender(obj);
        obj->Update(dt);
    }

    if (__objects.empty())
        return;

    vector<int> id_list= screen->Get_ObjectsID_InsideScreen(spatial.get(), GET_OBJECTS_RANGE);
    vector<PGAMEOBJECT>* nearbyObject = getObjectById(id_list);
    //for (int i = 0; i < _objects.size(); i++)
    //float old_l, old_right, old_bottom, old_top,
    float   new_l, new_right, new_bottom, new_top;

    //vector<Game_ObjectBase*>* colObjects = objects();

    for(auto& i : id_list)
    {
        Game_ObjectBase* obj = __objects[i].get();

        if (obj->NeedScanCollision())
            obj->Update(dt, nearbyObject);
        else
            obj->Update(dt);
        if (_controller != NULL)
            _controller->SpecificUpdate(dt, obj);

        if (obj->baseType() != TYPE_STATIC)
        {
            obj->GetBoundingBox(new_l, new_top, new_right, new_bottom);
            spatial->update(i,(int)new_l, (int)new_bottom, (int)new_right, (int)new_top);
        }

        screen->CheckObjectIfNeedRender(obj);
    }

    // Terminate effects have Delete flag
    for (int i = 0; i < _effects.size(); i++)
    {
        if (_effects[i]->IsDeleted())
        {
            _effects[i]->Execute_BeforeDelete();
            std::vector<unique_ptr<Game_Effect>>::iterator it = _effects.begin();
            _effects.erase(it + i);
            i--;
        }
    }

    // If MassKilling flag turn on, kill all enemies
    if (_massKilling)
    {
        for (auto& i : id_list)
        {
            Game_ObjectBase* obj = __objects[i].get();
            if (dynamic_cast<Game_Enemy*>(obj))
            {
                Game_Enemy* enemy = (Game_Enemy*)obj;
                enemy->forceDie();
            }
            _massKilling = false;
        }
    }

    // Terminate objects have Delete flag
    for (auto& i : id_list)
    {
        Game_ObjectBase* obj = __objects[i].get();
        if (obj->IsDeleted())
        {
            DebugOut(L"deleted id=%d\n", i);
            obj->Execute_BeforeDelete();
            delete_object(i);
        }
    }
    spatial->de_Split_phase();
    nearbyObject->clear();
    delete nearbyObject;
}

void Scene_Battle::Load()
{
    if (_controller == NULL)
    {
        DebugOut(L"[LOAD FAILED] Can't find Stage controller.\n");
        return;
    }
    _controller->Load();

}

void Scene_Battle::Unload()
{
    _delete_spatial();
    map_sprite.clear();
    __objects.clear();
    _p1.reset(NULL);
    //_p2.reset(NULL);
    if (_controller != NULL)
        delete _controller;
     //__instance = NULL;
}

void Scene_Battle::KeyDownEventHandler(int KeyCode)
{
    if (_controller != NULL)
    {
        _controller->KeyDownEventHandler(KeyCode);
    }
}

//=====================================================================================================================


//=====================================================================================================================
// DEMO
void Scene_Battle::addPlayer1()
{
    _p1_id = add_object(move(_p1));
    spatial->insert_exception(_p1_id);
    Game_KeyInput::GetInstance()->AddObjectControl(p1());
}

void Scene_Battle::AddEffect(unique_ptr<Game_Effect>&& obj)
{
    _effects.push_back(move(obj));
}


int Scene_Battle::add_object(unique_ptr<Game_ObjectBase>&& object)
{
    //_objects.push_back(object);
    int id = id_nth;
    if (!id_recycle_bin.empty())
    {
        id = id_recycle_bin[id_recycle_bin.size() - 1];
        id_recycle_bin.pop_back();
    }
    else
    {
        id_nth++;
    }
    float l, t, r, b;
    object->SetId(id);
    object->GetBoundingBox(l, t, r, b);
    __objects[id] =move(object);
    
    //DebugOut(L"id %d l=%d t=%d r=%d b=%d\n", id_nth, (int)l, (int)t, (int)r, (int)b);
    spatial->insert(id, l, b, r, t);
    return id;
}

void Scene_Battle::delete_object(int id)
{
    Game_ObjectBase* object = __objects[id].get();
    float left, top, right, bottom;
    object->GetBoundingBox(left, top, right, bottom);
    spatial->remove(id);
    __objects[id].reset();
    __objects.erase(id);
    id_recycle_bin.push_back(id);
}

void Scene_Battle::_init_spatial()
{
    int width = int(GAMESCREEN_WIDTH * 1.1),
        height= int(GAMESCREEN_HEIGHT*1.1),
        n= _mapHeight / width+1,
        m= _mapWidth/ height+1;
    spatial.reset();
    spatial.reset(move( new QuadTree(0, 0, width, height,8,5)));




}



/// REMBER TO DELETE AFTER USE
vector<Game_ObjectBase*>* Scene_Battle::getObjectById(vector<int>& vtr)
{
    vector<Game_ObjectBase*>* objects= new vector<Game_ObjectBase*>;
    for (auto& id : vtr)
    {
        objects->push_back(__objects[id].get());
    }
    return objects;
}
void Scene_Battle::_delete_spatial()
{
    spatial.release();
    mapTexSpatial.release();
}


///PROTYPE

//=====================================================================================================
// PARSE

void Scene_Battle::parseMap(string line)
{
    PAUSE();
    _ParseSection_DICT(line);
    _ParseOBject(line);
    PLAY();
}

void Scene_Battle::_ParseSection_DICT(string line)
{
    map_sprite.clear();
    //texu
    int n = int(_mapHeight / MAP_TEXU_HEIGHT),
        m = int(_mapWidth / MAP_TEXU_WIDTH);
    mapTexSpatial.reset();
    mapTexSpatial.reset(move(new SpatialforTex(n, m, MAP_TEXU_WIDTH, MAP_TEXU_HEIGHT, int(340 / MAP_TEXU_HEIGHT), int(340 / MAP_TEXU_WIDTH))));
    ifstream f;
    f.open(line + "\\info.txt");


    if (f.is_open())
    {
        f >> map_id;
        width = MapWidth() / MAP_TEXU_WIDTH;
        height = MapHeight() / MAP_TEXU_HEIGHT;
    }
    else
    {
        // handle error if the file cannot be opened
        // set default values or throw an exception
        DebugOut(L"CANNOT READ %s\\info.txt", line);
        return;
    }
    f.close();
    f.open(line + "\\mapping.txt");
    set<int> dect;
    if (f.is_open())
    {
        int count = 0;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int temp;
                f >> temp;
                map[i][j] = temp;
                dect.insert(temp);
                count++;
                if (count == 600)
                {

                }
            }
        }
        wstring path = ToWSTR(line + "\\merged.png");
        _map_tex = CGame::GetInstance()->LoadTexture(path.c_str(), false);
        for (auto& i : dect)
        {
            int texID = i;
            int index_value = i;
            int left = 0 + MAP_TEXU_WIDTH * (index_value % 10),
                top = 0 + MAP_TEXU_HEIGHT * (index_value / 10),
                right = left+ MAP_TEXU_WIDTH-1,
                bottom = top+MAP_TEXU_HEIGHT-1;
            map_sprite[texID].reset(new CSprite(texID, left, top, right, bottom, _map_tex));
        }
    }
    else
    {
        DebugOut(L"CANNOT READ %s\\mapping.txt", line);
        return;
    }
    f.close();

    int curID = 0;
    int curN = 0, curM = 0;
    //parsing texture+
    curN = 0, curM = 0;
    curID = 0;
    int a = MapHeight();
    DebugOut(L"%d\n",a);
    for (curN = 0; curN < height; curN++)
    {
        for (curM = 0; curM < width; curM++)
        {

             addMapPart(curID,(curM)*MAP_TEXU_WIDTH,MapHeight() - curN * MAP_TEXU_HEIGHT- MAP_TEXU_HEIGHT);
                curID++;
        }
    }


}
void Scene_Battle::_ParseOBject(string line)
{
    fstream f;
    f.open(line+"\\object.txt");
    if (f.is_open())
    {
        int16_t id;
        float x, y;
        int param1, param2;
        unique_ptr<Game_ObjectBase>obj;
        while (!f.eof() || !f.fail())
        {
            try
            {
                f >> id >> x >> y >> param1 >> param2;
                
                switch (id)
                {
                // PARSE TERRAIN (param1 = width, param2 = height)
                case TBLOCKER: obj.reset(new Game_Blocker(x, y, Z_INDEX_TERRAIN, param1, param2));
                    break;
                case TPLATFORM: obj.reset(new Game_Platform(x, y, Z_INDEX_TERRAIN, param1, param2));
                    break;
                case TWATER: obj.reset(new Game_Water(x, y, Z_INDEX_TERRAIN, param1, param2));
                    break;
                case TDEADLY: obj.reset(new Game_DeadlyBlock(x, y, Z_INDEX_TERRAIN, param1, param2));
                    break;
                case TPLAYERBLOCKER: obj.reset(new Game_PlayerBlocker(x, y, Z_INDEX_TERRAIN, param1, param2));
                    break;
                case TBRIDGE_S1: obj.reset(new Game_Bridge_S1(x, y, Z_INDEX_TERRAIN, param1, param2)); 
                    // param1 = triggerID, param2 = TimeOffset
                    break;
                case TMOVINGSTONE: obj.reset(new Obj_MovingStone(x, y, Z_INDEX_TERRAIN, param1, param2));
                    // param1 = max pos Left, param2 = max pos Right
                    break;
                // PARSE OBJECT
                case CHAR_CONTRA:
                    _p1.reset(new Game_Player(x, y, Z_INDEX_PLAYER));
                    addPlayer1();
                    obj.reset(NULL);
                    break;
                case RED_GUNNER: obj.reset(new Enemy_RedGunner(x, y, Z_INDEX_ENEMY, param1));
                    break;
                case SNIPER: obj.reset(new Enemy_Sniper(x, y, Z_INDEX_ENEMY));
                    break;
                case SNEAKY_SNIPER: obj.reset(new Enemy_SneakSniper(x, y, Z_INDEX_STATION));
                    break;
                case SCUBA_DIVER: obj.reset(new Enemy_ScubaDiver(x, y, Z_INDEX_ENEMY));
                    break;
                case TURRET: obj.reset(new Enemy_Turret(x, y, Z_INDEX_STATION, param1));
                    break;
                case CANNON: obj.reset(new Enemy_Cannon(x, y, Z_INDEX_STATION));
                    break;
                case BASE_SNIPER: obj.reset(new Enemy_SneakSniper_Base(x, y, Z_INDEX_ENEMY));
                    break;
                case BASE_CANNON_LEFT: obj.reset(new Enemy_Cannon_Base(x, y, Z_INDEX_ENEMY, 1));
                    break;
                case BASE_CANNON_RIGHT: obj.reset(new Enemy_Cannon_Base(x, y, Z_INDEX_ENEMY, 0));
                    break;
                case BASE_DOOR: obj.reset(new Enemy_Base_Door(x, y, Z_INDEX_ENEMY));
                    break;
                case BASE_BODY: obj.reset(new Obj_BossBase_S1(x, y, Z_INDEX_TERRAIN, param1));
                    break;
                case FLAME: obj.reset(new Obj_Flame(x, y, Z_INDEX_STATION, param1, param2));
                    break;
                case UP_BOX_STATION: obj.reset(new Obj_StationUpgradeBox(x, y, Z_INDEX_ITEM, param1, param2));
                    break;
                case UP_BOX_FLYING: obj.reset(new Obj_FlyingUpgradeBox(x, y, Z_INDEX_ITEM, param1, param2));
                    break;
                case CAMERA:
                    ScreenManager::GetInstance()->Screen()->SetPosition(x, y);
                    obj.reset(NULL);
                    break;

                // SPAWNER
                case SPAWNER_INFARY: obj.reset(new Spawner_Infary_Stage1(x, y, Z_INDEX_TERRAIN, param1, param2));
                    break;
                case SPAWNER_FALLING_STONE: obj.reset(new Spawner_FallingStone(x, y, Z_INDEX_TERRAIN, param1, param2));
                    break;
                case SPAWNER_INFARY_S3_LEFT: obj.reset(new Spawner_Infary_Stage3_Left(x, y, Z_INDEX_TERRAIN, param1, param2));
                    break;
                case SPAWNER_INFARY_S3_RIGHT: obj.reset(new Spawner_Infary_Stage3_Right(x, y, Z_INDEX_TERRAIN, param1, param2));
                    break;

                default:
                    obj.reset(NULL);
                    DebugOut(L"Unknown id=%d", id);
                    break;
                }
                if (obj.get() != NULL)
                {
                    add_object(move(obj));
                }
            }
            catch(...)
            {
                DebugOut(L"PLEASE RECHECK THE OBJECT.TXT IN MAP DIC");
                return;
            }

        }
    }
    else
    {
        DebugOut(L"CANNOT READ %s\\object.txt", line);
        return;
    }
    f.close();

}

void Scene_Battle::renderBG(float x, float y)
{
    vector<int> id = mapTexSpatial->getNearByIDyx(y, x);
    for (int i = 0; i < id.size(); i++)
    {
        int n = id[i] / width,
            m=id[i]%width;
        int _x, _y;
        mapTexSpatial->getXYCenter(id[i], _x, _y);
        map_sprite[map[n][m]].get()->Draw(_x,_y);
    }
}
void Scene_Battle::renderBG(int& x, int& y)
{
    renderBG(x / 1.0f, y / 1.0f);
}
void Scene_Battle::addMapPart( int partID, int x, int y)
{
    mapTexSpatial->init_object_ONLYONCE(partID, x, y );
}

void Scene_Battle::HUB_HP_handler()
{

}

//vector<int> Scene_Battle::getNearbyIDFast()
//{
//    float x, y;
//    ScreenManager::GetInstance()->Screen()->GetCenterPoint(x, y);
//    int width =(int) (GAMESCREEN_WIDTH * 1.3),
//        height = (int)(GAMESCREEN_HEIGHT * 1.3);
//    return getNearByIDwithWH(x, y, width, height);
//}

vector<int> Scene_Battle::getNearByID(int left, int bottom, int right, int top)
{
    return spatial->search(left, bottom, right, top, -100);
}

vector<int> Scene_Battle::getNearByIDwithWH(int x, int y, int width, int height)
{
    int left = x - width / 2,
        right = left + width,
        bottom = y - height / 2,
        top = y + height;
    return spatial->search(left, bottom, right, top,-100);
}
