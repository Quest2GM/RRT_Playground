#pragma once

#include <iostream>
#include <Geometry.hpp>


class RRT
{
public:
    Point start, end;
    std::vector<Rectangle> obstacles;
    RRTNode* root = NULL;
    RRTNode* lastNode = NULL;
    int id = 0;
    int expandDist = 150;
    int goalRadius = 50;
    int iterations = 0;

    RRT(Point start, Point end, std::vector<Rectangle> obstacles);
    RRTNode* addNode(Point p, sf::RenderWindow& window);
    RRTNode* findClosest(RRTNode* node, Point p);
    void traceBack(RRTNode* node, sf::RenderWindow& window);
    bool isCollision(RRTNode* parent, RRTNode* child);
    virtual Point samplePoint();
    void buildEnvironment(sf::RenderWindow &window);
    virtual bool runIteration(sf::RenderWindow &window);
};