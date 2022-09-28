#pragma once
#include "CLaunchable.h"
class CStarLinkSat :
    public CLaunchable
{
public:
    CStarLinkSat();
    ~CStarLinkSat();

    void ActivateSpecialAbility(sf::RenderWindow& _window, float _fScale, std::vector<CGameObject*>& _vpGameObjects) override;

private:
    b2DistanceJointDef m_distanceJointDef;

    b2DistanceJoint* m_pDistanceJoint = nullptr;
};

