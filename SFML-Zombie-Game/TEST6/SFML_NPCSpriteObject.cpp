#include "SFML_NPCSpriteObject.h"
#include "SFML_GameWorld.h"


SFML_NPCSpriteObject::SFML_NPCSpriteObject()
	: m_targetLocation(0, 0)
	, m_moveSpeed(100.0f)
	, m_state(IDLE)
	, m_idleAnimationID(-1)
	, m_walkingAnimationID(-1)
	, m_attackingAnimationID(-1)
	, m_visionConeAngle(90.0f)
	, m_visionRange(1200.0f)
{

}

SFML_NPCSpriteObject::~SFML_NPCSpriteObject()
{
}

int SFML_NPCSpriteObject::setIdleAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_idleAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_idleAnimationID;
}

int	SFML_NPCSpriteObject::setWalkingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_walkingAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_walkingAnimationID;
}

int SFML_NPCSpriteObject::setAttackingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_attackingAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_attackingAnimationID;
}

void SFML_NPCSpriteObject::toIdleState()
{
	m_state = IDLE;
	setCurrentAnimation(m_idleAnimationID);
}

void SFML_NPCSpriteObject::toWalkingState()
{
	m_state = WALKING;
	setCurrentAnimation(m_walkingAnimationID);
}

void SFML_NPCSpriteObject::toAttackingState()
{
	m_state = ATTACKING;
	setCurrentAnimation(m_attackingAnimationID);
}

void SFML_NPCSpriteObject::setTargetLocation(sf::Vector2f targetLocation)
{
	m_targetLocation = targetLocation;
}

void SFML_NPCSpriteObject::setMovementSpeed(float speed)
{
	m_moveSpeed = speed;
}

void SFML_NPCSpriteObject::update(float elapsedTime)
{
	const float PI = 3.1415f;

	sf::Vector2f currentPosition = getPosition();

	sf::Vector2f faceDirection = m_targetLocation - currentPosition;

	float distance = sqrt(faceDirection.x * faceDirection.x + faceDirection.y * faceDirection.y);

	if (distance < elapsedTime * m_moveSpeed)
	{
		setPosition(m_targetLocation);
		toIdleState();
	}
	else
	{
		float angle = atan2(faceDirection.y, faceDirection.x);
		setRotation(angle / PI * 180);

		sf::Vector2f unitMoveVector = sf::Vector2f(cos(angle), sin(angle));
		sf::Vector2f totalMoveVector = unitMoveVector * elapsedTime * m_moveSpeed;
		move(totalMoveVector);

		toWalkingState();
	}

	SFML_AnimatedSpriteObject::update(elapsedTime);
}

bool SFML_NPCSpriteObject::isInVision(sf::Vector2f targetpoint)
{
	const float PI = 3.1415f;

	sf::Vector2f currentPosition = getPosition();
	sf::Vector2f vector = targetpoint - currentPosition;
	float distance = sqrt(vector.x * vector.x + vector.y * vector.y);

	if (distance > m_visionRange)
		return false;

	float faceAngle = getRotation();
	float targetAngle = atan2(vector.y, vector.x);
	targetAngle = targetAngle * 180 / PI;

	while (targetAngle > 360)
		targetAngle = targetAngle - 360;
	while (targetAngle < 0)
		targetAngle = targetAngle + 360;

	float angleDifference = fabs(targetAngle - faceAngle);

	if (angleDifference <= m_visionConeAngle / 2)
		return true;
	else
		return false;
}
