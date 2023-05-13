
#include <string.h>
#include <RRT.hpp>
#include <RRTStar.hpp>
#include <AnytimeRRT.hpp>
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

    Rectangle r1(550, 200, 100, 200);
    Rectangle r2(550, 405, 100, 200);
    Rectangle r3(330, 100, 200, 100);
    Rectangle r4(330, 600, 200, 100);
    Rectangle r5(670, 100, 200, 100);
    Rectangle r6(670, 600, 200, 100);
    vector<Rectangle> obstacles = {r1, r2, r3, r4, r5, r6};

    // RRT Initialization and Loop
    AnytimeRRT planner(start, end, obstacles);
    planner.buildEnvironment(window);
    planner.addNode(start, window);

    bool found = false;
    float dist = 10000;
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

        if (!found && dist > 202)
        {
            found = planner.runIteration(window);    
        }
        if (found || planner.reachedDest)
        {
            dist = planner.lastNode->distToCome;
            Text text1("Distance: " + to_string(int(planner.lastNode->distToCome)), 10, 40);
            text1.draw(window);
        }

        Text text2("Iterations: " + to_string(planner.iterations), 10, 10);
        text2.draw(window);

        window.display();
    }
}

