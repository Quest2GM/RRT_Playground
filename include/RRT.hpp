#pragma once

#include <iostream>
#include <Geometry.hpp>


class RRT
{
public:
    RRTNode* root = NULL;
    int id = 0;
    Point start;
    Point end;
    std::vector<Rectangle> obstacles;
    int expandDist = 75;
    int goalRadius = 10;

    RRT(Point start, Point end, std::vector<Rectangle> obstacles);
    RRTNode* addNode(Point p, sf::RenderWindow& window);
    RRTNode* findClosest(RRTNode* node, Point p);
    void traceBack(RRTNode* node, sf::RenderWindow& window);
    bool isCollision(RRTNode* parent, RRTNode* child);
    void buildEnvironment(sf::RenderWindow &window);
    virtual bool runIteration(sf::RenderWindow &window);
};