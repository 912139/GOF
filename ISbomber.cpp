#include <conio.h>
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "House.h"
#include "ISbomber.h"
using namespace std;

ISbomber::ISbomber ()
        : bombsNumber(10), score(0) {}

ISbomber::~ISbomber()
{
    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        if (vecDynamicObj[i] != nullptr)
        {
            delete vecDynamicObj[i];
        }
    }

    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        if (vecStaticObj[i] != nullptr)
        {
            delete vecStaticObj[i];
        }
    }
}

uint16_t ISbomber::GetBombsNumber() const {
    return bombsNumber;
}
uint16_t ISbomber::GetScore() const {
    return score;
}
void ISbomber::modScore(uint16_t number) {
    score+=number;
}

void ISbomber::decBombsNumber() {
    bombsNumber--;
}

void ISbomber::addDynamic (DynamicObject* obj)
{
    vecDynamicObj.push_back(obj);
}
void ISbomber::addStatic (GameObject* obj)
{
    vecStaticObj.push_back(obj);
}
void ISbomber::forEachStatic(std::function<void(GameObject&)> cb)
{
    for(auto* obj : vecStaticObj)
    {
        if (obj != nullptr) {
            cb(*obj);
        }

    }
}
void ISbomber::forEachDynamic(std::function<void(DynamicObject&)> cb)
{
    for(auto* obj : vecDynamicObj)
    {
        if (obj != nullptr) {
            cb(*obj);
        }

    }
}

void ISbomber::removeDynamic (DynamicObject* obj)
{
    auto it = vecDynamicObj.begin();
    for (; it != vecDynamicObj.end(); it++)
    {
        if (*it == obj)
        {
            vecDynamicObj.erase(it);
            break;
        }
    }
}
void ISbomber::removeStatic (GameObject* obj)
{
    auto it = vecStaticObj.begin();
    for (; it != vecStaticObj.end(); it++)
    {
        if (*it == obj)
        {
            vecStaticObj.erase(it);
            break;
        }
    }
}

vector<DestroyableGroundObject*> ISbomber::FindDestoyableGroundObjects() const
{
    vector<DestroyableGroundObject*> vec;
    Tank* pTank;
    House* pHouse;
    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        pTank = dynamic_cast<Tank*>(vecStaticObj[i]);
        if (pTank != nullptr)
        {
            vec.push_back(pTank);
            continue;
        }

        pHouse = dynamic_cast<House*>(vecStaticObj[i]);
        if (pHouse != nullptr)
        {
            vec.push_back(pHouse);
            continue;
        }
    }

    return vec;
}

Ground* ISbomber::FindGround() const
{
    Ground* pGround;

    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        pGround = dynamic_cast<Ground *>(vecStaticObj[i]);
        if (pGround != nullptr)
        {
            return pGround;
        }
    }

    return nullptr;
}

vector<Ibomb*> ISbomber::FindAllBombs() const
{
    vector<Ibomb*> vecBombs;

    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        Ibomb* pBomb = dynamic_cast<Ibomb*>(vecDynamicObj[i]);
        if (pBomb != nullptr)
        {
            vecBombs.push_back(pBomb);
        }
    }

    return vecBombs;
}

Plane* ISbomber::FindPlane() const
{
    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        Plane* p = dynamic_cast<Plane*>(vecDynamicObj[i]);
        if (p != nullptr)
        {
            return p;
        }
    }

    return nullptr;
}

LevelGUI* ISbomber::FindLevelGUI() const
{
    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        LevelGUI* p = dynamic_cast<LevelGUI*>(vecStaticObj[i]);
        if (p != nullptr)
        {
            return p;
        }
    }

    return nullptr;
}
