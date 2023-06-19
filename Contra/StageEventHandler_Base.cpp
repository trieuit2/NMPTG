#include "StageEventHandler_Base.h"
#include "Scene_Battle.h"
#include "ScreenManager.h"
#include "GameManager.h"
#include "CharacterEffect.h"
void StageEventHandler_Base::Update(DWORD dt)
{
    Game_Player* player = _srcScene->p1();
    GameManager* gm = GameManager::GetInstance();

    // STAGE CLEAR
    if (gm->Test_IfPassStage() == CAN_PASS_STAGE)
    {
        Perform_StageClearEvent(dt);
        if (_WaitForClearStage < WAIT_STAGECLEAR_MAXVALUE)
        {
            if (_WaitForClearStage > dt)
            {
                _WaitForClearStage -= dt;
            }
            else
            {
                CompleteStage();
            }
        }

        return;
    }

    // GAME OVER
    if (player != NULL && player->Hp() <= 0)
    {
        if (_WaitForEndGame >= WAIT_ENDGAME_MAXVALUE)
        {
            _WaitForEndGame = ENDGAME_INTERVAL;
        }
        else if (_WaitForEndGame > dt)
        {
            _WaitForEndGame -= dt;
        }
        else
        {
            GameOver();
        }
    }

}

void StageEventHandler_Base::Set_Camera_Focus_Player()
{
    if (_toggleFreeCam)
        return;
	float camPosX = 0;
    float camPosY = 0;
    Game_Screen* cam = ScreenManager::GetInstance()->Screen();
    _srcScene->p1()->GetCenterPoint(camPosX, camPosY);
    cam->SetCenterPoint(camPosX, camPosY);
    //cam->focusToPoint(camPosX, camPosY);
}

void StageEventHandler_Base::Debug_KeyDownEventHandler(int KeyCode)
{
    if (STAGE_DEBUG_ALLOW)
    {
        float x, y;
        
        _srcScene->p1()->GetCenterPoint(x, y);

        switch (KeyCode)
        {
        case DIK_1:
            _srcScene->p1()->ChangeWeapon(new Equip_Gun_N());
            break;
        case DIK_2:
            _srcScene->p1()->ChangeWeapon(new Equip_Gun_M());
            break;
        case DIK_3:
            _srcScene->p1()->ChangeWeapon(new Equip_Gun_S());
            break;
        case DIK_4:
            _srcScene->p1()->ChangeWeapon(new Equip_Gun_L());
            break;
        case DIK_5:
            _srcScene->p1()->ChangeWeapon(new Equip_Gun_F());
            break;
        case DIK_6:
            CHARACTER_EFFECT::applyEffect(_srcScene->p1(), CHARACTER_EFFECT::BARRIER, 20000);
            break;
        case DIK_7:
            CompleteStage();
            break;
        case DIK_8:
            _toggleFreeCam = true;
            break;
        case DIK_9:
            _toggleFreeCam = false;
            break;
        case DIK_W:
            if (_toggleFreeCam)
            {
                Game_Screen* screen = ScreenManager::GetInstance()->Screen();
                screen->SetPosition(screen->x(), screen->y() + 32);
            }
            break;
        case DIK_S:
            if (_toggleFreeCam)
            {
                Game_Screen* screen = ScreenManager::GetInstance()->Screen();
                screen->SetPosition(screen->x(), screen->y() - 32);
            }
            break;
        case DIK_A:
            if (_toggleFreeCam)
            {
                Game_Screen* screen = ScreenManager::GetInstance()->Screen();
                screen->SetPosition(screen->x() - 32, screen->y());
            }
            break;
        case DIK_D:
            if (_toggleFreeCam)
            {
                Game_Screen* screen = ScreenManager::GetInstance()->Screen();
                screen->SetPosition(screen->x() + 32, screen->y());
            }
            break;
        }
    }
}

StageEventHandler_Base::StageEventHandler_Base(Scene_Battle* src)
{
    if (_srcScene != NULL)
    {
        delete _srcScene;
    }
    _srcScene = src;
}

void StageEventHandler_Base::Load()
{
    GameManager* gm = GameManager::GetInstance();
    
    Equip_GunBase* gun = NULL;

    switch (gm->GetSavedGun_P1())
    {
    case GUN_N:
        gun = new Equip_Gun_N();
        break;
    case GUN_R:
        gun = new Equip_Gun_M();
        break;
    case GUN_S:
        gun = new Equip_Gun_S();
        break;
    case GUN_L:
        gun = new Equip_Gun_L();
        break;
    case GUN_F:
        gun = new Equip_Gun_F();
        break;
    }
    _srcScene->p1()->ChangeWeapon(gun);

    _srcScene->p1()->SetHp(gm->GetSavedLife_P1());
}

void StageEventHandler_Base::CompleteStage()
{
    GameManager::GetInstance()->SaveGun_P1(_srcScene->p1()->GunID());
    GameManager::GetInstance()->SaveLife_P1(_srcScene->p1()->Hp());
}

void StageEventHandler_Base::GameOver()
{
    GameManager::GetInstance()->ReceiveSignal(SIG_PLAY_GAME_OVER, _srcScene);
    _srcScene->PAUSE();
}

void StageEventHandler_Base::KeyDownEventHandler(int KeyCode)
{
    Debug_KeyDownEventHandler(KeyCode);
}