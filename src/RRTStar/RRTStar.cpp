#include <RRTStar.hpp>

using namespace std;


vector<RRTNode*> RRTStar::findNodesWithinRadius(RRTNode* node, RRTNode* queryNode)
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
    Line nodeLine(node, queryNode);
    float currDist = nodeLine.getLength();
    if ((currDist < searchRadius) && (node != queryNode))
    {
        nodesInRadius.push_back(node);
    }
    
    for (int i = 0; i < node->children.size(); i++)
    {
        findNodesWithinRadius(node->children[i], queryNode);
    }

    return nodesInRadius;
}

void RRTStar::changeParent(RRTNode* node, RRTNode* newParent, float minDist)
{
    RRTNode* nodeParent = node->parent;
    nodeParent->children.erase(remove(nodeParent->children.begin(),
                                      nodeParent->children.end(), node), nodeParent->children.end());
    node->parent = newParent;
    newParent->children.push_back(node);
    node->distToCome = minDist;
}

void RRTStar::rewireEdges(RRTNode* node, vector<RRTNode*> closeNodes)
{

    if (closeNodes.size() == 0)
    {
        return;
    }

    // Switch parent of node to closestNode
    float minDist = 1000000;
    RRTNode* closestNode;
    for (int i = 0; i < closeNodes.size(); i++)
    {
        Line newEdge(closeNodes[i], node);
        float dist = closeNodes[i]->distToCome + newEdge.getLength();
        if (dist < minDist)
        {
            minDist = dist;
            closestNode = closeNodes[i];
        }
    }
    if (!isCollision(node, closestNode))
    {
        changeParent(node, closestNode, minDist);
    }

    // Improve other points in the radius
    for (int i = 0; i < closeNodes.size(); i++)
    {
        Line newEdge(node, closeNodes[i]);
        float dist = node->distToCome + newEdge.getLength();
        if (closeNodes[i]->distToCome > dist)
        {
            if (!isCollision(closeNodes[i], node))
            {
                changeParent(closeNodes[i], node, dist);
            }
        }
    }
}

void RRTStar::reDrawTree(RRTNode* node, sf::RenderWindow &window)
{
    if (node != NULL)
    {
        for (int i = 0; i < node->children.size(); i++)
        {
            Line branch(node, node->children[i]);
            branch.draw(window, sf::Color::Magenta);
            reDrawTree(node->children[i], window);
        }
    }    
}

bool RRTStar::runIteration(sf::RenderWindow &window)
{
    Point newPoint(rand() % 1200, rand() % 800);
    RRTNode* newNode = addNode(newPoint, window);

    if (newNode == NULL)
    {
        return false;
    }

    vector<RRTNode*> closeNodes = findNodesWithinRadius(root, newNode);
    rewireEdges(newNode, closeNodes);
    
    // Rebuild tree
    window.clear(sf::Color::White);
    reDrawTree(root, window);
    buildEnvironment(window);
    window.display();

    // Draw path if found
    Line newLine(newPoint, end);
    if (newLine.getLength() < goalRadius)
    {
        RRTNode* finalNode = addNode(end, window);
        traceBack(finalNode, window);
        return true;
    }

    return false;
}