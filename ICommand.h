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

class AbstractCommand {
public:
    AbstractCommand() = default;
    virtual ~AbstractCommand() = default;
    virtual void Execute() = 0;
};

class DeleteDynamicObject : public AbstractCommand {
    DynamicObject* obj;
    ISbomber* Interface;
public:

    DeleteDynamicObject (DynamicObject *object, ISbomber* Int);
    ~DeleteDynamicObject() override = default;

    void Execute() override;
};

class DeleteStaticObject : public AbstractCommand {
    GameObject* obj;
    ISbomber* Interface;
public:

    DeleteStaticObject (GameObject *object, ISbomber* Int);
    ~DeleteStaticObject() override = default;

    void Execute() override;
};

class DropBomb : public AbstractCommand {
private:
    ISbomber* Interface;

public:
    explicit DropBomb(ISbomber* Int);
    ~DropBomb() override = default;

    void Execute() override;
};

class DropBombDecorator : public AbstractCommand {
private:
    ISbomber* Intarface;

public:
    explicit DropBombDecorator(ISbomber* Int);
    ~DropBombDecorator() override = default;

    void Execute() override;
};
