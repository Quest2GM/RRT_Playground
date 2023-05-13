#include <RRTStar.hpp>

using namespace std;


vector<RRTNode*> RRTStar::findNodesWithinRadius(RRTNode* node, RRTNode* queryNode, int radius)
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
    if ((currDist < radius) && (node != queryNode))
    {
        nodesInRadius.push_back(node);
    }
    
    for (int i = 0; i < node->children.size(); i++)
    {
        findNodesWithinRadius(node->children[i], queryNode, radius);
    }

    return nodesInRadius;
}

void RRTStar::rewireEdges(RRTNode* node, vector<RRTNode*> closeNodes)
{

    if (closeNodes.size() == 0)
    {
        return;
    }

    // Determine best rewiring for current node
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

    // Improve rewiring for other points in the radius
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

void RRTStar::changeParent(RRTNode* node, RRTNode* newParent, float minDist)
{
    RRTNode* nodeParent = node->parent;

    // Remove child from old parent
    vector<RRTNode*>::iterator itr = find(nodeParent->children.begin(), nodeParent->children.end(), node);
    nodeParent->children.erase(nodeParent->children.begin() + distance(nodeParent->children.begin(), itr));

    // Add new parent
    node->parent = newParent;
    newParent->children.push_back(node);
    node->distToCome = minDist;
}

bool RRTStar::inGoalRegion(RRTNode* node)
{
    Line l(node, end);
    if (l.getLength() < goalRadius)
    {
        return true;
    }
    return false;
}

bool RRTStar::runIteration(sf::RenderWindow &window)
{
    Point newPoint = samplePoint();
    RRTNode* newNode = addNode(newPoint, window);

    if (newNode == NULL)
    {
        return false;
    }

    iterations++;
    if (iterations % 100 == 0)
    {
        cout << iterations << endl;
    }

    vector<RRTNode*> closeNodes = findNodesWithinRadius(root, newNode, searchRadius);
    rewireEdges(newNode, closeNodes);
   
    // Rebuild tree
    window.clear(sf::Color::White);
    reDrawTree(root, window);
    buildEnvironment(window);

    // Draw path if found
    if (!reachedDest)
    {
        if (inGoalRegion(newNode))
        {
            reachedDest = true;
            lastNode = addNode(end, window);
            traceBack(lastNode, window);
        }
    }
    else
    {
        traceBack(lastNode, window);
    }

    // Exit if maxIterations reached
    if (iterations >= maxIterations)
    {
        cout << "Max Iterations Reached!" << endl;
        if (lastNode == NULL)
        {
            cout << "Could not find goal!" << endl;
        }
        else
        {
            cout << "Distance to Come: " << lastNode->distToCome << endl;
        }
        return true;
    }
    
    return false;
}