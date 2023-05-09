
#include <iostream>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <RRT.hpp>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "##################" << endl;
    cout << "# RRT Playground #" << endl;
    cout << "##################" << endl;

    sf::RenderWindow window(sf::VideoMode(1200, 800), "RRT");
    window.setFramerateLimit(60);
    
    // if (argc == 1 || string(argv[1]) == "RRT")
    // {
    //     cout << "Running RRT..." << endl;
    // }
    // else
    // {
    //     cout << "Running else..." << endl;
    // }

    RRT x(10, 10);

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

