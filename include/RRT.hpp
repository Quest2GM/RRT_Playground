#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <eigen3/Eigen/Dense>

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
    int startX, startY, endX, endY;
    vector<vector<int>> obsLocs;

    RRT(int startX, int startY, int endX, int endY);
    ~RRT();
    RRTNode* addNode(int x, int y, sf::RenderWindow& window);
    RRTNode* findClosest(RRTNode* node, int x, int y);
    float findDistance(int x1, int x2, int y1, int y2);
    void drawBranch(int x1, int y1, int x2, int y2, sf::RenderWindow& window, sf::Color colour);
    void drawObstacles(sf::RenderWindow &window);
    void dispStartEnd(sf::RenderWindow &window);
    bool runIteration(sf::RenderWindow &window);
    void traceBack(RRTNode* node, sf::RenderWindow& window);
    bool isCollision(RRTNode* parent, RRTNode* child);
    bool checkIntersection(int x1, int x2, int y1, int y2, int a1, int a2, int b1, int b2);
};