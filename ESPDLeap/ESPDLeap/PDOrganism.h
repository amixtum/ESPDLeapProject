#include "PDCell.h"

#define _USE_MATH_DEFINES
#include <cmath>

class PDOrganism : public sf::Drawable {
public:
	PDOrganism(sf::Vector2i dimensions, float sqrSize, double b);

	void update();

	void operator++() {
		b += 0.1;
	}
	void operator--() {
		b -= 0.1;
	}
	void setB(double b) {
		this->b = b;
	}
private:
	int getIndexFromIntersect(sf::Vector2f vect);

	sf::Vector2i getVect2iFromPoint(sf::Vector2f vect);

	sf::FloatRect getRectFromIndex(int index);

	sf::Vector2i getVectorFromIndex(int index);

	int getIndexFromVector(sf::Vector2i vect);

	std::vector<PDCell*> getNeighborCells(int cellIndex);

	void getHeighestSumIndexAround(int centerIndex);

	void playGamesAt(int cellIndex);

	void playAllGames();

	void compareAllCells();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
		for (auto it = cells.begin(); it != cells.end(); ++it) {
			target.draw(*it, states);
		}
	}
private:
	double b;
	std::vector<PDCell> cells;
	sf::Vector2i dimensions;
	float sqrSize;
	const double pi = 3.14159265358979323846;
};