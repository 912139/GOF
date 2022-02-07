#pragma once

#include <vector>
#include <functional>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "MyTools.h"

class ISbomber {
private:
    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;

    uint16_t bombsNumber;
    int16_t score;

public:
    ISbomber ();
    ~ISbomber ();

    Ground * FindGround() const;
    Plane * FindPlane() const;
    LevelGUI * FindLevelGUI() const;
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    std::vector<Ibomb*> FindAllBombs() const;

    uint16_t GetBombsNumber() const;
    uint16_t GetScore() const;
    void modScore(uint16_t number);
    void decBombsNumber();

    void addDynamic (DynamicObject* obj);
    void addStatic (GameObject* obj);
    void forEachStatic(std::function<void(GameObject&)> cb);
    void forEachDynamic(std::function<void(DynamicObject&)> cb);
    void removeDynamic (DynamicObject* obj);
    void removeStatic (GameObject* obj);
};
