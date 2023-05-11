#pragma once

#include <iostream>
#include <RRT.hpp>
#include <Geometry.hpp>

class RRTStar : public RRT
{
    int searchRadius = 50;

    vector<RRTNode*> findNodesWithinRadius(RRTNode* node, Point p);
    bool runIteration(sf::RenderWindow &window) override;
};