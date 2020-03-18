#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;

class Pipe
{
private:
	Vector2f m_position;
	Vector2f m_moveSpeed;
	float m_gapWidth;
	float m_gapStart;

	float m_width;
	float m_height;

	Texture m_texture;
	Sprite m_upSprite;
	Sprite m_downSprite;

public:
	bool m_isScored;

private:
	static int getRandomNumber(int min, int max);

public:
	~Pipe();
	Pipe();

	Pipe(const Vector2f& position, Texture &texture);
	//Pipe(const Pipe& other);
	Sprite& getUpSprite();
	Sprite& getDownSprite();

	Vector2f getPosition() const;
	void moveLeft();

	void drawPipe();

	float getGapStart() { return m_gapStart; }
	float getGapWidth() { return m_gapWidth; }
	float getHeight() { return m_height; }
	float getWidth() { return m_width; }
};

