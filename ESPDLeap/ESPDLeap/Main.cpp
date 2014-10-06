#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif // SFML_STATIC


#include <SFML/Graphics.hpp>
#include "PDOrganism.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML works!");

	PDOrganism org(sf::Vector2i(225, 225), 4, 1.9);

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

		window.clear();
		window.draw(org);
		window.display();

		org.update();
	}

	return 0;
}