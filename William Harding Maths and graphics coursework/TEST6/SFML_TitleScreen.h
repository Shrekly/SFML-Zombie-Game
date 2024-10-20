#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class SFML_TitleScreen : public Drawable
{
public:
	SFML_TitleScreen(std::string texturefilename, int windowWidth, int windowHeight);
	~SFML_TitleScreen();

	void update(sf::Time elapsedTime);
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Texture m_titleScreenTexture;
	sf::Sprite m_titleScreenSprite;

	sf::Texture m_messageTexture;
	sf::Sprite m_messageSprite;

	sf::Time m_FlashingTime;
	sf::Time m_timeSinceLastFlash;
	bool m_flashon;


};

