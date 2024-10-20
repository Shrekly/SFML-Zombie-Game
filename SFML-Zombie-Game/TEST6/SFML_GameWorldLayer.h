#pragma once
#include <SFML/Graphics.hpp>
#include "SFML_2DCamera.h"

class SFML_GameWorldLayer : public sf::Drawable
{
public:
	SFML_GameWorldLayer(std::string textureFileName, float parallaxFactor, int viewportWidth, int viewportHeight);
	~SFML_GameWorldLayer();

	void followCamera(SFML_2DCamera* camera);

	void setParallaxFactor(float parallaxFactor);
	float getParallaxFactor();

	void update(float elapsedTime);

	void setScrollSpeed(sf::Vector2f scrollSpeed);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Texture m_layerTexture;
	sf::VertexArray m_layerVertices;

	sf::Vector2f m_offset;
	sf::Vector2f m_scrollSpeed;

	float m_parallaxFactor;
};

