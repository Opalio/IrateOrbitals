#pragma once
#include "CDestructable.h"
class CEnemy :
    public CDestructable
{
public:
    CEnemy(sf::Vector2f _v2fPosition, float _fScale, b2World* _pWorld);
    ~CEnemy();
private:

};

