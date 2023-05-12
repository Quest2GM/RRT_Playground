
#include <string.h>
#include <RRT.hpp>
#include <RRTStar.hpp>

using namespace std;


int main()
{
    // Random seed
    srand(0);

    sf::RenderWindow window(sf::VideoMode(1200, 800), "RRT");
    window.setFramerateLimit(100);
    window.clear(sf::Color::White);
    
    // Terminals and Obstacles
    Point start(100, 100);
    Point end(1100, 700);
    Rectangle r1(150, 0, 300, 700);
    Rectangle r2(700, 100, 300, 700);
    vector<Rectangle> obstacles = {r1, r2};

    // RRT Initialization and Loop
    RRT rrt(start, end, obstacles);
    rrt.buildEnvironment(window);
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

