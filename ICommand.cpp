#include "MyTools.h"
#include "Bomb.h"
#include "Ground.h"
#include "ISbomber.h"
#include "ICommand.h"

DeleteDynamicObject::DeleteDynamicObject(DynamicObject *object, ISbomber* Int)
        : obj(object), Interface{Int} {}

void DeleteDynamicObject::Execute() {
    Interface->removeDynamic(obj);
}

DeleteStaticObject::DeleteStaticObject(GameObject *object, ISbomber* Int)
        : obj(object), Interface{Int} {}

void DeleteStaticObject::Execute()
{
    Interface->removeStatic(obj);
}

DropBomb::DropBomb(ISbomber* Int) : Interface {Int} {}

void DropBomb::Execute()
{
    if (Interface->GetBombsNumber() > 0) {
        MyTools::LoggerSingletone::getInstance().WriteToLog(std::string(__FUNCTION__) + " was invoked");
        Plane* pPlane = Interface->FindPlane();
        double x = pPlane->GetX() + 4;
        double y = pPlane->GetY() + 2;

        Bomb *pBomb = new Bomb;
        pBomb->SetDirection(0.3, 1);
        pBomb->SetSpeed(2);
        pBomb->SetPos(x, y);
        pBomb->SetWidth(SMALL_CRATER_SIZE);

        Interface->addDynamic(pBomb);
        Interface->decBombsNumber();
        Interface->modScore(-Bomb::BombCost);
    }
}

DropBombDecorator::DropBombDecorator(ISbomber* Int)  : Intarface{Int} {}

void DropBombDecorator::Execute()
{
    if (Intarface->GetBombsNumber() > 0) {
        MyTools::LoggerSingletone::getInstance().WriteToLog(std::string(__FUNCTION__) + " was invoked");
        Plane* pPlane = Intarface->FindPlane();
        double x = pPlane->GetX() + 4;
        double y = pPlane->GetY() + 2;

        BombDecorator* pBomb = new BombDecorator();
        pBomb->SetDirection(0.3, 1);
        pBomb->SetSpeed(2);
        pBomb->SetPos(x, y);
        pBomb->SetWidth(SMALL_CRATER_SIZE);
        Intarface->addDynamic(pBomb);
        Intarface->decBombsNumber();
        Intarface->modScore(-Bomb::BombCost);
    }
}
