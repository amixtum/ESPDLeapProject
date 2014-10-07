#include "PDCell.h"

#include <cstdlib>
#include <ctime>

/**
The PDOrganism is where all the simulation happens

Holds a "grid" of PDCell objects and updates them according to the rules
of the evolutionary spatial prisoner's dillema
*/
class PDOrganism : public sf::Drawable {
public:
	/**
	dimensions : the dimensions of the grid
	sqrSize : the size of the graphical representation of the cells (squares in this case)
	b : the advantage of the defecting against a cooperator
	random : whether the grid will be initialized with a random distribution of strategies or not
	*/
	PDOrganism(sf::Vector2i dimensions, float sqrSize, double b, bool random);

	/**
	advances the simulation to the next generation
	*/
	void update();

	/**
	Increases the benefit of D against C
	*/
	void operator++() {
		b += 0.1;
	}

	/**
	Decreases the benefit of D against C
	*/
	void operator--() {
		b -= 0.1;
	}

	/**
	Sets the advantage of D against C
	*/
	void setB(double b) {
		this->b = b;
	}
private:
	//gets the index of the cell whose rectangle is intersected by the given vector
	int getIndexFromIntersect(sf::Vector2f vect);

	//gets integer coordinates from (0,0) to (width,height) from the given float coordinates
	sf::Vector2i getVect2iFromPoint(sf::Vector2f vect);

	//gets the rectangle of the cell at the given index in the std::vector
	sf::FloatRect getRectFromIndex(int index);

	//gets the integer coordinates of the cell at the given index
	sf::Vector2i getVectorFromIndex(int index);

	//gets the index of the cell at the given integer coordinates
	int getIndexFromVector(sf::Vector2i vect);

	//gets cells in a moore neighborhood around the cell at the given index
	std::vector<PDCell*> getNeighborCells(int cellIndex);

	//sets the next strategy of the cell at the given index
	void setNextStratAt(int centerIndex);

	//the cell at the given index plays games with all of its neighbors
	void playGamesAt(int cellIndex);

	//every cell in the organism plays games with their neighbors
	void playAllGames();

	//every cell in the organism compares their genSums to their neighbors
	//and sets their next strategies
	void compareAllCells();

	//SFML Drawing code
	//inherited from sf::Drawable
	//draws all the cells
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
		for (auto it = cells.begin(); it != cells.end(); ++it) {
			target.draw(*it, states);
		}
	}
private:
	//advantage of playing D against C
	double b;

	//the cells in the organism
	std::vector<PDCell> cells;

	//the dimensions of the grid
	sf::Vector2i dimensions;

	//the size of the graphical representation of the cells
	float sqrSize;
};