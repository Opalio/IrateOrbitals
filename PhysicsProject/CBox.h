#pragma once
#include "CDestructable.h"
class CBox :
    public CDestructable
{
public:
    CBox(sf::Vector2f _v2fPosition, float _fScale, b2World* _pWorld);
    ~CBox();

private:
};

