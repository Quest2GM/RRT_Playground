
#include <string.h>
#include <RRT.hpp>

using namespace std;


int main(int argc, char *argv[])
{
    cout << "##################" << endl;
    cout << "# RRT Playground #" << endl;
    cout << "##################" << endl;

    srand(0);

    sf::RenderWindow window(sf::VideoMode(1200, 800), "RRT");
    window.setFramerateLimit(100);
    window.clear(sf::Color::White);
    
    RRT rrt(100,100,1100,700);
    rrt.dispStartEnd(window);
    rrt.drawObstacles(window);

    bool found = false;

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

        if (!found)
        {
            found = rrt.runIteration(window);    
        }

        window.display();
    }
}

