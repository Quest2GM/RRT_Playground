
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
    
    RRT rrt(10,10,1150,750);
    rrt.dispStartEnd(window);

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
        

        window.display();
    }
}

