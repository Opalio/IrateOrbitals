#pragma once

#include "CIndestructable.h"

class CLaunchable :
    public CIndestructable
{
public:
    CLaunchable();
    virtual ~CLaunchable();

    // Generates launchable using factory method
    static CLaunchable* CreateLaunchable(EGAMEOBJECTTYPE _EGameObjectType);

    // Setsup Box2D stuff
    void Launch(float _fScale, sf::Vector2f _v2fPosition, b2World& _world);

    void Render(sf::RenderWindow& _window, float _fScale) override;

    // Not all parameters are used for each ability
    // Each parameter is used across all lauchable subclasses
    virtual void ActivateSpecialAbility(sf::RenderWindow& _window, float _fScale, std::vector<CGameObject*>& _vpGameObjects);

    sf::Sprite& GetSprite() { return m_sprite; }
};

