#include "GameObject.h"
#include <SFML/Graphics.hpp>
using namespace sf;

GameObject::GameObject(char type, sf::Vector2f size, sf::Vector2f location, Texture *texture) : m_type(type)
{
	m_rec = RectangleShape(size);
	m_rec.setSize(size);
	m_rec.setTexture(texture);
	m_rec.setPosition(location);
	m_rec.setOrigin(m_rec.getSize().x / 2, m_rec.getSize().y / 2);
}
//----------------------------------------------------------------------------
RectangleShape GameObject::getRectangle()
{
	return m_rec;
}
//----------------------------------------------------------------------------
void GameObject::setTexture(Texture *texture)
{
	m_rec.setTexture(texture);
}
//----------------------------------------------------------------------------
void GameObject::Draw(sf::RenderWindow& window)
{
	window.draw(m_rec);
}
//----------------------------------------------------------------------------
char GameObject::getType() const
{
	return m_type;
}
//----------------------------------------------------------------------------
bool GameObject::collide_with(const RectangleShape &other)
{
	if ((*this).getRectangle().getGlobalBounds().intersects(other.getGlobalBounds()))
		return true;
	return false;
}
//----------------------------------------------------------------------------
