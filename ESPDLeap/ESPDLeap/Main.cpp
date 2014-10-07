#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif // SFML_STATIC


#include <SFML/Graphics.hpp>
#include "Leap.h"
#include "PDOrganism.h"

int main()
{
	Leap::Controller controller;

	float velocityThreshold = 700.f;

	while (!controller.isConnected()){}

	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

	std::srand(std::time(nullptr));

	PDOrganism org(sf::Vector2i(199, 199), 4, 1.9, true);

	float sleepTime = 0.05f;
	float timeSinceSleep = 0;
	sf::Clock timer;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
				org++;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
				org--;
			}
		}

		for (Leap::Hand hand : controller.frame().hands()) {
			if (hand.isRight()) {
				if (hand.palmVelocity().y > velocityThreshold) {
					org++;
				}
				if (-hand.palmVelocity().y > velocityThreshold) {
					org--;
				}
			}
		}

		window.clear();
		window.draw(org);
		window.display();

		org.update();
	}

	return 0;
}