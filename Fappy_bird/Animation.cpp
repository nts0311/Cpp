#include "Animation.h"


Animation::Animation(vector<Texture>& textures, int totalImage, float switchTime)
	:m_textures(textures), m_totalImage(totalImage), m_switchTime(switchTime), 
	m_currentImageIndex(0), m_totalTime(0.0f)
{
}

Animation::~Animation()
{
}

void Animation::Update(float deltaTime)
{
	m_totalTime += deltaTime;

	if (m_totalTime >= m_switchTime)
	{
		m_totalTime -= m_switchTime;
		m_currentImageIndex++;
	}

	if (m_currentImageIndex >= m_totalImage)
		m_currentImageIndex = 0;
}

Texture & Animation::getCurrentTexture()
{
	// TODO: insert return statement here
	return m_textures[m_currentImageIndex];
}
