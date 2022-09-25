#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

enum class EGAMEOBJECTTYPE
{
	// Launchables
	ASTERIOD,
	LAUNCHABLE2,
	LAUNCHABLE3,

	// Enemies
	ENEMY1,
	ENEMY2,
	ENEMY3,

	// Obstacles
	DESTRUCTABLE1,
	DESTRUCTABLE2,
	DESTRUCTABLE3,
	NUCLEARPASTA,

	// Gravity Generator
	PLANET

};

class CGameObject
{
public:
	CGameObject();// (sf::Vector2f _v2fPosition, float _fScale, b2BodyType _bodyType, std::string _sSpriteName, b2World* _pWorld);
	virtual ~CGameObject();
	
	// Factory method to create game objects
	static CGameObject* CreateGameObject(EGAMEOBJECTTYPE _EGameObjectType, b2World* _pWorld, sf::Vector2f _v2fPosition, float _fScale);

	// Updates the position of the sprite and draws it to the window
	virtual void Render(sf::RenderWindow& _window, float _fScale);

	// Called when object starts touching another object
	virtual void StartContact(CGameObject* _goOther);

	// Called when object finishes touching another object
	virtual void EndContact(CGameObject* _goOther);

	// Called after the collision response is calculated
	virtual void PostSolve(const b2ContactImpulse* _impulse);

	// Returns the objects body
	b2Body* Getb2Body() { if (m_pBody != nullptr) { return m_pBody; } }

protected:

	EGAMEOBJECTTYPE m_EGameObjectType;

	// Box2D for physics
	b2BodyDef m_bodyDef;
	b2Body* m_pBody;
	b2Shape* m_pShape;
	b2FixtureDef m_fixtureDef;

	// SFML for rendering
	sf::Sprite m_sprite;
	sf::Texture m_texture;

};

