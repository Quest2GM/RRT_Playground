
#include <string.h>
#include <RRT.hpp>
#include <RRTStar.hpp>
#include <InformedRRTStar.hpp>

using namespace std;


int main()
{
    // Random seed
    srand(0);

    sf::RenderWindow window(sf::VideoMode(1200, 800), "RRT Playground");
    window.setFramerateLimit(100);
    window.clear(sf::Color::White);
    
    // Terminals and Obstacles
    Point start(500, 400);
    Point end(700, 400);
    // Point end(100, 350);
    Rectangle r1(550, 200, 100, 200);
    Rectangle r2(550, 403, 100, 200);
    vector<Rectangle> obstacles = {r1, r2};

    // RRT Initialization and Loop
    InformedRRTStar rrt(start, end, obstacles);
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

