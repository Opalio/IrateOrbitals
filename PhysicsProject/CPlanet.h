#pragma once
#include "CGameObject.h"
class CPlanet :
    public CGameObject
{
public:
    CPlanet(sf::Vector2f _v2fPosition, float _fScale, b2World* _pWorld, std::string _sPlanetName, b2BodyType _bodyType, float _fPlanetScale);
    virtual ~CPlanet();

    // Uses equation formulated from Newton's law of universal gravitation
    // Exerts force on passed object towards planet
    void ExertGravitationalForceOn(CGameObject* _pGameObject);

    // Create a revolute joint with a motor to create a faux orbit, speed is in Degrees/Second
    void GiveAsOrbital(b2Body* _pBodyThatWillOrbit, float _fSpeed, int _iDistance);

private:
    float m_fGravitationalConstant = 0.5f;
    float m_fMass = 0.0f; // requires this as static bodies do not have mass

    b2RevoluteJointDef m_revoluteJointDef;
    b2RevoluteJoint* m_pOrbitalJoint;
};

