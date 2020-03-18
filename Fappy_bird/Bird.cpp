#include "Bird.h"


Bird::~Bird()
{
}

Bird::Bird()
	:m_gAccelerator(0, 0.3f), m_flyForce(0, -6.6f),
	m_moveOffset(0.0f, 0.0f), m_animation(m_textures, 3, 0.15f)
{
	m_sprite.setPosition(288 / 2 - 70, 512 / 2);

	m_textures.resize(3);
	m_textures[0].loadFromFile("sprites//yellowbird-downflap.png");
	m_textures[1].loadFromFile("sprites//yellowbird-midflap.png");
	m_textures[2].loadFromFile("sprites//yellowbird-upflap.png");

	
}

Sprite & Bird::getSprite()
{
	// TODO: insert return statement here
	return m_sprite;
}

bool Bird::isDead()
{
	return m_isDead;
}

void Bird::updateAnimation(float deltaTime)
{
	m_animation.Update(deltaTime);
	m_sprite.setTexture(m_animation.getCurrentTexture());
}

void Bird::flyUp()
{
	m_moveOffset = m_flyForce;
}

void Bird::fallDown()
{
	m_moveOffset += m_gAccelerator;
}

void Bird::move()
{
	m_sprite.move(m_moveOffset);
}

Vector2f Bird::getPosition()
{
	return m_sprite.getPosition();
}
