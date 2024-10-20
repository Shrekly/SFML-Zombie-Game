#include "SFML_AnimatedSpriteObject.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

SFML_AnimatedSpriteObject::SFML_AnimatedSpriteObject()
	: m_currentAnimation(NULL)
	, m_ispaused(false)
	, m_currentAnimationID(-1)
{

}

SFML_AnimatedSpriteObject::~SFML_AnimatedSpriteObject()
{
	for (std::vector<sf::Texture*>::iterator it = m_spriteTextureList.begin();
		it != m_spriteTextureList.end(); ++it)
	{
		delete(*it);
	}

	m_spriteTextureList.clear();

	for (std::vector<SFML_SpriteAnimation*>::iterator it = m_animatedSpriteList.begin();
		it != m_animatedSpriteList.end(); ++it)
	{
		delete(*it);
	}

	m_animatedSpriteList.clear();
}

int SFML_AnimatedSpriteObject::addAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	sf::Texture* spriteTexture = new sf::Texture();

	if (!spriteTexture->loadFromFile(spriteSheetFilename))
	{
		return -1;
	}


	m_spriteTextureList.push_back(spriteTexture);

	SFML_SpriteAnimation* animation = new SFML_SpriteAnimation();

	animation->setSpriteSheet(spriteTexture);

	std::string left;
	std::string top;
	std::string width;
	std::string height;
	std::string xcentre;
	std::string ycentre;

	int ileft, itop, iwidth, iheight, ixcentre, iycentre;

	int frameCounter = 0;

	std::ifstream inputFile(spriteInfoFilename);

	if (inputFile.is_open())
	{
		do {
			std::string stringLine;
			std::getline(inputFile, stringLine);

			if (inputFile.good())
			{
				std::istringstream stringStream(stringLine);

				stringStream >> left;
				stringStream >> top;
				stringStream >> width;
				stringStream >> height;
				stringStream >> xcentre;
				stringStream >> ycentre;

				ileft = std::stoi(left);
				itop = std::stoi(top);
				iwidth = std::stoi(width);
				iheight = std::stoi(height);
				ixcentre = std::stoi(xcentre);
				iycentre = std::stoi(ycentre);

				animation->addFrame(sf::IntRect(ileft, itop, iwidth, iheight), sf::Vector2f(ixcentre - ileft, iycentre - itop));

				frameCounter++;
			}
			else
				break;
		} while (true);
		
		inputFile.close();
	}

	if (frameCounter > 0)
	{
		animation->setFrameTime(animationTime / frameCounter);
		m_animatedSpriteList.push_back(animation);
		m_initialised = true;
		return m_animatedSpriteList.size() - 1;
	}
	else
		return -1;

}

void SFML_AnimatedSpriteObject::setCurrentAnimation(int animationindex)
{
	SFML_SpriteAnimation* newAnimation = m_animatedSpriteList[animationindex];

	if (newAnimation)
	{
		if (m_currentAnimation != newAnimation)
		{
			m_currentAnimation = newAnimation;
			m_spriteTexture = m_currentAnimation->getSpriteSheet();
			m_currentAnimation->resetCurrentAnimation();
			m_currentAnimation->getCurrentFrame(&m_textureRectangle, &m_spriteOrigin);
			m_currentTime = 0;
		}
	}
}

SFML_SpriteAnimation* SFML_AnimatedSpriteObject::getCurrentAnimation()
{
	return m_currentAnimation;
}

void SFML_AnimatedSpriteObject::play()
{
	m_ispaused = false;
}

void SFML_AnimatedSpriteObject::pause()
{
	m_ispaused = true;
}

void SFML_AnimatedSpriteObject::stop()
{
	m_ispaused = true;
	m_currentTime = 0;
}

void SFML_AnimatedSpriteObject::update(float elapsedTime)
{
	if (!m_ispaused && m_currentAnimation)
	{
		float frameTime = m_currentAnimation->getTimePerFrame();

		m_currentTime += elapsedTime;

		if (m_currentTime >= frameTime)
		{
			m_currentAnimation->incrementFrameNumber();
			m_currentAnimation->getCurrentFrame(&m_textureRectangle, &m_spriteOrigin);
			m_currentTime = m_currentTime - frameTime;
		}
	}
	SFML_SpriteObject::update(elapsedTime);
}