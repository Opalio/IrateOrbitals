#pragma once

#include "CIndestructable.h"

class CLaunchable :
    public CIndestructable
{
public:
    CLaunchable();
    virtual ~CLaunchable();

    void Launch(float _fScale, sf::Vector2f _v2fPosition, b2World& _world);

    void Render(sf::RenderWindow& _window, float _fScale) override;

    sf::Sprite& GetSprite() { return m_sprite; }
};

