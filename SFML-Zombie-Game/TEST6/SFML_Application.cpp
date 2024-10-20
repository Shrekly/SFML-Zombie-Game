#include "SFML_Application.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

SFML_Application::SFML_Application(int windowWidth, int windowHeight)
	: m_window(sf::VideoMode(windowWidth, windowHeight), "SFML Application", sf::Style::Close)
	, m_initialised(true)
	, m_screenWidth(windowWidth)
	, m_ScreenHeight(windowHeight)
	, m_appState(TITLESCREEN)
	, m_titleScreen("media/textures/title-screen.png", windowWidth, windowHeight)
	, m_mainMenu("media/menuInfo/main-menu.txt", windowWidth, windowHeight)
	, m_gameMenu("media/menuInfo/Game-Menu.txt", windowWidth, windowHeight)
	, m_credits("media/textures/credits.png", windowWidth, windowHeight)
	, m_story("media/textures/story.png", windowWidth, windowHeight)
	, m_desiredUpdateTime(sf::seconds(1.f / 60.f))
	, m_timeCounter(sf::seconds(0))
	, m_FPSCounter(0)
	, m_gameWorld(windowWidth, windowHeight, &m_window)
	, m_previousDownKeyPressed(false)
	, m_previousUpKeyPressed(false)
	, m_insideMenu(0)
{
	m_initialised = m_textFont.loadFromFile("media/Fonts/SegoeMarker.ttf");

	m_messageText.setFont(m_textFont);

	m_mainMenu.setScale(0.85f, 0.85f);
	m_mainMenu.setPosition(m_screenWidth / 2, m_ScreenHeight / 2);

	m_gameMenu.setScale(0.85f, 0.85f);
	m_gameMenu.setPosition(m_screenWidth / 2, m_ScreenHeight / 2);
}

SFML_Application::~SFML_Application()
{

}

void SFML_Application::update(sf::Time elapsedTime)
{
	int selection;
	bool validEventPoll = m_window.pollEvent(m_event);;

	bool currentDownKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	bool currentUpKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	bool currentEscapeKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

	if ((m_event.type == sf::Event::Closed) && validEventPoll)
		m_window.close();

	//checks which app state the game is and then will use code inputted

	switch (m_appState)
	{
	case TITLESCREEN:
		//if any key is pressed it will either take you to the menu or credits
		if (currentDownKeyPressed && !m_previousDownKeyPressed)
			m_appState = MAINMENU;
		else if (currentUpKeyPressed && !m_previousUpKeyPressed)
			m_appState = MAINMENU;
		else if (currentEscapeKeyPressed)
			m_appState = CREDITS;

		m_titleScreen.update(elapsedTime);

		break;

	case MAINMENU:
		selection = m_mainMenu.update(elapsedTime);
		if (selection >= 0)
		{
			if (selection == 0)
				m_appState = STORY;
			else if (selection == 1)
				m_appState = OPTIONMENU;
			else if (selection == 2)
				m_appState = CREDITS;
		}
		

		break;

	case OPTIONMENU:
		//Checks if the player is already inside the game and if they are will instead load the game menu
		if (currentEscapeKeyPressed && m_insideMenu == 0) 
		{
			m_appState = MAINMENU;
		}
		else if (currentEscapeKeyPressed && m_insideMenu >= 1)
		{
			m_appState = GAMEMENU;
		}
		break;
	
	case STORY:
		if (currentDownKeyPressed && !m_previousDownKeyPressed)
			m_appState = GAMEPLAYING;
		else if (currentUpKeyPressed && !m_previousUpKeyPressed)
			m_appState = GAMEPLAYING;
		else if (currentEscapeKeyPressed)
			m_appState = GAMEPLAYING;

		m_story.update(elapsedTime);
		break;

	case GAMEPLAYING:
		if (currentEscapeKeyPressed)
			m_appState = GAMEMENU;

		m_gameWorld.update(elapsedTime.asSeconds());

		break;

	case GAMEMENU:
		m_insideMenu++;
		selection = m_gameMenu.update(elapsedTime);
		if (selection >= 0) 
		{
			if (selection == 0)
				m_appState = GAMEPLAYING;
			else if (selection == 1)
				m_appState = OPTIONMENU;
			else if (selection == 2)
				m_appState = CREDITS;
		}

		break;
	case CREDITS:
		if (currentDownKeyPressed && !m_previousDownKeyPressed)
			m_appState = EXITING;
		else if (currentUpKeyPressed && !m_previousUpKeyPressed)
			m_appState = EXITING;
		else if (currentEscapeKeyPressed)
			m_appState = EXITING;

		m_credits.update(elapsedTime);

		break;

	case EXITING:
		m_window.close();
		break;

	default:
		break;
	}

	m_messageText.setPosition(m_screenWidth / 2, m_ScreenHeight / 2);
	m_messageText.setCharacterSize(100);

	sf::FloatRect textbox = m_messageText.getLocalBounds();
	m_messageText.setOrigin(textbox.width / 2, textbox.height / 2);
}

void SFML_Application::render()
{
	m_window.clear();

	switch (m_appState)
	{
	case TITLESCREEN:
		m_window.draw(m_titleScreen);
		break;
	case MAINMENU:
		m_window.draw(m_mainMenu);
		break;
	case OPTIONMENU:
		m_window.draw(m_messageText);
		break;
	case GAMEMENU:
		m_window.draw(m_gameMenu);
		break;
	case STORY:
		m_window.draw(m_story);
		break;
	case GAMEPLAYING:
		m_window.draw(m_gameWorld);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) 
		{
			m_window.draw(m_messageText);
		}
		break;
	case CREDITS:
		m_window.draw(m_credits);
		break;
	case EXITING:
		break;
	}

	m_window.display();
}

void SFML_Application::run()
{
	if (!m_initialised)
		return;

	sf::Clock clock;

	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();

		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > m_desiredUpdateTime)
		{
			update(m_desiredUpdateTime);

			timeSinceLastUpdate -= m_desiredUpdateTime;
		}

		updateFPS(elapsedTime);
		render();
	}
}

void SFML_Application::updateFPS(sf::Time elapsedTime)
{
	m_timeCounter += elapsedTime;

	m_FPSCounter += 1;

	if (m_timeCounter >= sf::seconds(1.0f))
	{
		m_messageText.setString(
			"Refresh rate = " + std::to_string(m_FPSCounter) +
			" fps \n" +
			"Time between refreshes = " +
			std::to_string(m_timeCounter.asMicroseconds() / m_FPSCounter) +
			" microseconds \n"
		);

		m_timeCounter -= sf::seconds(1.0f);

		m_FPSCounter = 0;
	}
}

