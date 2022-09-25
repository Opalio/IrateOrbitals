#pragma once

#include "SFML/Graphics.hpp"

// Forward Declarations
class b2World;
class CLaunchable;


class CLauncher
{
public:
	CLauncher(sf::Vector2f _v2fPosition);
	~CLauncher();

	void Render(sf::RenderWindow& window);

	void LoadLaunchable(CLaunchable* _launchable);
	void MoveLaunchable(sf::RenderWindow& _window);
	void LaunchLoaded(float _fScale, b2World& _world);

private:

	CLaunchable* m_pLoadedLaunchable;

	// Firing Variables
	sf::Vector2f m_v2fFiringOrigin;
	sf::Vector2f m_v2fFiringVector;

	// SFML Stuff
	sf::Sprite m_sprite;
	sf::Texture m_texture;
};

