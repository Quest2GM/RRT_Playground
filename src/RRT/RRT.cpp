#include <RRT.hpp>

RRT::RRT(int x, int y)
{
    parent = NULL;
    int xPos = x;
    int yPos = y;
}

RRT::~RRT() 
{
    cout << "RRT Destructed" << endl;
}

void RRT::display()
{
    cout << "Hi from RRT" << endl;
}