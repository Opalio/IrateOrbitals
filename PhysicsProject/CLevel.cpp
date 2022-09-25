#include "CLevel.h"
#include "CAsteriod.h"

CLevel::CLevel(float _fScale)
{
	b2Vec2 b2v2Gravity(0.0f, 10.0f);
	m_pWorld = new b2World(b2v2Gravity);

	// Create and bind the contact listener
	m_pContactListener = new CContactListener();
	m_pWorld->SetContactListener(m_pContactListener);

	// Static Floor
	m_vpObjects.push_back(new Object(sf::Vector2f(480, 500), _fScale, b2BodyType::b2_staticBody, "Ground.png", m_pWorld));

	// 3 dynamic 'balls'
	for (int i = 0; i < 3; i++)
	{
		m_vpObjects.push_back(new Object(sf::Vector2f(550 + i * 100, 100), _fScale, b2BodyType::b2_dynamicBody, "Ball.png", m_pWorld));
	}

	m_pLauncher = new CLauncher(sf::Vector2f(250, 410));
}

CLevel::~CLevel()
{
	// Delete all objects here

	// Delete contact listener
	if (m_pContactListener != nullptr)
	{
		delete m_pContactListener;
		m_pContactListener = nullptr;
	}

	// Delete the world
	if (m_pWorld != nullptr)
	{
		delete m_pWorld;
		m_pWorld = nullptr;
	}
}

void CLevel::Render(sf::RenderWindow& _window, float _fScale)
{
	for (size_t i = 0; i < m_vpObjects.size(); i++)
	{
		m_vpObjects[i]->Render(_window, _fScale);
	}

	for (size_t i = 0; i < m_vpGameObjects.size(); i++)
	{
		m_vpGameObjects[i]->Render(_window, _fScale);
	}

	/*for (size_t i = 0; i < m_vpLaunchables.size(); i++)
	{
		m_vpLaunchables[i]->Render(_window, _fScale);
	}*/

	m_pLauncher->Render(_window);

	return;
}

void CLevel::Update()
{
	m_pWorld->Step(1 / 60.f, 8, 3);

	return;
}

void CLevel::MouseButtonPressed(sf::RenderWindow& _window)
{
	CLaunchable* pNewLauchable = new CAsteriod();

	m_vpGameObjects.push_back(pNewLauchable);

	m_pLauncher->LoadLaunchable(pNewLauchable);
	m_pLauncher->MoveLaunchable(_window);

	return;
}

void CLevel::MouseButtonReleased(float _fScale)
{
	m_pLauncher->LaunchLoaded(_fScale, *m_pWorld);

	return;
}

void CLevel::MouseMoved(sf::RenderWindow& _window)
{
	m_pLauncher->MoveLaunchable(_window);

	return;
}
