#pragma once
#include <SFML/Graphics.hpp>
class SFML_2DCamera
{
public:
	SFML_2DCamera(int projectionWindowWidth, int projectionWindowHeight);
	~SFML_2DCamera();

	sf::FloatRect getCameraWindow(float parallaxFactor);
	void setPosition(sf::Vector2f target);

	void zoomUp(float elapsedTime);
	void zoomDown(float elapsedTime);

	sf::Transform getViewTransform() const;
	sf::Transform getProjTransform() const;

private:
	sf::Vector2f m_cameraWindowSize;
	sf::Vector2f m_cameraPosition;
	
	float m_cameraZoom;
};

