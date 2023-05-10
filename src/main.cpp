
#include <string.h>
#include <RRT.hpp>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "##################" << endl;
    cout << "# RRT Playground #" << endl;
    cout << "##################" << endl;

    srand(1);

    int windowX = 1200, windowY = 800;

    sf::RenderWindow window(sf::VideoMode(windowX, windowY), "RRT");
    window.setFramerateLimit(60);
    
    RRT rrt;

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

		// window.clear();
        int rX = rand() % windowX, rY = rand() % windowY;
        rrt.addNode(rX, rY, window);

        window.display();
    }
}

