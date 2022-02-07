#pragma once

#include "DynamicObject.h"

class Ibomb : public DynamicObject
{
public:

    static const uint16_t BombCost = 10; // стоимость бомбы в очках

};

class Bomb : public Ibomb
{
public:

	void Draw() const override;

private:

};

class BombDecorator : public Ibomb
{
    Bomb* bomb;
public:
    BombDecorator();
    ~BombDecorator() {}
    void Draw() const override;
    void Move(uint16_t time) override;
    void SetPos(double nx, double ny) override;
    uint16_t GetWidth() const override;
    void SetSpeed(double sp) override;
    void SetDirection(double dx, double dy) override;
    double GetY() const override;
    double GetX() const override;
};