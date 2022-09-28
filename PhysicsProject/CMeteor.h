#pragma once
#include "CLaunchable.h"
class CMeteor :
    public CLaunchable
{
public:
    CMeteor();
    ~CMeteor();

    void ActivateSpecialAbility(sf::RenderWindow& _window, float _fScale, std::vector<CGameObject*>& _vpGameObjects) override;

private:
    
    float ConvertToRadians(float _fDegrees);
    b2Vec2 RotateVector(b2Vec2 _v2f, float _degrees);
    //CMeteor* Clone() const { return new CMeteor(*this); }


};

