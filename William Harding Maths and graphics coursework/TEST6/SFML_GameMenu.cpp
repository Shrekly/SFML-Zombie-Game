#include "SFML_GameMenu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

SFML_GameMenu::SFML_GameMenu(std::string menufilename, int windowWidth, int windowHeight)
{
	std::ifstream inputFile(menufilename);
	if (inputFile.is_open())
	{
		std::string stringLine;
		//first line
		std::getline(inputFile, stringLine);
		if(inputFile.good())
		{
			m_backgroundTexture.loadFromFile(stringLine);
			m_backgroundSprite.setTexture(m_backgroundTexture);

			sf::Vector2u textureSize = m_backgroundTexture.getSize();
			m_backgroundSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
			m_backgroundSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
			m_backgroundSprite.setPosition(0, 0);


			m_backgroundRect.left = -static_cast<float> (textureSize.x / 2);
			m_backgroundRect.top = -static_cast<float> (textureSize.y / 2);
			m_backgroundRect.width = textureSize.x;
			m_backgroundRect.height = textureSize.y;
		}

		//second line
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			m_logo.loadFromFile(stringLine);
			m_logoSprite.setTexture(m_logo);

			sf::Vector2u textureSize = m_logo.getSize();
			m_logoSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
			m_logoSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
			m_logoSprite.setPosition(0, m_backgroundTexture.getSize().y / 2 * 0.9f);
		}

		//third line
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			m_gameFont.loadFromFile(stringLine);
		}

		std::string redString;
		std::string greenString;
		std::string blueString;

		int redInt;
		int greenInt;
		int blueInt;

		//fourth line
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			m_normalTextColour = sf::Color(redInt, greenInt, blueInt);
		}

		//fifth line
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			m_normalOutlineColour = sf::Color(redInt, greenInt, blueInt);
		}

		//sixth line
		std::getline(inputFile, stringLine);

		if (inputFile.good())
		{
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			m_highlightTextColour = sf::Color(redInt, greenInt, blueInt);
		}

		//seventh line
		std::getline(inputFile, stringLine);

		if (inputFile.good())
		{
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			m_highlightOutlineColour = sf::Color(redInt, greenInt, blueInt);
		}

		//eight line
		std::string xBorderString;
		std::string yBorderString;

		int xBorderInt;
		int yBorderInt;

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			std::istringstream stringStream(stringLine);
			stringStream >> xBorderString;
			stringStream >> yBorderString;

			xBorderInt = std::stoi(xBorderString);
			yBorderInt = std::stoi(yBorderString);

			m_menuItemBorder.x = xBorderInt;
			m_menuItemBorder.y = yBorderInt;
		}

		m_menuAlignment = CENTRE_JUSTIFIED;

		//ninth line
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			if (!std::strcmp(stringLine.c_str(), "LEFT_JUSTIFIED"))
				m_menuAlignment = LEFT_JUSTIFIED;
			else if (!std::strcmp(stringLine.c_str(), "CENTRE_JUSTIFIED"))
				m_menuAlignment = CENTRE_JUSTIFIED;
			else if (!std::strcmp(stringLine.c_str(), "RIGHT_JUSTIFIED"))
				m_menuAlignment = RIGHT_JUSTIFIED;
		}

		//next lines
		sf::Text start;
		start.setFont(m_gameFont);
		start.setCharacterSize(50);
		start.setStyle(sf::Text::Bold);
		start.setFillColor(m_normalTextColour);
		start.setOutlineColor(m_normalOutlineColour);
		start.setOutlineThickness(1.0f);

		sf::Vector2f textpos;

		if (m_menuAlignment == CENTRE_JUSTIFIED)
		{
			textpos.x = m_backgroundRect.left + m_backgroundRect.width / 2;
			textpos.y = m_backgroundRect.top + m_menuItemBorder.y;
		}
		else if (m_menuAlignment == LEFT_JUSTIFIED)
		{
			textpos.x = m_backgroundRect.left + m_menuItemBorder.x;
			textpos.y = m_backgroundRect.top + m_menuItemBorder.y;
		}
		else if (m_menuAlignment == RIGHT_JUSTIFIED)
		{
			textpos.x = m_backgroundRect.left + m_backgroundRect.width - m_menuItemBorder.x;
			textpos.y = m_backgroundRect.top + m_menuItemBorder.y;
		}

		do
		{
			std::getline(inputFile, stringLine);
			if (inputFile.good())
			{
				start.setPosition(textpos.x, textpos.y);

				start.setString(stringLine);

				sf::FloatRect textbox = start.getLocalBounds();
				if (m_menuAlignment == CENTRE_JUSTIFIED) 
				{
					start.setOrigin(textbox.width / 2, textbox.height / 2);
				}
				else if (m_menuAlignment == LEFT_JUSTIFIED)
				{
					start.setOrigin(0, textbox.height / 2);
				}
				else if (m_menuAlignment == RIGHT_JUSTIFIED)
				{
					start.setOrigin(textbox.width, textbox.height / 2);
				}

				m_menuText.push_back(start);

				textpos.y += start.getLocalBounds().height * 1.2f;
			}
			else
				break;
		} while (true);

		m_highlightIndex = 0;
		m_menuText[m_highlightIndex].setFillColor(m_highlightTextColour);
		m_menuText[m_highlightIndex].setOutlineColor(m_highlightOutlineColour);

		m_prevDownKeyPressed = true;
		m_prevUpKeyPressed = true;
		m_prevReturnKeyPressed = true;
		
		inputFile.close();
	}
}

SFML_GameMenu::~SFML_GameMenu()
{
	m_menuText.clear();
}

void SFML_GameMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	states.transform *= getTransform();
	target.draw(m_backgroundSprite, states);
	target.draw(m_logoSprite, states);

	for (std::size_t count = 0; count < m_menuText.size(); count++)
		target.draw(m_menuText[count], states);
}

int SFML_GameMenu::update(sf::Time elapsedTime) 
{
	bool m_currentDownKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	bool m_currentUpKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	bool m_currentReturnKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Return);

	if (m_currentDownKeyPressed && !m_prevDownKeyPressed) 
	{
		m_menuText[m_highlightIndex].setFillColor(m_normalTextColour);
		m_menuText[m_highlightIndex].setOutlineColor(m_normalOutlineColour);

		m_highlightIndex++;
		m_highlightIndex = m_highlightIndex % m_menuText.size();

		m_menuText[m_highlightIndex].setFillColor(m_highlightTextColour);
		m_menuText[m_highlightIndex].setOutlineColor(m_highlightOutlineColour);
	}

	else if (m_currentUpKeyPressed && !m_prevUpKeyPressed)
	{
		m_menuText[m_highlightIndex].setFillColor(m_normalTextColour);
		m_menuText[m_highlightIndex].setOutlineColor(m_normalOutlineColour);

		m_highlightIndex--;
		if (m_highlightIndex < 0)
			m_highlightIndex = m_highlightIndex + m_menuText.size();

		m_menuText[m_highlightIndex].setFillColor(m_highlightTextColour);
		m_menuText[m_highlightIndex].setOutlineColor(m_highlightOutlineColour);
	}

	m_prevDownKeyPressed = m_currentDownKeyPressed;
	m_prevUpKeyPressed = m_currentUpKeyPressed;

	bool hasSelected = false;

	if (m_currentReturnKeyPressed && !m_prevReturnKeyPressed)
		hasSelected = true;

	m_prevReturnKeyPressed = m_currentReturnKeyPressed;

	if (hasSelected)
		return m_highlightIndex;
	else
		return -1;
}
