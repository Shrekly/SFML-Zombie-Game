#include "SFML_GameWorld.h"


SFML_GameWorld::SFML_GameWorld(int windowWidth, int windowHeight, sf::RenderWindow* parentWindow)
	:m_windowWidth(windowWidth)
	, m_windowHeight(windowHeight)
	, m_camera(windowWidth, windowHeight)
{

	//declares all background images so that there is a background
	SFML_GameWorldLayer* background = new SFML_GameWorldLayer("media/textures/wall.png", 1.0f, windowWidth, windowHeight);
	m_gameWorldLayerList.push_back(background);

	m_cameraPosition = sf::Vector2f(0, 0);

	SFML_GameWorldLayer* foreground = new SFML_GameWorldLayer("media/textures/wire.png", 0.3f, windowWidth, windowHeight);
	m_gameWorldLayerList.push_back(foreground);

	SFML_GameWorldLayer* fog = new SFML_GameWorldLayer("media/textures/fog.png", 0.8f, windowWidth, windowHeight);
	m_gameWorldLayerList.push_back(fog);

	//calls the layer sort function so it get called in the right order
	std::sort(m_gameWorldLayerList.begin(), m_gameWorldLayerList.end(), layerSortFunction);

	//Sets the player object's texture
	m_SpriteObject.setDefaultTexture("media/textures/soldier.png", "media/spriteInfo/soldier.txt");
	m_SpriteObject.setPosition(0, 0);

	m_animatedObject = new SFML_AnimatedSpriteObject();

	m_idleAnimationID = m_animatedObject->addAnimation("media/textures/hero_flashlight_idle.png", "media/spriteInfo/hero_flashlight_idle.txt", 1.0f);

	m_parentWindow = parentWindow;

	m_animatedObject->setPosition(0, 0);
	m_animatedObject->setCurrentAnimation(m_idleAnimationID);

	//Declares all the zombie animations and the number of zombies and set's their target location
	m_numberofZombies = 10;
	for (int i = 0; i < m_numberofZombies; i++)
	{
		SFML_NPCSpriteObject* npcSprite = new SFML_NPCSpriteObject();
		npcSprite->setIdleAnimation("media/textures/zombie-idle.png", "media/spriteInfo/zombie-idle.txt", 1.0f);
		npcSprite->setWalkingAnimation("media/textures/zombie-move.png", "media/spriteInfo/zombie-move.txt", 1.0f);
		npcSprite->setAttackingAnimation("media/textures/zombie-attack.png", "media/spriteInfo/zombie-attack.txt", 1.0f);

		npcSprite->setPosition(rand() % 4000 - 2000, rand() % 4000 - 2000);
		npcSprite->setTargetLocation(sf::Vector2f(rand() % 4000 - 2000, rand() % 4000 - 2000));
		m_zombieCharacterList.push_back(npcSprite);
	}

	//declare all player character animations and sets the files up to the functions
	m_playerCharacter = new SFML_PlayableSpriteObject();

	m_playerCharacter->setFlashlightIdleAnimation("media/textures/hero_flashlight_idle.png", "media/spriteInfo/hero_flashlight_idle.txt", 1.0f);
	m_playerCharacter->setFlashlightWalkingAnimation("media/textures/hero_flashlight_move.png", "media/spriteInfo/hero_flashlight_move.txt", 1.0f);
	m_playerCharacter->setFlashlightMeleeAnimation("media/textures/hero_flashlight_melee.png", "media/spriteInfo/hero_flashlight_melee.txt", 1.0f);

	m_playerCharacter->setRifleIdleAnimation("media/textures/hero_rifle_idle.png", "media/spriteInfo/hero_rifle_idle.txt", 1.0f);
	m_playerCharacter->setRifleWalkingAnimation("media/textures/hero_rifle_move.png", "media/spriteInfo/hero_rifle_move.txt", 1.0f);
	m_playerCharacter->setRifleMeleeAnimation("media/textures/hero_rifle_melee.png", "media/spriteInfo/hero_rifle_melee.txt", 1.0f);
	m_playerCharacter->setRifleShootAnimation("media/textures/hero_rifle_shoot.png", "media/spriteInfo/hero_rifle_shoot.txt", 1.0f);

	m_playerCharacter->setKnifeIdleAnimation("media/textures/hero_knife_idle.png", "media/spriteInfo/hero_knife_idle.txt", 1.0f);
	m_playerCharacter->setKnifeWalkingAnimation("media/textures/hero_knife_move.png", "media/spriteInfo/hero_knife_move.txt", 1.0f);
	m_playerCharacter->setKnifeMeleeAnimation("media/textures/hero_knife_melee.png", "media/spriteInfo/hero_knife_melee.txt", 1.0f);

	m_playerCharacter->setPistolIdleAnimation("media/textures/hero_pistol_idle.png", "media/spriteInfo/hero_pistol_idle.txt", 1.0f);
	m_playerCharacter->setPistolWalkingAnimation("media/textures/hero_pistol_move.png", "media/spriteInfo/hero_pistol_move.txt", 1.0f);
	m_playerCharacter->setPistolMeleeAnimation("media/textures/hero_pistol_melee.png", "media/spriteInfo/hero_pistol_melee.txt", 1.0f);
	m_playerCharacter->setPistolShootAnimation("media/textures/hero_pistol_shoot.png", "media/spriteInfo/hero_pistol_shoot.txt", 1.0f);

	m_playerCharacter->equipFlashlight();
	m_playerCharacter->toIdleState();

	m_playerCharacter->setPosition(0, 0);
}

