#include <SFML/Graphics.hpp>
#include <string>
#include "Menu.h"
using namespace sf;

//----------------------------------------------------------------------------
Menu::Menu(RectangleShape background)
{
    m_background = background;
    m_menu = RectangleShape(Vector2f(580, 680));
    m_howToPlay = RectangleShape(Vector2f(580, 680));
    m_howToPlayButton = RectangleShape(Vector2f(480, 120));
    m_exit = RectangleShape(Vector2f(480, 120));
    m_start = RectangleShape(Vector2f(480, 120));
    m_exit.setPosition(Vector2f(420, 570));
    m_howToPlayButton.setPosition(Vector2f(420, 370));
    m_start.setPosition(Vector2f(420, 200));

    m_startTextures.push_back(new Texture());
    m_startTextures[0]->loadFromFile("start.png");
    m_startTextures.push_back(new Texture());
    m_startTextures[1]->loadFromFile("start2.png");
    m_start.setTexture(m_startTextures[0]);

    m_howtoTextures.push_back(new Texture());
    m_howtoTextures[0]->loadFromFile("howtobutton.png");
    m_howtoTextures.push_back(new Texture());
    m_howtoTextures[1]->loadFromFile("howtobutton2.png");
    m_howToPlayButton.setTexture(m_howtoTextures[0]);

    m_exitTextures.push_back(new Texture());
    m_exitTextures[0]->loadFromFile("exit.png");
    m_exitTextures.push_back(new Texture());
    m_exitTextures[1]->loadFromFile("exit2.png");
    m_exit.setTexture(m_exitTextures[0]);

    auto texture = new Texture();
    texture->loadFromFile("menu.png");
    m_menu.setTexture(texture);
    texture = new Texture();
    texture->loadFromFile("howtoplay.png");
    m_howToPlay.setTexture(texture);
    m_menu.setPosition(380, 120);
    m_howToPlay.setPosition(m_menu.getPosition());

    m_back = RectangleShape(Vector2f(120, 50));
    texture = new Texture();
    texture->loadFromFile("back.png");
    m_back.setTexture(texture);
    m_back.setPosition(Vector2f(600, 800));
}
//----------------------------------------------------------------------------
void Menu::showMenu(RenderWindow& window)
{
    while (window.isOpen())
    {
        window.clear();
        window.draw(m_background);
        if (m_showHowto)
        {
            window.draw(m_howToPlay);
            window.draw(m_back);
        }
        else
        {
            window.draw(m_menu);
            window.draw(m_howToPlayButton);
            window.draw(m_start);
            window.draw(m_exit);
        }
        window.display();
        if (auto event = sf::Event{}; window.waitEvent(event)) {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonReleased:
                {
                    auto location = window.mapPixelToCoords(
                            { event.mouseButton.x, event.mouseButton.y });

                    switch (event.mouseButton.button)
                    {
                        case sf::Mouse::Button::Left:
                            handleClick(location, window);
                            if (m_toStart) return;
                            break;
                        default: break;
                    }

                    break;

                }
                case sf::Event::MouseMoved:
                {
                    auto location = window.mapPixelToCoords(
                            { event.mouseMove.x, event.mouseMove.y });
                    handleHover(location);
                    break;
                }
                default: break;
            }
        }
    }
}
//----------------------------------------------------------------------------
void Menu::handleClick(const sf::Vector2f& location, RenderWindow& window)
{
    if (m_start.getGlobalBounds().contains(location))
    {
        m_toStart = true;
        return;
    }
    if (m_exit.getGlobalBounds().contains(location))
        window.close();

    if (m_howToPlayButton.getGlobalBounds().contains(location))
        m_showHowto = true;
    if (m_back.getGlobalBounds().contains(location))
        m_showHowto = false;
}
//----------------------------------------------------------------------------
void Menu::handleHover(const sf::Vector2f& location)
{
    if (m_start.getGlobalBounds().contains(location))
    {
        m_start.setTexture(m_startTextures[1]);
    }
    else m_start.setTexture(m_startTextures[0]);

    if (m_exit.getGlobalBounds().contains(location))
        m_exit.setTexture(m_exitTextures[1]);
    else m_exit.setTexture(m_exitTextures[0]);

    if (m_howToPlayButton.getGlobalBounds().contains(location))
        m_howToPlayButton.setTexture(m_howtoTextures[1]);
    else m_howToPlayButton.setTexture(m_howtoTextures[0]);
}
//----------------------------------------------------------------------------