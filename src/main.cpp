
#include <string.h>
#include <RRT.hpp>

using namespace std;


int main(int argc, char *argv[])
{
    // Random seed
    srand(0);

    // Initialize Display Window
    sf::RenderWindow window(sf::VideoMode(1200, 800), "RRT");
    window.setFramerateLimit(100);
    window.clear(sf::Color::White);
    
    // Display start and end points
    Point start(100, 100);
    start.draw(5, window, sf::Color::Green);
    Point end(1100, 700);
    end.draw(5, window, sf::Color::Red);

    // Create obstacles
    Rectangle r1(150, 0, 300, 700);
    r1.draw(window);
    Rectangle r2(700, 100, 300, 700);
    r2.draw(window);
    vector<Rectangle> obstacles = {r1, r2};

    // RRT Initialization and Loop
    RRT rrt(start, end, obstacles);
    rrt.addNode(start, window);

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

