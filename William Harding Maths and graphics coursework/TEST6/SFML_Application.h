#pragma once
#include <SFML/Graphics.hpp>
#include "SFML_TitleScreen.h"
#include "SFML_GameMenu.h"
#include "SFML_GameWorldLayer.h"
#include "SFML_GameWorld.h"

class SFML_Application : public sf::NonCopyable
{
public:
    SFML_Application(int windowWidth, int windowHeight);
    ~SFML_Application();

    void run();

private:
    void update(sf::Time elapsedTime);
    void render();
    bool m_initialised;

    bool m_previousDownKeyPressed;
    bool m_previousUpKeyPressed;

    sf::RenderWindow m_window;
    std::size_t m_screenWidth;
    std::size_t m_ScreenHeight;
    sf::Event m_event;

    sf::Font m_textFont;
    sf::Text m_messageText;

    sf::Time m_timeCounter;
    sf::Time m_desiredUpdateTime;
    std::size_t m_FPSCounter;

    int m_insideMenu;

    void updateFPS(sf::Time elapsedTime);

    enum AppState
    {
	    TITLESCREEN,
        MAINMENU,
        GAMEPLAYING,
        EXITING,
        OPTIONMENU,
        GAMEMENU,
        CREDITS,
        STORY
    };

    AppState m_appState;

    SFML_TitleScreen m_titleScreen;
    SFML_GameMenu m_mainMenu;
    SFML_TitleScreen m_credits;
    SFML_TitleScreen m_story;
    SFML_GameMenu m_gameMenu;
    SFML_GameWorld m_gameWorld;
};

