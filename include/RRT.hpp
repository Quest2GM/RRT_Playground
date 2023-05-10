#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;


class RRTNode
{
public:
    int xPos, yPos;
    int nodeId;
    float distToCome;
    RRTNode* parent;
    vector<RRTNode*> children;

    RRTNode(int x, int y);
    ~RRTNode();
};


class RRT
{
public:
    RRTNode* root = NULL;
    int id = 0;

    RRT();
    ~RRT();
    void addNode(int x, int y, sf::RenderWindow& window);
    RRTNode* findClosest(RRTNode* node, int x, int y);
    float findDistance(int x1, int x2, int y1, int y2);
    void drawBranch(int x1, int y1, int x2, int y2, sf::RenderWindow& window);

};