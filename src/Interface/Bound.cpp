#include "Bound.h"

Bound::Bound()
{
	top = 0;
	left = 0;
	width = 50;
	height = 50;
	setOpacity(255);
}

Bound::Bound(const sf::Vector2f& newSize)
{
	top = 0;
	left = 0;
	width = newSize.x;
	height = newSize.y;
	setOpacity(255);
}

Bound::~Bound()
{

}

void Bound::setSize(const sf::Vector2f& newSize)
{
	width = newSize.x;
	height = newSize.y;
	
}

void Bound::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	int opacity = getOpacity();
	sf::VertexArray vertex(sf::PrimitiveType::Quads, 4);
	vertex[0].position = sf::Vector2f(left, top);
	vertex[0].color = sf::Color(0, 255, 255, opacity);
	vertex[1].position = sf::Vector2f(width + left, top);
	vertex[1].color = sf::Color(0, 255, 255, opacity);
	vertex[2].position = sf::Vector2f(width + left, top + height);
	vertex[2].color = sf::Color(0, 255, 255, opacity);
	vertex[3].position = sf::Vector2f(left, top + height);
	vertex[3].color = sf::Color(0, 255, 255, opacity);
	target.draw(vertex, states);
}