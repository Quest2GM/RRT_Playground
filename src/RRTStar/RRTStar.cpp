#include <RRTStar.hpp>

using namespace std;

vector<RRTNode*> RRTStar::findNodesWithinRadius(RRTNode* node, Point p)
{ 
    static vector<RRTNode*> nodesInRadius;

    if (node == NULL)
    {
        return nodesInRadius;
    }

    // Reset static variables if first iteration
    if (node == root)
    {
        nodesInRadius.clear();
    }

    // Add to vector if node is within search radius
    Line nodeLine(node, p);
    float currDist = nodeLine.getLength();
    if (currDist < searchRadius)
    {
        nodesInRadius.push_back(node);
    }
    
    for (int i = 0; i < node->children.size(); i++)
    {
        findNodesWithinRadius(node->children[i], p);
    }

    return nodesInRadius;
}

bool RRTStar::runIteration(sf::RenderWindow &window)
{
    Point newPoint(rand() % 1200, rand() % 800);
    RRTNode* newNode = addNode(newPoint, window);

    if (newNode == NULL)
    {
        return false;
    }

    return false;
}