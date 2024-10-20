#include "SFML_GameWorldLayer.h"
#include "SFML_GameWorld.h"

SFML_GameWorldLayer::SFML_GameWorldLayer(std::string textureFileName, float parallaxFactor, int viewportWidth, int viewportHeight)
	: m_layerTexture()
	, m_layerVertices(sf::Quads, 4)
	, m_parallaxFactor(parallaxFactor)
	, m_offset()
	, m_scrollSpeed()
{
	if (m_layerTexture.loadFromFile(textureFileName))
	{
		m_layerTexture.setRepeated(true);

		m_layerVertices[0].position = sf::Vector2f(0.f, 0.f);
		m_layerVertices[1].position = sf::Vector2f(0.f, viewportHeight);
		m_layerVertices[2].position = sf::Vector2f(viewportWidth, viewportHeight);
		m_layerVertices[3].position = sf::Vector2f(viewportWidth, 0.f);
	}
}

SFML_GameWorldLayer:: ~SFML_GameWorldLayer()
{
	
}

void SFML_GameWorldLayer::followCamera(SFML_2DCamera* camera)
{
	sf::FloatRect cameraWindows = camera->getCameraWindow(m_parallaxFactor);

	int left = cameraWindows.left + m_offset.x;
	int right = cameraWindows.left + cameraWindows.width + m_offset.x;
	int top = cameraWindows.top + m_offset.y;
	int bottom = cameraWindows.top + cameraWindows.height + m_offset.y;

	m_layerVertices[0].texCoords = sf::Vector2f(left, top);
	m_layerVertices[1].texCoords = sf::Vector2f(left, bottom);
	m_layerVertices[2].texCoords = sf::Vector2f(right, bottom);
	m_layerVertices[3].texCoords = sf::Vector2f(right, top);
}

void SFML_GameWorldLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &m_layerTexture;

	target.draw(m_layerVertices, states);
}

void SFML_GameWorldLayer::setParallaxFactor(float parallaxFactor)
{
	m_parallaxFactor = parallaxFactor;
}

float SFML_GameWorldLayer::getParallaxFactor()
{
	return m_parallaxFactor;
}

void SFML_GameWorldLayer::update(float elapsedTime)
{
	m_offset = m_offset + elapsedTime * m_scrollSpeed;
}

void SFML_GameWorldLayer::setScrollSpeed(sf::Vector2f scrollSpeed)
{
	m_scrollSpeed = scrollSpeed;
}