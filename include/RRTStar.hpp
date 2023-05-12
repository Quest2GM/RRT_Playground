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
    int maxIterations = 3000;

    RRTStar(Point start, Point end, std::vector<Rectangle> obstacles) : RRT(start, end, obstacles) {};
    vector<RRTNode*> findNodesWithinRadius(RRTNode* node, RRTNode* queryNode, int radius);
    void rewireEdges(RRTNode* node, vector<RRTNode*> closeNodes);
    void changeParent(RRTNode* node, RRTNode* newParent, float minDist);
    void reDrawTree(RRTNode* node, sf::RenderWindow &window);
    bool inGoalRegion(RRTNode* node);
    bool runIteration(sf::RenderWindow &window) override;
};