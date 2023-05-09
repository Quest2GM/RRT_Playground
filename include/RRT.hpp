#pragma once

#include <iostream>
#include <vector>

using namespace std;

class RRT
{
public:
    RRT *parent;
    vector<RRT> children;
    int xPos, yPos;

    RRT(int x, int y);
    ~RRT();
    void display();
};