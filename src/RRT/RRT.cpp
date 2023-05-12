#include <RRT.hpp>

using namespace std;

RRT::RRT(Point start, Point end, vector<Rectangle> obstacles)
{
    this->start = start;
    this->end = end;
    this->obstacles = obstacles;
    root = NULL;
}

RRTNode* RRT::addNode(Point childPoint, sf::RenderWindow& window)
{   
    RRTNode* child = new RRTNode(childPoint.x, childPoint.y);

    if (root == NULL)
    {
        root = child;
        root->nodeId = id++;
        return root;
    }

    RRTNode* parent = findClosest(root, childPoint);

    Line parToChild(parent, child);
    float pcDist = parToChild.getLength();

    // If pcDist > expandDist, avoid collision checking. Thus, don't merge if statements.
    if (pcDist > expandDist)
    {
        delete child;
        return NULL;
    }
    else if (isCollision(parent, child))
    {
        delete child;
        return NULL;
    }
    
    // Add child node
    child->parent = parent;
    child->nodeId = id++;
    child->distToCome = parent->distToCome + pcDist;
    parent->children.push_back(child);
    parent->optEdge.push_back(false);
    parToChild.draw(window, sf::Color::Magenta);

    return child;
}

RRTNode* RRT::findClosest(RRTNode* node, Point p)
{ 
    static RRTNode* minNode = root;

    if (node == NULL)
    {
        return minNode;
    }
    
    Line minLine(minNode, p);
    static float minDist = minLine.getLength();

    // Reset static variables if first iteration
    if (node == root)
    {
        minNode = root;
        minDist = minLine.getLength();
    }

    // Update minimum node if current node is closer to point
    Line nodeLine(node, p);
    float currDist = nodeLine.getLength();
    if (currDist < minDist)
    {
        minDist = currDist;
        minNode = node;
    }
    
    for (int i = 0; i < node->children.size(); i++)
    {
        findClosest(node->children[i], p);
    }

    return minNode;
}

void RRT::traceBack(RRTNode* finalNode, sf::RenderWindow& window)
{
    RRTNode* currNode = finalNode;
    cout << "Distance to Come: " << finalNode->distToCome << endl;
    while (currNode->parent != NULL)
    {
        RRTNode* par = currNode->parent;
        
        vector<RRTNode*>::iterator itr = find(par->children.begin(), par->children.end(), currNode);
        int idx = distance(par->children.begin(), itr);
        par->optEdge[idx] = true;

        Line newTraceLine(par, currNode);
        newTraceLine.draw(window, sf::Color::Red);
        currNode = par;
    }
}

bool RRT::isCollision(RRTNode* p, RRTNode* c)
{
    Line parToChild(p, c);
    for (int i = 0; i < obstacles.size(); i++)
    { 
        if (obstacles[i].checkIntersection(parToChild))
        {
            return true;
        }
    }
    return false;
}

void RRT::buildEnvironment(sf::RenderWindow &window)
{
    // Display start and end points
    start.draw(5, window, sf::Color::Green);
    end.draw(5, window, sf::Color::Red);

    // Create obstacles
    for (int i = 0; i < obstacles.size(); i++)
    {
        obstacles[i].draw(window);
    }
}


bool RRT::runIteration(sf::RenderWindow &window)
{
    Point newPoint(rand() % 1200, rand() % 800);

    RRTNode* newNode = addNode(newPoint, window);

    if (newNode == NULL)
    {
        return false;
    }

    Line newLine(newPoint, end);
    if (newLine.getLength() < goalRadius)
    {
        RRTNode* finalNode = addNode(end, window);
        traceBack(finalNode, window);
        return true;
    }
    return false;
}
