#pragma once
#include "SFML_SpriteAnimation.h"
#include "SFML_SpriteObject.h"

class SFML_AnimatedSpriteObject : public SFML_SpriteObject
{
public:
	SFML_AnimatedSpriteObject();
	virtual ~SFML_AnimatedSpriteObject();

	int addAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime);

	void setCurrentAnimation(int animationindex);

	SFML_SpriteAnimation* getCurrentAnimation();

	virtual void update(float elapsedTime);

	void play();
	void pause();
	void stop();

private:
	std::vector<sf::Texture*> m_spriteTextureList;
	int m_currentAnimationID;
	float m_currentTime;
	bool m_ispaused;

protected:
	std::vector<SFML_SpriteAnimation*> m_animatedSpriteList;
	SFML_SpriteAnimation* m_currentAnimation;
};

