#include "CLevel.h"
#include "CAsteriod.h"
#include "CNuclearPasta.h"
#include "CEnemy.h"

CLevel::CLevel(float _fScale)
{
	b2Vec2 b2v2Gravity(0.0f, 0.0f);
	m_pWorld = new b2World(b2v2Gravity);

	// Create and bind the contact listener
	m_pContactListener = new CContactListener();
	m_pWorld->SetContactListener(m_pContactListener);

	// Static Floor
	//m_vpObjects.push_back(new Object(sf::Vector2f(480, 500), _fScale, b2BodyType::b2_staticBody, "Ground.png", m_pWorld));

	//// 3 dynamic 'balls'
	//for (int i = 0; i < 1; i++)
	//{
	//	m_vpObjects.push_back(new Object(sf::Vector2f(550 + i * 100, 100), _fScale, b2BodyType::b2_dynamicBody, "Ball.png", m_pWorld));
	//}

	// Planet

	

	CPlanet* newPlanet = new CPlanet(sf::Vector2f(1000, 500), _fScale, m_pWorld, "Planet.png", b2BodyType::b2_staticBody, 1.0f);
	m_vpPlanets.push_back(newPlanet);
	m_vpGameObjects.push_back(newPlanet);

	CPlanet* newPlanet2 = new CPlanet(sf::Vector2f(750, 250), _fScale, m_pWorld, "Planet.png", b2BodyType::b2_dynamicBody, 0.5f);
	m_vpPlanets.push_back(newPlanet2);
	m_vpGameObjects.push_back(newPlanet2);

	CPlanet* newPlanet3 = new CPlanet(sf::Vector2f(100, 100), _fScale, m_pWorld, "Ball.png", b2BodyType::b2_dynamicBody, 1.0f);
	m_vpPlanets.push_back(newPlanet3);
	m_vpGameObjects.push_back(newPlanet3);

	

	newPlanet->GiveAsOrbital(newPlanet2->Getb2Body(), 25, 20);
	newPlanet2->GiveAsOrbital(newPlanet3->Getb2Body(), 90, 10);

	for (int i = 0; i < 10; i++)
	{
		m_vpGameObjects.push_back(new CNuclearPasta(sf::Vector2f(500 - i, 500 - i), _fScale, m_pWorld));
	}

	for (int i = 0; i < 20; i++)
	{
		CDestructable* newEnemy = new CEnemy(sf::Vector2f(500 + i, 300 + i), _fScale, m_pWorld);

		m_vpGameObjects.push_back(newEnemy);
		m_vpDestructableObjects.push_back(newEnemy);

		m_iEnemyCount++;

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

	/*for (size_t i = 0; i < m_vpObjects.size(); i++)
	{
		std::cout << m_vpObjects[i]->Getb2Body()->GetTransform().p.x << ", " << m_vpObjects[i]->Getb2Body()->GetTransform().p.y << std::endl;
	}*/

	for (size_t i = 0; i < m_vpPlanets.size(); i++)
	{
		for (size_t j = 0; j < m_vpGameObjects.size(); j++)
		{
			if (m_vpGameObjects[j]->GetObjectType() != EGAMEOBJECTTYPE::PLANET)
			{
				m_vpPlanets[i]->ExertGravitationalForceOn(m_vpGameObjects[j]);
			}
		}
	}

	DestroyObjectsMarkedForDestruction();

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

void CLevel::DestroyObjectsMarkedForDestruction()
{
	for (size_t i = 0; i < m_vpDestructableObjects.size(); i++)
	{
		if (m_vpDestructableObjects[i]->GetShouldDestroy())
		{
			std::cout << "Destroying" << std::endl;
			DestroyDestructable(m_vpDestructableObjects[i]);
		}
	}

	// Get rid of all nullptrs in the vector
	m_vpDestructableObjects.erase(std::remove(begin(m_vpDestructableObjects), end(m_vpDestructableObjects), nullptr), end(m_vpDestructableObjects));

	return;
}

void CLevel::DestroyDestructable(CDestructable* _pDestructable)
{
	// Erase it from the gameobject vector
	for (size_t i = 0; i < m_vpGameObjects.size(); i++)
	{
		if (m_vpGameObjects[i] == _pDestructable)
		{
			m_vpGameObjects.erase(m_vpGameObjects.begin() + i);

			// exit the loop
			i = m_vpGameObjects.size();
		}
	}

	// Nullify the pointer in the destructableobjects vector
	// Can not erase as it will mess up loop calling this function
	for (size_t i = 0; i < m_vpDestructableObjects.size(); i++)
	{
		if (m_vpDestructableObjects[i] == _pDestructable)
		{
			m_vpDestructableObjects[i] = nullptr;

			// exit the loop
			i = m_vpDestructableObjects.size();
		}
	}

	if (_pDestructable->GetObjectType() == EGAMEOBJECTTYPE::ENEMY)
	{
		m_iEnemyCount--;

		std::cout << m_iEnemyCount << std::endl;
	}

	// Actually delete the object
	delete _pDestructable;

	return;
}
