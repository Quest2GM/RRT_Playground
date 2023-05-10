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
    float distToCome;
    RRTNode *parent;
    vector<RRTNode*> children;

    RRTNode(int x, int y);
    ~RRTNode();
};


class RRT
{
public:
    RRTNode* root;

    RRT();
    ~RRT();
    void addNode(int x, int y);
    RRTNode* findClosest(RRTNode* node, int x, int y);
    float findDistance(int x1, int x2, int y1, int y2);

};