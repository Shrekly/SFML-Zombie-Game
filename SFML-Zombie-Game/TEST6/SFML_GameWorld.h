#pragma once
#include <SFML/Graphics.hpp>
#include "SFML_GameWorldLayer.h"
#include "SFML_SpriteObject.h"
#include "SFML_AnimatedSpriteObject.h"
#include "SFML_NPCSpriteObject.h"
#include "SFML_PlayableSpriteObject.h"
#include "SFML_BulletSpriteObject.h"

class SFML_GameWorld : public sf:: Drawable
{
public:
	SFML_GameWorld(int windowWidth, int windowHeight, sf::RenderWindow* parentWindow);
	~SFML_GameWorld();

	void update(float elapsedTime);

private:
	void processEvents(float elapsedTime);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int m_windowWidth;
	int m_windowHeight;

	std::vector<SFML_GameWorldLayer*> m_gameWorldLayerList;
	sf::Vector2f m_cameraPosition;
	
	static bool layerSortFunction(SFML_GameWorldLayer* a, SFML_GameWorldLayer* b);

	SFML_2DCamera m_camera;
	SFML_SpriteObject m_SpriteObject;
	sf::RenderWindow* m_parentWindow;

	SFML_AnimatedSpriteObject* m_animatedObject;
	int m_idleAnimationID;

	std::vector<SFML_NPCSpriteObject*> m_zombieCharacterList;
	int m_numberofZombies;

	SFML_PlayableSpriteObject* m_playerCharacter;
	std::vector<SFML_BulletSpriteObject*> m_bulletList;
};

