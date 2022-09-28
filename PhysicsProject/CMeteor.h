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
    

    //CMeteor* Clone() const { return new CMeteor(*this); }


};

