#pragma once
#include "CGameObject.h"
class CPlanet :
    public CGameObject
{
public:
    CPlanet(sf::Vector2f _v2fPosition, float _fScale, b2World* _pWorld);
    virtual ~CPlanet();

    void ExertGravitationalForceOn(CGameObject* _pGameObject);

private:
    float m_fGravitationalConstant = 0.5f;
    float m_fMass = 15.0f; // requires this as static bodies do not have mass
};

