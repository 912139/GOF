#pragma once

#include <vector>
#include <functional>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "MyTools.h"
#include "ISbomber.h"
#include "ICommand.h"

class SBomber
{
public:

    SBomber();
    ~SBomber() = default;
    
    inline bool GetExitFlag() const { return exitFlag; }

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();

    void CommandExecuter(AbstractCommand * pCommand);

    void CheckPlaneAndLevelGUI();
    void CheckBombsAndGround();
    void __fastcall CheckDestoyableObjects(Ibomb* pBomb);

private:
    ISbomber* Interface;
    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t deltaTime, fps;
};