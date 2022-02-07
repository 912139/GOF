
#include <conio.h>
#include <windows.h>

#include "MyTools.h"
#include "SBomber.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "House.h"
#include "ISbomber.h"
#include "ICommand.h"

using namespace std;
using namespace MyTools;

SBomber::SBomber()
        : exitFlag(false),
          startTime(0),
          finishTime(0),
          deltaTime(0),
          passedTime(0),
          fps(0),
          Interface(new ISbomber)
{
    LoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    Plane* p = new Plane;
    p->SetDirection(1, 0.1);
    p->SetSpeed(4);
    p->SetPos(5, 10);
    Interface->addDynamic(p);

    LevelGUI* pGUI = new LevelGUI;
    pGUI->SetParam(passedTime, fps, Interface->GetBombsNumber(), Interface->GetScore());
    const uint16_t maxX = ScreenSingleton::getInstance().GetMaxX();
    const uint16_t maxY = ScreenSingleton::getInstance().GetMaxY();
    const uint16_t offset = 3;
    const uint16_t width = maxX - 7;
    pGUI->SetPos(offset, offset);
    pGUI->SetWidth(width);
    pGUI->SetHeight(maxY - 4);
    pGUI->SetFinishX(offset + width - 4);
    Interface->addStatic(pGUI);

    Ground* pGr = new Ground;
    const uint16_t groundY = maxY - 5;
    pGr->SetPos(offset + 1, groundY);
    pGr->SetWidth(width - 2);
    Interface->addStatic(pGr);

    Tank* pTank = new Tank;
    pTank->SetWidth(13);
    pTank->SetPos(30, groundY - 1);
    Interface->addStatic(pTank);

    pTank = new Tank;
    pTank->SetWidth(13);
    pTank->SetPos(50, groundY - 1);
    Interface->addStatic(pTank);

    House * pHouse = new House;
    pHouse->SetWidth(13);
    pHouse->SetPos(80, groundY - 1);
    Interface->addStatic(pHouse);
}

void SBomber::MoveObjects()
{
    LoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    Interface->forEachDynamic([this](auto& obj) {obj.Move(deltaTime);});
}

void SBomber::CheckObjects()
{
    LoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    CheckPlaneAndLevelGUI();
    CheckBombsAndGround();
}

void SBomber::CheckPlaneAndLevelGUI()
{
    if (Interface->FindPlane()->GetX() > Interface->FindLevelGUI()->GetFinishX())
    {
        exitFlag = true;
    }
}

void SBomber::CheckBombsAndGround()
{
    vector<Ibomb*> vecBombs = Interface->FindAllBombs();
    Ground* pGround = Interface->FindGround();
    const double y = pGround->GetY();
    for (size_t i = 0; i < vecBombs.size(); i++)
    {
        if (vecBombs[i]->GetY() >= y) // ����������� ����� � ������
        {
            pGround->AddCrater(vecBombs[i]->GetX());
            CheckDestoyableObjects(vecBombs[i]);
            DeleteDynamicObject* command = new DeleteDynamicObject(vecBombs[i], Interface);
            CommandExecuter(command);
        }
    }

}

void SBomber::CheckDestoyableObjects(Ibomb* pBomb)
{
    vector<DestroyableGroundObject*> vecDestoyableObjects = Interface->FindDestoyableGroundObjects();
    const double size = pBomb->GetWidth();
    const double size_2 = size / 2;
    for (size_t i = 0; i < vecDestoyableObjects.size(); i++)
    {
        const double x1 = pBomb->GetX() - size_2;
        const double x2 = x1 + size;
        if (vecDestoyableObjects[i]->isInside(x1, x2))
        {
            Interface->modScore(vecDestoyableObjects[i]->GetScore());
            DeleteStaticObject* command = new DeleteStaticObject(vecDestoyableObjects[i], Interface);
            CommandExecuter(command);
        }
    }
}

void SBomber::ProcessKBHit()
{
    int c = _getch();

    if (c == 224)
    {
        c = _getch();
    }

    LoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked. key = ", c);

    switch (c) {

        case 27: // esc
            exitFlag = true;
            break;

        case 72: // up
            Interface->FindPlane()->ChangePlaneY(-0.25);
            break;

        case 80: // down
            Interface->FindPlane()->ChangePlaneY(0.25);
            break;

        case 'b': {
            DropBomb *command = new DropBomb(Interface);
            CommandExecuter(command);
            break;
        }

        case 'B': {
            DropBomb *command = new DropBomb(Interface);
            CommandExecuter(command);
            break;
        }

        case 'v': {
            DropBombDecorator *command = new DropBombDecorator(Interface);
            CommandExecuter(command);
            break;
        }

        case 'V': {
            DropBombDecorator *command = new DropBombDecorator(Interface);
            CommandExecuter(command);
            break;
        }

        default:
            break;
    }
}

void SBomber::DrawFrame()
{
    LoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    Interface->forEachDynamic([this](auto& obj) {obj.Draw();});

    Interface->forEachStatic([this](auto& obj) {obj.Draw();});

    ScreenSingleton::getInstance().GotoXY(0, 0);
    fps++;

    Interface->FindLevelGUI()->SetParam(passedTime, fps, Interface->GetBombsNumber(), Interface->GetScore());
}

void SBomber::TimeStart()
{
    LoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");
    startTime = GetTickCount64();
}

void SBomber::TimeFinish()
{
    finishTime = GetTickCount64();
    deltaTime = uint16_t(finishTime - startTime);
    passedTime += deltaTime;

    LoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " deltaTime = ", (int)deltaTime);
}

void SBomber::CommandExecuter(AbstractCommand * pCommand) {
    pCommand->Execute();
    delete pCommand;
}