#include "CMeteor.h"

CMeteor::CMeteor()
{
	m_EGameObjectType = EGAMEOBJECTTYPE::METEOR;

	// Set the sprite
	m_texture.loadFromFile("Resources/Sprites/Asteroid.png");
	m_sprite.setTexture(m_texture);
	float fOriginX = (m_texture.getSize().x / 2);
	float fOriginY = (m_texture.getSize().y / 2);
	m_sprite.setOrigin(fOriginX, fOriginY);
}

CMeteor::~CMeteor()
{
}

void CMeteor::ActivateSpecialAbility(sf::RenderWindow& _window, float _fScale, std::vector<CGameObject*>& _vpGameObjects)
{
	if (m_pBody != nullptr)
	{
		int iNumOfNewSpawns = 4;
		for (int i = 0; i < iNumOfNewSpawns; i++)
		{
			CMeteor* newMeteor = new CMeteor();

			sf::Vector2f v2fNewPosition = m_sprite.getPosition();
			v2fNewPosition.x += float(i * 20);
			v2fNewPosition.y += float(i * 20);

			newMeteor->Launch(_fScale, v2fNewPosition, *m_pBody->GetWorld());

			b2Vec2 v2fForce = m_pBody->GetLinearVelocity();
			v2fForce.x *= m_pBody->GetMass();
			v2fForce.y *= m_pBody->GetMass();

			// So they explode outwards
			v2fForce = RotateVector(v2fForce, float(360.0f / (iNumOfNewSpawns + 1) * i));

			v2fForce *= 2.0f;

			newMeteor->Getb2Body()->ApplyLinearImpulseToCenter(v2fForce, true);

			_vpGameObjects.push_back(newMeteor);
		}
	}
	
	

	return;
}

float CMeteor::ConvertToRadians(float _fDegrees)
{
	return ((_fDegrees * b2_pi) / 180.0f);
}

b2Vec2 CMeteor::RotateVector(b2Vec2 _v2f, float _degrees)
{
	float fRadians = ConvertToRadians(_degrees);

	// 2D anticclockwise rotation matrix
	// | cos(theta)     -sin(theta) |
	// | sin(theta)      cos(theta) |
	float fRotationMatrix[2][2];
	fRotationMatrix[0][0] = cos(fRadians);
	fRotationMatrix[0][1] = -sin(fRadians);

	fRotationMatrix[1][0] = sin(fRadians);
	fRotationMatrix[1][1] = cos(fRadians);

	// Rotation Matrix * Vector
	// | a    b | * | x |
	// | c    d |   | y |
	// =
	// | (ax + by) |
	// | (cx + dy) |

	b2Vec2 v2fRotated;

	v2fRotated.x = fRotationMatrix[0][0] * _v2f.x + fRotationMatrix[0][1] * _v2f.y;
	v2fRotated.y = fRotationMatrix[1][0] * _v2f.x + fRotationMatrix[1][1] * _v2f.y;

	return (v2fRotated);
}
