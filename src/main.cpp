
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
    cout << "RRT Playground" << endl;

    sf::RenderWindow window(sf::VideoMode(1200, 800), "RRT");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
            	window.close();
            	return 0; exit(0);
            }
        }
		window.clear();
        window.display();
    }
}