SFML_GameWorld::~SFML_GameWorld()
{
	//make sure to clear memory when the game closes
	for (std::vector<SFML_GameWorldLayer*>::iterator it = m_gameWorldLayerList.begin();
		it != m_gameWorldLayerList.end(); it++)
	{
		delete(*it);
	}
	m_gameWorldLayerList.clear();
	delete m_animatedObject;
}

void SFML_GameWorld::processEvents(float elapsedTime)
{
	/*float cameraPanSpeed = 60.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_cameraPosition.x = m_cameraPosition.x - cameraPanSpeed * elapsedTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_cameraPosition.x = m_cameraPosition.x + cameraPanSpeed * elapsedTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_cameraPosition.y = m_cameraPosition.y - cameraPanSpeed * elapsedTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_cameraPosition.y = m_cameraPosition.y + cameraPanSpeed * elapsedTime;
	}*/

	//Controls code

	//Camera zooms in and out when the add or subtract is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
	{
		m_camera.zoomUp(elapsedTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
	{
		m_camera.zoomDown(elapsedTime);
	}

	//when a number key is pressed it will change over to the next weapon
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		m_playerCharacter->equipRifle();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		m_playerCharacter->equipKnife();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		m_playerCharacter->equipPistol();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		m_playerCharacter->equipFlashlight();
	}

	//highlights player and zombie when hovered over
	sf::Transform transform;
	transform = m_camera.getProjTransform() * m_camera.getViewTransform();


	sf::Transform inv = transform.getInverse();

	sf::Vector2f mouseScreenPosition = sf::Vector2f(sf::Mouse::getPosition(*m_parentWindow));

	sf::Vector2f wp = inv.transformPoint(mouseScreenPosition);

	sf::FloatRect rect = m_SpriteObject.getGlobalBounds();

	//Checks if the zombie is in the vision cone of the player
	for (unsigned int counter = 0; counter < m_zombieCharacterList.size(); counter++)
	{
		if (m_zombieCharacterList[counter]->isInVision(wp)) 
		{
			m_zombieCharacterList[counter]->setColour(sf::Color(128, 0, 0));
		}
		else
		{
			m_zombieCharacterList[counter]->setColour(sf::Color(255, 255, 255));
		}
	}

	//if (rect.contains(wp))
	//{
	//	m_SpriteObject.setColour(sf::Color(255, 0, 0));
	//}
	//else
	//{
	//	m_SpriteObject.setColour(sf::Color(255, 255, 255));
	//}

	//shoots bullet where the mouse is placed
	SFML_BulletSpriteObject* bullet = m_playerCharacter->processEvents(elapsedTime, transform, mouseScreenPosition);
	if (bullet)
		m_bulletList.push_back(bullet);

	//checks whether the player and the zombie's sprites intersect and then changes the colour of the main character to reflect that
	for (unsigned int counter = 0; counter < m_zombieCharacterList.size(); counter++) {
		if (m_zombieCharacterList[counter]->getGlobalBounds().intersects(m_playerCharacter->getGlobalBounds()))
		{
			m_playerCharacter->setColour(sf::Color(255, 0, 0));
		}
		else
		{
			m_playerCharacter->setColour(sf::Color(255, 255, 255));
		}
	}
	/*for (unsigned int counter = 0; counter < m_zombieCharacterList.size(); counter++) {
		if (m_zombieCharacterList[counter]->getGlobalBounds().intersects(m_bulletList[counter]->getGlobalBounds()))
		{
			m_playerCharacter->setColour(sf::Color(255, 0, 0));
		}
		else
		{
			m_playerCharacter->setColour(sf::Color(255, 255, 255));
		}
	}*/
}

void SFML_GameWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	sf::RenderStates renderState;
	renderState.transform = m_camera.getProjTransform() * m_camera.getViewTransform();

	//makes sure that all of the layers greater than 1.0f gets drawn
	for (unsigned int counter = 0; counter < m_gameWorldLayerList.size(); counter++)
	{
		if (m_gameWorldLayerList[counter]->getParallaxFactor() >= 1.0f)
			target.draw(*m_gameWorldLayerList[counter]);
	}

	//makes sure that all of the layers less than 1.0f get drawn
	for (unsigned int counter = 0; counter < m_gameWorldLayerList.size(); counter++)
	{
		if (m_gameWorldLayerList[counter]->getParallaxFactor() < 1.0f);
			target.draw(*m_gameWorldLayerList[counter]);
	}

	//draws all of the zombies into the world
	for (unsigned int counter = 0; counter < m_zombieCharacterList.size(); counter++)
	{
		target.draw(*m_zombieCharacterList[counter], renderState);
	}

	//draws the player character into the world
	target.draw(*m_playerCharacter, renderState);
	/*target.draw(m_SpriteObject, renderState);*/
	/*target.draw(*m_animatedObject, renderState);*/

	//draws all of the bullets into the world
	for (unsigned int counter = 0; counter < m_bulletList.size(); counter++)
	{
		target.draw(*m_bulletList[counter], renderState);
	}
}

