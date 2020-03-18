#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

class Animation
{
public:
	Animation(vector<Texture> &textures, int totalImage, float switchTime);
	~Animation();

	void Update(float deltaTime);//deltaTime is the time between a image and next image
	Texture& getCurrentTexture();

private:
	int m_totalImage;
	int m_currentImageIndex;

	float m_totalTime;
	float m_switchTime;//time of each image

	vector<Texture> &m_textures;
	Texture m_currentTexture;
};

