#pragma once
#include <SFML/Graphics.hpp>

class SFML_SpriteAnimation
{
public:
	SFML_SpriteAnimation();
	~SFML_SpriteAnimation();

	void setSpriteSheet(sf::Texture* spriteTexture);
	void addFrame(sf::IntRect textureRect, sf::Vector2f centre);
	bool getCurrentFrame(sf::IntRect* rect, sf::Vector2f* centre);
	void setFrameTime(float timeperFrame);
	float getFrameTime();
	float getTimePerFrame();
	sf::Texture* getSpriteSheet();

	int getNumberofFrames();
	void getTextureInfo(int newFrame, sf::IntRect* rect, sf::Vector2f* centre);

	void setLoop(bool loop);
	bool isLooped() const;

	void setCanbeInterrupted(bool trueorfalse);
	bool canbeInterrupted() const;

	void incrementFrameNumber();
	int getCurrentFrameNumber();
	void resetCurrentAnimation();

	bool isCompleted();

private:
	std::vector<sf::IntRect> m_frameRectangleList;
	std::vector<sf::Vector2f> m_frameCentreList;

	sf::Texture* m_spritesheet;

	int m_currentFrameNumber;
	float m_timeperFrame;

	bool m_isLoop;
	bool m_canbeInterrupted;
};

