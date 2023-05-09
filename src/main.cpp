
#include <iostream>
#include <SFML/Graphics.hpp>
#include <RRT.hpp>

using namespace std;

int main()
{
    cout << "RRT Playground" << endl;

    RRT rrt;
    rrt.display();

    sf::RenderWindow window(sf::VideoMode(1200, 800), "RRT");
    window.setFramerateLimit(60);

    sf::CircleShape shape(50);
    shape.setFillColor(sf::Color(150, 50, 250));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
            	window.close();
            	return 0;
            }
        }

		window.clear();
        
        window.display();
    }
}

