#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class SFML_SpriteObject : public sf::Drawable, public sf::Transformable
{
public:
	SFML_SpriteObject();
	virtual ~SFML_SpriteObject();

	bool setDefaultTexture(std::string textureFilename);
	bool setDefaultTexture(std::string textureFilename, std::string spriteInfoFilename);

	void setColour(const sf::Color& color);;

	sf::Vector2f getWorldPosition();
	sf::Vector2f getScreenPosition(sf::Transform cameraScreenTransform);

	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;

	virtual void update(float elapsedTime);

protected:
	sf::Sprite m_sprite;
	sf::Texture* m_spriteTexture;

	sf::IntRect m_textureRectangle;
	sf::Vector2f m_spriteOrigin;

	bool m_initialised;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Texture* m_defaultTexture;

};