void SFML_GameWorld::update(float elapsedTime)
{
	//Calls all the update functions and process events
	processEvents(elapsedTime);
	m_camera.setPosition(m_cameraPosition);
	m_SpriteObject.update(elapsedTime);
	m_animatedObject->update(elapsedTime);
	m_playerCharacter->update(elapsedTime);
	m_camera.setPosition(m_playerCharacter->getWorldPosition());

	//calls all gameworld layers so that the camera can scroll
	for (std::size_t counter = 0; counter < m_gameWorldLayerList.size(); counter++)
	{
		m_gameWorldLayerList[counter]->followCamera(&m_camera);
		m_gameWorldLayerList[counter]->update(elapsedTime);
	}

	//calls all zombies so that they move around
	for (unsigned int counter = 0; counter < m_zombieCharacterList.size(); counter++)
	{
		m_zombieCharacterList[counter]->update(elapsedTime);
	}

	//calls all bullets so that they move
	for (unsigned int counter = 0; counter < m_bulletList.size(); counter++)
	{
		m_bulletList[counter]->update(elapsedTime);
	}
}

bool SFML_GameWorld::layerSortFunction(SFML_GameWorldLayer* a, SFML_GameWorldLayer* b)
{
	return (a->getParallaxFactor() > b->getParallaxFactor());
}