#pragma once
#include "Scene_Base.h"
class Scene_Start : public Scene_Base
{
    void init();
    bool startTimer = false;
    DWORD _waitingTick = 2000;  
public:
    Scene_Start(): Scene_Base() {};
    void KeyDownEventHandler(int KeyCode) override;
    void Update(DWORD dt) override;
   // void Render() override;
    void Load() override;
    void Unload() override;
    void nextScene() override;
    ~Scene_Start() { Unload(); };
};

