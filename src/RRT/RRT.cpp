#include <RRT.hpp>

RRTNode::RRTNode(int x, int y)
{
    xPos = x; yPos = y;
    parent = NULL;
    distToCome = 0;
}

RRTNode::~RRTNode() {};

RRT::RRT()
{
    root = NULL;
}

RRT::~RRT() 
{
    cout << "RRT Destructed" << endl;
}

void RRT::addNode(int x, int y)
{   
    RRTNode* parent = findClosest(root, x, y);
    RRTNode* child = new RRTNode(x, y);
    
    if (parent == NULL)
    {
        root = child;
        return;
    }
    
    child->distToCome = parent->distToCome + findDistance(x, parent->xPos, y, parent->yPos);
    parent->children.push_back(child);
}

RRTNode* RRT::findClosest(RRTNode* node, int x, int y)
{
    static RRTNode* minNode = node;
    static float minDist = findDistance(x, minNode->xPos, y, minNode->yPos);

    if (node == NULL)
    {
        return minNode;
    }

    float currDist = findDistance(x, minNode->xPos, y, minNode->yPos);
    if (currDist < minDist)
    {
        minDist = currDist;
        minNode = node;
    }
    
    if (node != NULL)
    {
        for (int i = 0; i < node->children.size(); i++)
        {
            RRTNode* n = findClosest(node->children[i], x, y);
        }
    }
    return minNode;
}

float RRT::findDistance(int x1, int x2, int y1, int y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}