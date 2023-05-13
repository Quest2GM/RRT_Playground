
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

    Rectangle r1(550, 200, 100, 200);
    Rectangle r2(550, 410, 100, 200);
    vector<Rectangle> obstacles = {r1, r2};

    // RRT Initialization and Loop
    InformedRRTStar rrt(start, end, obstacles);
    rrt.buildEnvironment(window);
    rrt.addNode(start, window);

    sf::Font font;
    font.loadFromFile("/home/sinarasi/Documents/RRT_Playground/src/Memogram.otf");

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
        if (found || rrt.reachedDest)
        {
            sf::Text text2;
            text2.setFont(font);
            text2.setString("Distance to Come: " + to_string(int(rrt.lastNode->distToCome)));
            text2.setPosition(950, 740);
            text2.setCharacterSize(20);
            text2.setFillColor(sf::Color::Black);
            window.draw(text2);
        }

        sf::Text text1;
        text1.setFont(font);
        text1.setString("Iterations: " + to_string(rrt.iterations));
        text1.setPosition(950, 700);
        text1.setCharacterSize(20);
        text1.setFillColor(sf::Color::Black);
        window.draw(text1);

        window.display();
    }
}

