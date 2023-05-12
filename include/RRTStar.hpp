#pragma once

#include <iostream>
#include <RRT.hpp>
#include <Geometry.hpp>

using namespace std;

class RRTStar : public RRT
{
public:
    int searchRadius = 50;
    bool reachedDest = false;
    RRTNode* lastNode;

    RRTStar(Point start, Point end, std::vector<Rectangle> obstacles) : RRT(start, end, obstacles) {};
    void reDrawTree(RRTNode* node, sf::RenderWindow &window);
    vector<RRTNode*> findNodesWithinRadius(RRTNode* node, RRTNode* queryNode);
    void changeParent(RRTNode* node, RRTNode* newParent, float minDist);
    void rewireEdges(RRTNode* node, vector<RRTNode*> closeNodes);
    bool runIteration(sf::RenderWindow &window) override;
};