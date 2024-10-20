#include "SFML_TitleScreen.h"

SFML_TitleScreen::SFML_TitleScreen(std::string textureFileName, int windowWidth, int windowHeight)
{
	m_titleScreenTexture.loadFromFile(textureFileName);
	m_titleScreenSprite.setTexture(m_titleScreenTexture);

	sf::Vector2u bkTextureSize = m_titleScreenTexture.getSize();
	m_titleScreenSprite.setTextureRect(sf::IntRect(0, 0, bkTextureSize.x, bkTextureSize.y));

	m_titleScreenSprite.setPosition(0, 0);

	m_messageTexture.loadFromFile("media/textures/continue.png");
	m_messageSprite.setTexture(m_messageTexture);

	m_messageSprite.setPosition(windowWidth * 0.5f, windowHeight * 0.75f);
	sf::Vector2u msgTextureSize = m_messageTexture.getSize();
	m_messageSprite.setOrigin(msgTextureSize.x / 2, msgTextureSize.y / 2);

	m_messageSprite.setTextureRect(sf::IntRect(0, 0, msgTextureSize.x, msgTextureSize.y));
	m_messageSprite.setColor(sf::Color(255, 0, 0));

	m_timeSinceLastFlash = sf::Time::Zero;
	m_FlashingTime = sf::seconds(0.2f);
}

SFML_TitleScreen::~SFML_TitleScreen()
{
}

void SFML_TitleScreen::update(sf::Time elapsedTime)
{
	m_timeSinceLastFlash += elapsedTime;

	if (m_timeSinceLastFlash > m_FlashingTime)
	{
		m_flashon = !m_flashon;
		m_timeSinceLastFlash -= m_FlashingTime;

		if (m_flashon)
			m_messageSprite.setColor(sf::Color(255, 255, 255));
		else
			m_messageSprite.setColor(sf::Color(255, 0, 0));
	}
}

void SFML_TitleScreen::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_titleScreenSprite);
	target.draw(m_messageSprite);
}


