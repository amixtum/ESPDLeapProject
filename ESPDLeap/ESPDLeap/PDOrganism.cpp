#include "PDOrganism.h"
#include <iostream>

PDOrganism::PDOrganism(sf::Vector2i dimensions, float sqrSize, double b, bool random) : dimensions(dimensions) {
	this->sqrSize = sqrSize;
	this->b = b;

	if (random) {
		srand(time(NULL));

		for (int i = 0; i < dimensions.y; ++i) {
			for (int k = 0; k < dimensions.x; ++k) {
				cells.push_back(PDCell((std::rand()%1000 < 750) ? PDCell::Strategy::C : PDCell::Strategy::D, sf::Vector2f(k * sqrSize, i * sqrSize), sqrSize));
			}
		}
	}
	else {
		for (int i = 0; i < dimensions.y; ++i) {
			for (int k = 0; k < dimensions.x; ++k) {
				if (i == dimensions.x / 2 && k == dimensions.y / 2) {
					cells.push_back(PDCell(PDCell::Strategy::D, sf::Vector2f(k * sqrSize, i * sqrSize), sqrSize));
				}
				else {
					cells.push_back(PDCell(PDCell::Strategy::C, sf::Vector2f(k * sqrSize, i * sqrSize), sqrSize));
				}
			}
		}
	}
}

void PDOrganism::update() {
	playAllGames();
	compareAllCells();
}

void PDOrganism::setNextStratAt(int centerIndex) {
	PDCell *self = &cells[centerIndex];

	std::vector<PDCell*> surroundingCells = getNeighborCells(centerIndex);

	double max = surroundingCells[0]->getGenSum();
	int maxIndex = 0;

	for (unsigned int i = 0; i < surroundingCells.size(); ++i) {
		if (surroundingCells[i]->getGenSum() > max) {
			max = surroundingCells[i]->getGenSum();
			maxIndex = i;
		}
	}

	self->setNextStrat(surroundingCells[maxIndex]->getStrat());
}

void PDOrganism::compareAllCells() {
	for (unsigned int i = 0; i < cells.size(); ++i) {
		setNextStratAt(i);
	}

	for (auto it = cells.begin(); it != cells.end(); ++it) {
		it->updateStrat();
		it->updateColor();
		it->resetGenSum();
	}
}

void PDOrganism::playGamesAt(int cellIndex) {
	PDCell *self = &cells[cellIndex];

	std::vector<PDCell*> neighborVect = getNeighborCells(cellIndex);

	for (auto it = neighborVect.begin(); it != neighborVect.end(); ++it) {
		self->playGame(*(*it), this->b);
	}
}

void PDOrganism::playAllGames() {
	for (unsigned int i = 0; i < cells.size(); ++i) {
		playGamesAt(i);
	}
}

std::vector<PDCell*> PDOrganism::getNeighborCells(int cellIndex) {
	PDCell *self = &cells[cellIndex];

	sf::Vector2f middle = self->getMiddle();

	sf::Vector2i intVect = getVect2iFromPoint(middle);

	std::vector<PDCell*> returnVect;

	returnVect.reserve(9);

	for (int i = intVect.x - 1; i <= intVect.x + 1; ++i) {
		for (int k = intVect.y - 1; k <= intVect.y + 1; ++k) {
			if (i >= 0 && i < dimensions.x && k >= 0 && k < dimensions.y) {
				int intersectIndex = getIndexFromVector(sf::Vector2i(k,i));
				returnVect.push_back(&cells[intersectIndex]);
			}
		}
	}

	return returnVect;
}

int PDOrganism::getIndexFromIntersect(sf::Vector2f vect) {
	return getIndexFromVector(getVect2iFromPoint(vect));
}

sf::Vector2i PDOrganism::getVect2iFromPoint(sf::Vector2f vect) {
	int left = (int)vect.x / sqrSize;
	int top = (int)vect.y / sqrSize;

	return sf::Vector2i(left, top);
}

sf::FloatRect PDOrganism::getRectFromIndex(int index) {
	return sf::FloatRect(getVectorFromIndex(index).x * sqrSize, getVectorFromIndex(index).y * sqrSize, sqrSize, sqrSize);
}

sf::Vector2i PDOrganism::getVectorFromIndex(int index) {
	int col = index / dimensions.x;
	int row = index - (col * dimensions.x);

	return sf::Vector2i(col, row);
}

int PDOrganism::getIndexFromVector(sf::Vector2i vect) {
	return (vect.x * dimensions.x) + vect.y;
}