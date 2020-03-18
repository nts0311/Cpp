#include "Pipe.h"
#include <cstdlib>
#include <ctime>


int Pipe::getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);  // static used for efficiency, so we only calculate this value once
	// evenly distribute the random number across our range
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}


Pipe::~Pipe()
{
}

Pipe::Pipe()
{
}
//good version
/*Pipe::Pipe(const Vector2f & position, Texture &texture)
	:m_position(position), m_width(52.f), m_height(450.f), m_gapStart(getRandomNumber(50, 300)), m_moveSpeed(-1.f, 0.f),
	m_gapWidth(100.f),
	m_texture(), 
	m_upSprite(texture, IntRect(0.f, 0.f, m_width, m_gapStart)),
	m_downSprite(texture, IntRect(0.f, 0.f, m_width, m_height - m_gapStart - m_gapWidth))
{
	m_texture.loadFromFile("sprites//pipe-green.png");

	m_upSprite.rotate(180.f);
	m_upSprite.setPosition(m_position.x + m_width, m_gapStart);
	m_downSprite.setPosition(m_position.x, m_gapStart + m_gapWidth);
}*/

Pipe::Pipe(const Vector2f & position, Texture &texture)
	:m_position(position), m_width(52.f), m_height(450.f), m_gapStart(getRandomNumber(50, 300)), m_moveSpeed(-1.5f, 0.f),
	m_gapWidth(110.f), m_isScored(false)
	//m_texture(),
	//m_upSprite(texture, IntRect(0.f, 0.f, m_width, m_gapStart)),
	//m_downSprite(texture, IntRect(0.f, 0.f, m_width, m_height - m_gapStart - m_gapWidth))
{
	m_upSprite.setTexture(texture);
	m_downSprite.setTexture(texture);

	drawPipe();
}



/*Pipe::Pipe(const Pipe & other)
	:m_position(other.getPosition()), m_moveSpeed(-3.f,0),
{
}*/

Sprite & Pipe::getUpSprite()
{
	// TODO: insert return statement here
	return m_upSprite;
}

Sprite & Pipe::getDownSprite()
{
	// TODO: insert return statement here
	return m_downSprite;
}

Vector2f Pipe::getPosition() const
{
	//return Vector2f(m_downSprite.getPosition().x, m_downSprite.getPosition().y - m_gapWidth - m_gapStart);
	return m_position;
}

void Pipe::moveLeft()
{
	m_downSprite.move(m_moveSpeed);
	m_upSprite.move(m_moveSpeed.x , m_moveSpeed.y);

	m_position += m_moveSpeed;
}

void Pipe::drawPipe()
{
	m_upSprite.setTextureRect(IntRect(0.f, 0.f, m_width, m_gapStart));
	m_downSprite.setTextureRect(IntRect(0.f, 0.f, m_width, m_height - m_gapStart - m_gapWidth));
	m_upSprite.rotate(180.f);
	m_upSprite.setPosition(m_position.x + m_width, m_gapStart);
	m_downSprite.setPosition(m_position.x, m_gapStart + m_gapWidth);
}
