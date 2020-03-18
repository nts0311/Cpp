#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"

using namespace sf;
using namespace std;

class Bird
{
private:
	Vector2f m_moveOffset;
	Vector2f m_gAccelerator;
	Vector2f m_flyForce;

	vector<Texture> m_textures;
	Animation m_animation;
	Sprite m_sprite;

	bool m_isDead;

public:
	~Bird();

	Bird();

	Sprite& getSprite();
	bool isDead();

	void updateAnimation(float deltaTime);
	void flyUp();
	void fallDown();
	void move();

	Vector2f getPosition();
};

