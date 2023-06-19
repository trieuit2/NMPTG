#pragma once
#include "Scene_Base.h"
class Scene_GameOver : public Scene_Base
{
        void init();
        bool startTimer = false;
        DWORD _waitingTick = 0;
        int location;
        int selection_id=-1;
        bool endGame = false;
    public:
        Scene_GameOver() : Scene_Base() { location = 0; };
        void KeyDownEventHandler(int KeyCode) override;
        void Update(DWORD dt) override;
        //void Render() override;
        void Load() override;
        void Unload() override;
        void nextScene() override;
        ~Scene_GameOver() { Unload(); };
};
