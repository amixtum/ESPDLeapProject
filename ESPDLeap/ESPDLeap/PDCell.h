#include <SFML/Graphics.hpp>
#include <vector>



class PDCell : public sf::Drawable
{
public:
	static enum Strategy {
		C, D
	};
public:
	PDCell(Strategy s, sf::Vector2f topLeft, float size);

	void playGame(PDCell &other, double b);

	Strategy getStrat();

	sf::Vector2f getMiddle();

	void updateColor();

	void setNextStrat(Strategy nextStrat);

	void updateStrat();

	double getGenSum();

	void resetGenSum();
private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const 
	{
		target.draw(vertices, states);
	}

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

class GameMatrix
{
public:
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