#include "PDCell.h"

PDCell::PDCell(Strategy s, sf::Vector2f topLeft, float size) {
	genSum = 0;

	lastStrat = s;
	strat = s;
	switch (s)
	{
	case PDCell::Strategy::C:
		color = sf::Color::Blue;
		break;
	case PDCell::Strategy::D:
		color = sf::Color::Red;
		break;
	default:
		color = sf::Color::White;
	}

	rect.left = topLeft.x;
	rect.top = topLeft.y;
	rect.width = size;
	rect.height = size;

	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(4);

	float x = rect.left;
	float y = rect.top;

	vertices[0].position = sf::Vector2f(x, y);
	vertices[1].position = sf::Vector2f(x + size, y);
	vertices[2].position = sf::Vector2f(x + size, y + size);
	vertices[3].position = sf::Vector2f(x, y + size);

	for (int i = 0; i < vertices.getVertexCount(); ++i) {
		vertices[i].color = color;
	}
}

void PDCell::setNextStrat(PDCell::Strategy nextStrat) {
	this->nextStrat = nextStrat;
}

void PDCell::updateStrat() {
	this->lastStrat = this->strat;
	this->strat = nextStrat;
}

void PDCell::updateColor() {
	switch (this->strat) {
	case PDCell::Strategy::C:
		switch (this->lastStrat) {
		case PDCell::Strategy::C:
			this->color = sf::Color::Blue;
			break;
		case PDCell::Strategy::D:
			this->color = sf::Color::Green;
			break;
		}
		break;
	case PDCell::Strategy::D:
		switch (this->lastStrat) {
		case PDCell::Strategy::C:
			this->color = sf::Color::Yellow;
			break;
		case PDCell::Strategy::D:
			this->color = sf::Color::Red;
			break;
		}
		break;
	}

	changeColor(color);
}

void PDCell::changeColor(sf::Color c) {
	for (int i = 0; i < vertices.getVertexCount(); ++i) {
		vertices[i].color = c;
	}
}

PDCell::Strategy PDCell::getStrat() {
	return this->strat;
}

void PDCell::playGame(PDCell &other, double b) {
	genSum += GameMatrix::getPayoff(this->strat, other.getStrat(), b);
}

sf::Vector2f PDCell::getMiddle() {
	return sf::Vector2f(rect.left + (rect.width / 2), rect.top + (rect.height / 2));
}

double PDCell::getGenSum() {
	return genSum;
}

void PDCell::resetGenSum() {
	genSum = 0;
}