#pragma once

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


class RRTNode
{
public:
    int xPos, yPos;
    float distToCome;
    RRTNode *parent;
    vector<RRTNode*> children;

    RRTNode(int x, int y, float dist, RRTNode* parentNode);
    ~RRTNode();
};


class RRT
{
public:
    RRTNode* root;

    void addNode(int x, int y, RRTNode* parent);
    void findClosest(RRTNode* node);

};