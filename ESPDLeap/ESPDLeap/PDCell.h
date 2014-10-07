#include <SFML/Graphics.hpp>
#include <vector>


/**
The basis for all of this code. These are the "players" in the evolutionary spatial prisoner's dilemma.
*/
class PDCell : public sf::Drawable
{
public:
	//enum to easily identify strategies.
	//avoids lots of 1s and 0s all over the place
	static enum Strategy {
		C, D
	};
public:
	/**
	Sets the initial strategy of the cell. It's top-left corner and the size
	of its sides.
	*/
	PDCell(Strategy s, sf::Vector2f topLeft, float size);

	/**
	Plays the prisoner's dilemma against another cell
	The 'b' param is the advantage of defecting while another player cooperates
	*/
	void playGame(PDCell &other, double b);

	/**
	Gets the strategy of this cell
	*/
	Strategy getStrat();

	/**
	Gets the middle of this cell's rectangle
	*/
	sf::Vector2f getMiddle();

	/**
	updates the color of the cell
	should only be called when the strategy is updated
	*/
	void updateColor();

	/**
	Sets the next strategy to be switched
	at the end of the generation
	*/
	void setNextStrat(Strategy nextStrat);

	/**
	updates the strategy of the cell
	should only be called after all comparisons are made
	*/
	void updateStrat();

	/**
	Gets the sum of the games played during the generation
	*/
	double getGenSum();

	/**
	Sets genSum back to 0
	Should be called at the end of a generation
	*/
	void resetGenSum();
private:
	//SFML drawing code
	//inherited from sf::Drawable
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw(vertices, states);
	}

	//changes the color of the vertices
	//called in PDCell::updateColor()
	void changeColor(sf::Color c);
private:
	//data properties
	Strategy lastStrat;
	Strategy strat;
	Strategy nextStrat;
	double genSum;

	//graphics properties
	sf::FloatRect rect;
	sf::VertexArray vertices;
	sf::Color color;
};

/**
Results of the prisoner's dillema are defined here

Much can be done with this to make things more interesting
*/
class GameMatrix
{
public:
	/**
	Gets the payoff for the first player given two strategies
	'b' param is the value given to a player who defects while the other cooperates
	*/
	static double getPayoff(PDCell::Strategy s1, PDCell::Strategy s2, double b) {
		switch (s1) {
		case PDCell::C:
			switch (s2) {
			case PDCell::C:
				return 1;
				break;
			case PDCell::D:
				return 0;
				break;
			}
			break;
		case PDCell::D:
			switch (s2) {
			case PDCell::C:
				return b;
				break;
			case PDCell::D:
				return 0;
				break;
			}
			break;
		}
		return -1;
	}
};