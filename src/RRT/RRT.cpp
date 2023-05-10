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

void RRT::addNode(int x, int y, sf::RenderWindow& window)
{   
    RRTNode* child = new RRTNode(x, y);

    if (root == NULL)
    {
        root = child;
        root->nodeId = id++;
        return;
    }

    RRTNode* parent = findClosest(root, x, y);
    
    child->parent = parent;
    child->nodeId = id++;
    child->distToCome = parent->distToCome + findDistance(x, parent->xPos, y, parent->yPos);
    parent->children.push_back(child);
    drawBranch(parent->xPos, parent->yPos, x, y, window);
}

void RRT::drawBranch(int x1, int y1, int x2, int y2, sf::RenderWindow& window)
{
    sf::Vertex branch[] =
    {
        sf::Vertex(sf::Vector2f(x1, y1)),
        sf::Vertex(sf::Vector2f(x2, y2))
    };
    window.draw(branch, 2, sf::Lines);
}

RRTNode* RRT::findClosest(RRTNode* node, int x, int y)
{ 
    static RRTNode* minNode = root;

    if (node == NULL)
    {
        return minNode;
    }
    
    static float minDist = findDistance(x, minNode->xPos, y, minNode->yPos);

    // Reset static variables if first iteration
    if (node == root)
    {
        minNode = root;
        minDist = findDistance(x, minNode->xPos, y, minNode->yPos);
    }

    float currDist = findDistance(x, node->xPos, y, node->yPos);
    if (currDist < minDist)
    {
        minDist = currDist;
        minNode = node;
    }
    
    for (int i = 0; i < node->children.size(); i++)
    {
        findClosest(node->children[i], x, y);
    }

    return minNode;
}

float RRT::findDistance(int x1, int x2, int y1, int y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}