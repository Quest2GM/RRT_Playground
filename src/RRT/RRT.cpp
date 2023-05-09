#include <RRT.hpp>

RRTNode::RRTNode(int x, int y, float dist, RRTNode* parentNode)
{
    xPos = x; yPos = y;
    parent = parentNode;
    distToCome = dist;
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

void RRT::addNode(int x, int y, RRTNode* parent)
{   
    float distance = parent->distToCome + sqrt(pow(parent->xPos - x, 2) + pow(parent->yPos - y, 2));
    RRTNode* rrtNode = new RRTNode(x, y, distance, parent);

    if (root == NULL)
    {
        root = rrtNode;
    }
    else 
    {
        parent->children.push_back(rrtNode);
    }
}

void RRT::findClosest(RRTNode* node)
{
    static RRTNode* minNode = root;
    static float minDist = 1000000;

    float currDist = sqrt(pow(node->xPos - minNode->xPos, 2) + pow(node->yPos - minNode->yPos, 2));
    if (currDist < minDist)
    {
        minDist = currDist;
        minNode = node;
    }
    
    if (node != NULL)
    {
        for (int i = 0; i < node->children.size(); i++)
        {
            findClosest(node->children[i]);
        }
    }
}