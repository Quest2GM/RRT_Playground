#pragma once

#include <iostream>
#include <Geometry.hpp>


class RRT
{
private:
    std::vector<Rectangle> obstacles;
    int id = 0;
    int expandDist = 100;

public:
    Point start, end;
    RRTNode* root = NULL;
    RRTNode* lastNode = NULL;
    int iterations = 0;
    int goalRadius = 50;
    bool reachedDest = false;

    RRT(Point start, Point end, std::vector<Rectangle> obstacles);
    ~RRT();
    void deleteNodes(RRTNode* node);
    RRTNode* addNode(Point p, sf::RenderWindow& window);
    RRTNode* findClosest(RRTNode* node, Point p);
    void traceBack(RRTNode* node, sf::RenderWindow& window);
    bool isCollision(RRTNode* parent, RRTNode* child);
    virtual Point samplePoint();
    void reDrawTree(RRTNode* node, sf::RenderWindow &window);
    void buildEnvironment(sf::RenderWindow &window);
    virtual bool runIteration(sf::RenderWindow &window);
};